#include <bits/stdc++.h>

#include <vector>
using ll = long long;
using ull = unsigned long long;
using namespace std;
const ull B = 131;
const ll MXN = 2e5 + 5;
ull pw[MXN];
void init() {
    pw[0] = 1;
    for (ll i = 1; i < MXN; i++) pw[i] = pw[i - 1] * B;
}
unordered_map<ll, ll> cnt;
ull h[MXN];
char tmp[MXN];
vector<ll> sz;
#define geth(l, r) (h[r] - h[(l) - 1] * pw[(r) - (l) + 1])
void gen(ll n, char *s) {
    sz.push_back(n);
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * B + s[i];
    }
    vector<ull> unq;
    for (ll i = 1; i <= n; i++) {
        ull res = geth(i, n) * pw[i - 1] + geth(1, i - 1);
        // cout<<i<<" "<<res<<" "<<('c'*B+'a')<<endl;
        unq.push_back(res);
    }
    sort(unq.begin(), unq.end());
    unq.erase(unique(unq.begin(), unq.end()), unq.end());
    for (auto &i : unq) ++cnt[i];
}
ll solve(ll n, char *s) {
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * B + s[i];
    }
    ll ans = 0;
    for (auto &l : sz) {
        if (l > n) break;
        for (ll i = l; i <= n; i++) {
            // if (l == 2 && i == 3) cout << "!!!" << geth(i-l+1, i);
            auto it = cnt.find(geth(i - l + 1, i));
            if (it != cnt.end()) {
                ans += it->second;
            }
        }
    }
    return ans;
}
int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();
    ll n, q;
    cin >> n >> q;
    for (ll i = 1; i <= n; i++) {
        cin >> (tmp + 1);
        gen(strlen(tmp + 1), tmp);
    }
    sort(sz.begin(), sz.end());
    sz.erase(unique(sz.begin(), sz.end()), sz.end());
    while (q--) {
        cin >> (tmp + 1);
        cout << solve(strlen(tmp + 1), tmp) << '\n';
    }

    return 0;
}

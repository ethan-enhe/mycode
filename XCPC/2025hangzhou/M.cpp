#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
vector<ll> get_fact(ll x) {
    vector<ll> res;
    for (ll i = 1; i * i <= x; i++)
        if (x % i == 0) {
            res.push_back(i);
            if (i * i != x) {
                res.push_back(x / i);
            }
        }
    return res;
}
const ll MXN = 5e4 + 5;
const ll INF = 1e18;
ll n, k;
ll b[MXN];
set<ll> possible;

ll stk[MXN], top;
void upd(ll x, ll y) {
    vector<ll> rm;
    for (auto delt : possible) {
        if ((y + delt) % (x + delt)) {
            rm.push_back(delt);
        }
    }
    for (auto i : rm) possible.erase(i);
}
void solve() {
    top = 0;
    b[0] = -INF;
    for (ll i = 1; i <= n; i++) {
        while (b[stk[top]] >= b[i]) --top;
        if (top) {
            upd(b[stk[top]], b[i]);
        }
        stk[++top] = i;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        possible.clear();
        cin >> n >> k;
        ll mn = INF, mx = -INF;
        for (ll i = 1; i <= n; i++) {
            cin >> b[i];
            mn = min(mn, b[i]);
            mx = max(mx, b[i]);
        }
        if (mx == mn) {
            cout << k << " " << (k + 1) * k / 2 << "\n";
            continue;
        }
        auto f = get_fact(mx - mn);
        for (auto i : f) {
            ll v = i - mn;
            if (v >= 1 && v <= k) {
                possible.insert(v);
            }
        }
        solve();
        reverse(b + 1, b + 1 + n);
        solve();
        ll sum = 0;
        for (auto i : possible) sum += i;
        cout << possible.size() << " " << sum << "\n";
    }
    return 0;
}

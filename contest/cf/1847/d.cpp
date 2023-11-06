#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

ll n, m, q, arr[MXN];
vector<ll> tmp[MXN];
char str[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    cin >> (str + 1);
    for (ll i = 1; i <= m; i++) {
        ll l, r;
        cin >> l >> r;
        tmp[l].push_back(i);
        tmp[r + 1].push_back(-i);
    }
    vector<ll> idx;
    set<ll> cover;
    for (ll i = 1; i <= n; i++) {
        for (auto &j : tmp[i]) {
            if (j > 0) cover.insert(j);
            if (j < 0) cover.erase(-j);
        }
        if (!cover.empty()) arr[i] = *cover.begin();

        if (arr[i]) idx.push_back(i);
    }
    arr[n + 1] = m + 1;
    idx.push_back(n + 1);
    auto cmp = [](ll x, ll y) {
        if (arr[x] == arr[y]) return x < y;
        return arr[x] < arr[y];
    };
    sort(all(idx), cmp);
    ll tot = 0, inplace = 0, ind = 0;
    for (ll i = 1; i <= n; i++) tot += str[i] - '0';
    while (ind < min(tot, (ll)idx.size() - 1)) inplace += str[idx[ind++]] - '0';
    while (q--) {
        ll x;
        cin >> x;
        if (str[x] == '1') {
            str[x] = '0';
            --tot;
            if (arr[x] && cmp(x, idx[ind])) --inplace;
            while (ind > min(tot, (ll)idx.size() - 1)) inplace -= str[idx[--ind]] - '0';


        } else {
            str[x] = '1';
            ++tot;
            if (arr[x] && cmp(x, idx[ind])) ++inplace;
            while (ind < min(tot, (ll)idx.size() - 1)) inplace += str[idx[ind++]] - '0';
        }
        cout << (min(tot, (ll)idx.size() - 1) - inplace) << '\n';
    }
    return 0;
}

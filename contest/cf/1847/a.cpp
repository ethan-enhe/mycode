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
const char nl = '\n';
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        vector<ll> tmp;
        cin >> n >> m;
        ll s = 0;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
            if (i > 1) {
                ll x = abs(arr[i] - arr[i - 1]);
                tmp.push_back(x);
                s += x;
            }
        }
        sort(all(tmp), [](ll x, ll y) { return x > y; });
        for (ll i = 0; i < m - 1; i++) s -= tmp[i];
        cout << s << nl;
    }
    return 0;
}

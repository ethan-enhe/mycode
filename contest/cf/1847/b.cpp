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
const ll INF = 1e18;
const ll MXN = 1e6 + 5;
const ll mask = (1ll << 34) - 1;

ll n, m, arr[MXN], lf[MXN], rh[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) {
            lf[i] = rh[i] = 0;
            cin >> arr[i];
        }

        ll v = mask, cnt = 0;
        for (ll i = 1; i <= n; i++) {
            v &= arr[i];
        }
        if (v != 0)
            cout << 1 << nl;
        else {
            v = mask;
            for (ll i = 1; i <= n; i++) {
                v &= arr[i];
                if (v == 0) {
                    ++cnt;
                    v = mask;
                }
            }
            cout << cnt << nl;
        }
    }
    return 0;
}

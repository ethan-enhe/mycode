// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = int;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
const ll P = 1e9 + 7;
const char nl = '\n';
const ll MXN = 2100;
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());

ll n, m, arr[MXN], brr[MXN];
int cnt = 0;
pi ans[MXN * MXN];
ll mv(ll v) {
    ll ida, idb;
    for (ll i = 1; i <= n; i++) {
        if (arr[i] == v) ida = i;
        if (brr[i] == v) idb = i;
    }
    if (idb > ida) return 0;
    ll last = ida;
    while (--ida >= idb) {
        if (arr[ida] >= v && arr[ida] != brr[ida]) {
            ans[++cnt] = {ida, last};
            assert(ida < last && arr[ida] > arr[last]);
            swap(arr[ida], arr[last]);
            last = ida;
        }
    }
    return 1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) cin >> arr[i];
        for (ll i = 1; i <= n; i++) cin >> brr[i];
        bool f = 1;
        cnt = 0;
        for (ll i = 1; i <= n; i++) {
            if (!mv(i)) {
                f = 0;
                break;
            }
        }
        if (f) {
            cout << "1\n";
            // assert(cnt <= n * (n - 1) / 2);
            // cout << cnt << nl;
            // for (int i = 1; i <= cnt; i++) cout << ans[i].fi << " " << ans[i].se << nl;
            // for (int i = 1; i <= n; i++) assert(arr[i] == brr[i]);
        } else
            cout << "-1" << nl;
    }
    return 0;
}

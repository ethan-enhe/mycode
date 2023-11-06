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
const ll P = 998244353;
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN], pre[MXN], suf[MXN];
ll ans = 0;
#define lcm(x, y) (x / __gcd(x, y) * y)
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    pre[0] = suf[n + 1] = 1;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        pre[i] = lcm(pre[i - 1], arr[i]);
    }
    for (ll i = n; i; i--) suf[i] = lcm(suf[i + 1], arr[i]);
    for (ll i = 1; i <= n; i++) {
        ll g = 1;
        for (ll j = i + 1; j <= n; j++) {
            ans = (ans + lcm(lcm(lcm(arr[i] + arr[j], g), pre[i - 1]), suf[j + 1])) % P;
            g = lcm(g, arr[j - 1]);
        }
    }
    cout << ans;
    return 0;
}

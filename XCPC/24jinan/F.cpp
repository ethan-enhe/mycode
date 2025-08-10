#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e5 + 5;
const ll LG = 20;
const ll P = 998244353;
ll n, m;
ll fac[MXN], ifac[MXN];
ll f[MXN][LG], succ[MXN];
ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
ll c(ll x, ll y) {
    if (y > x || y < 0) return 0;
    return fac[x] * ifac[y] % P * ifac[x - y] % P;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    fac[0] = ifac[0] = 1;
    for (ll i = 1; i < MXN; i++) {
        fac[i] = fac[i - 1] * i % P;
        ifac[i] = qpow(fac[i], P - 2);
    }
    cin >> m >> n;
    ll ans = c(m, n) * n % P;
    // cout << ans << endl;
    for (ll i = 1; i <= m; i++) {
        f[i][1] = 1;
        for (ll j = i * 2; j <= m; j += i) {
            for (ll k = 1; k < LG; k++) {
                f[j][k] = (f[j][k] + f[i][k - 1]) % P;
            }
            succ[i]++;
        }
        // cout << i << ":" << endl;
        for (ll k = 1; k < LG; k++) {
            // cout << f[i][k] << " ";
            ans = (ans - f[i][k] * c(succ[i], n - k)) % P;
        }
        // cout << endl;
    }
    ans = (ans + P) % P;
    cout << ans;

    return 0;
}

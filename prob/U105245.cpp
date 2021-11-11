#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN = 1e5 + 5, P = 998244353;
ll n, fac[MXN], ifac[MXN], dp[MXN];
inline ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
inline ll c(ll x, ll y) {
    if (y > x || y < 0) return 0;
    return fac[x] * ifac[y] % P * ifac[x - y] % P;
}
int main() {
    scanf("%lld", &n);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % P;
        ifac[i] = qpow(fac[i], P - 2);
    }
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = qpow(4, i);
        for (int j = 2; j <= i; j += 2) {
            ll tmp = c(j, j >> 1);
            dp[i] = (dp[i] - dp[i - j] * tmp % P * tmp) % P;
        }
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++) ans = (ans + dp[i] * qpow(4, n - i)) % P;
    printf("%lld", (ans + P) % P);

    return 0;
}

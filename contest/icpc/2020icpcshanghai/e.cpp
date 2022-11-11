#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e7 + 5;
const ll P = 998244353;
ll n, k;
ll dp[MXN], sum[MXN];
ll fac[MXN], inv[MXN];

ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
ll gsum(ll i) {
    if (i == k)
        return sum[i - 1];
    else
        return (sum[i - 1] - sum[i - k - 1]) % P;
}
int main() {
    fac[0] = 1;
    for (ll i = 1; i < MXN; i++) fac[i] = fac[i - 1] * i % P;
    inv[MXN - 1] = qpow(fac[MXN - 1], P - 2);
    for (ll i = MXN - 1; i; i--) inv[i - 1] = inv[i] * i % P;

    cin >> n >> k;
    dp[0] = sum[0] = 1;
    for (ll i = 1; i <= n; i++) {
        if (i < k) {
            dp[i] = fac[i];
            sum[i] = (sum[i - 1] + 1) % P;
        } else {
            dp[i] = gsum(i) * fac[i - 1] % P;
            sum[i] = (sum[i - 1] + dp[i] * inv[i]) % P;
        }
    }
    cout << (dp[n] % P + P) % P;

    return 0;
}

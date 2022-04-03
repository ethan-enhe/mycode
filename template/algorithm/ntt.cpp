#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN = 4e6 + 5;
const ll MXD = 30;
const ll P = 998244353;
ll wtmp[MXD << 1], *w = wtmp + MXD;
inline ll qpow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % P;
        x = x * x % P;
        y >>= 1;
    }
    return res;
}
inline void init() {
    ll tmp = P - 1, v2 = 0;
    while (!(tmp & 1)) tmp >>= 1, v2++;
    w[v2] = qpow(3, tmp);
    w[-v2] = qpow(w[v2], P - 2);
    while (v2--) {
        w[v2] = w[v2 + 1] * w[v2 + 1] % P;
        w[-v2] = w[-v2 - 1] * w[-v2 - 1] % P;
    }
}
void ntt(ll *f, ll len, ll tp) {
    if (len == 1) return;
    ll f0[len >> 1], f1[len >> 1], tw = w[tp * (ll)log2(len)], cur = 1;
    for (int i = 0; i < len; i += 2) f0[i >> 1] = f[i];
    for (int i = 1; i < len; i += 2) f1[i >> 1] = f[i];
    ntt(f0, len >> 1, tp);
    ntt(f1, len >> 1, tp);
    for (int i = 0; i < (len >> 1); i++, cur = cur * tw % P)
        f[i] = (f0[i] + cur * f1[i]) % P, f[i + (len >> 1)] = (f0[i] - cur * f1[i]) % P;
}
ll n, m;
ll arr[MXN], brr[MXN];
int main() {
    init();
    scanf("%lld%lld", &n, &m);
    n++, m++;
    for (int i = 0; i < n; i++) scanf("%lld", arr + i);
    for (int i = 0; i < m; i++) scanf("%lld", brr + i);
    ll mxl = 1 << (ll)(log2(n + m) + 1);
    ntt(arr, mxl, 1);
    ntt(brr, mxl, 1);
    for (int i = 0; i < mxl; i++) arr[i] = arr[i] * brr[i] % P;
    ntt(arr, mxl, -1);
    ll tmp = qpow(mxl, P - 2);
    for (int i = 0; i < n + m - 1; i++) printf("%lld ", tmp * (arr[i] + P) % P);

    return 0;
}

#include <bits/stdc++.h>

#include <cmath>
using namespace std;
typedef long long ll;
const ll MXN = 2.1e6 + 5;
const ll P = 998244353;
const ll MXLG = 30;
ll trt[MXLG << 1], *rt = trt + MXLG;
inline ll fix(ll x) { return x < 0 ? x + P : x; }
inline ll qpow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % P;
        y >>= 1, x = x * x % P;
    }
    return res;
}
inline void init() {
    ll tmp = P - 1, tcnt = 0;
    while (!(tmp & 1)) tmp >>= 1, tcnt++;
    rt[tcnt] = qpow(3, tmp);
    rt[-tcnt] = qpow(rt[tcnt], P - 2);
    while (--tcnt) {
        rt[tcnt] = rt[tcnt + 1] * rt[tcnt + 1] % P;
        rt[-tcnt] = rt[-tcnt - 1] * rt[-tcnt - 1] % P;
    }
}
inline void ntt(ll *f, ll len, ll tp) {
    if (len == 1) return;
    ll tf[2][len >> 1], cw = 1, w0 = rt[tp * (ll)log2(len)];
    for (int i = 0; i < len; i++) tf[i & 1][i >> 1] = f[i];
    ntt(tf[0], len >> 1, tp);
    ntt(tf[1], len >> 1, tp);
    for (int i = 0; i < len >> 1; i++, cw = cw * w0 % P) {
        f[i] = (tf[0][i] + tf[1][i] * cw) % P;
        f[i + (len >> 1)] = (tf[0][i] - tf[1][i] * cw) % P;
    }
}
ll h;
ll n, m, arr[MXN], brr[MXN];
void mult() {
    ll tlen = 1 << int(log2(n + m - 1) + 1);
    ntt(arr, tlen, 1);
    ntt(brr, tlen, 1);
    for (int i = 0; i < tlen; i++) arr[i] = arr[i] * brr[i] % P;
    ntt(arr, tlen, -1);
    ll tmp = qpow(tlen, P - 2);
    for (int i = 0; i < n + m - 1; i++) arr[i] = fix(arr[i] * tmp % P);
}

ll tmp[MXN];
void mv(ll *x, ll y) {
    for (ll i = 0; i < n; i++) tmp[i] = x[i];
    for (ll i = 0; i < n; i++) {
        if (i - y >= 0 && i - y < n)
            x[i] = tmp[i - y];
        else
            x[i] = 0;
    }
}
ll fac[MXN], ifac[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (ll i = 1; i < MXN; i++) fac[i] = fac[i - 1] * i % P;
    ifac[MXN - 1] = qpow(fac[MXN - 1], P - 2);
    for (ll i = MXN - 1; i; i--) ifac[i - 1] = ifac[i] * i % P;

    init();
    cin >> h;
    n = m = (1 << h);
    arr[n - 1] = qpow(2, n - 1);
    fac[0] = 1;

    for (ll i = h - 2; i >= 0; i--) {
        mv(arr, -qpow(2, i + 2) + 1);
        // cerr << "left" << -qpow(2, i + 1) - qpow(2, i) + 1;
        ll pw2 = qpow(2, i + 1);
        for (ll j = 0; j < n; j++) {
            brr[j] = j < pw2 ? ifac[j] : 0;
            arr[i] = arr[i] * fac[i] % P;
        }
        mult();
        for (ll j = 0; j < n; j++) arr[i] = arr[i] * ifac[i] % P;
        mv(arr, pow(2, i + 1) - 1);
        // for (ll i = 0; i < n; i++) cerr << arr[i] << " ";
        // cerr << endl;
    }
    for (ll i = n; i; i--) {
        arr[i] = (arr[i] + arr[i + 1]) % P;
        cout << arr[i] << "\n";
    }

    return 0;
}

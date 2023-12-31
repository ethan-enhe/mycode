#include <bits/stdc++.h>

#include <cmath>
using ld = long double;
using ll = long long;
using comp = std::complex<ld>;
using namespace std;
const ll P = 998244353;
const ll root = 3;
ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P;
        y >>= 1;
    }
    return r;
}
ll tmp[1000], *w = tmp + 500;
void init() {
    ll tmp = P - 1, cnt = 0;
    while (tmp % 2 == 0) tmp /= 2, ++cnt;
    ll w0 = qpow(root, tmp);
    for (ll i = cnt; ~i; i--) {
        w[i] = w0;
        w0 = w0 * w0 % P;
    }
    for (ll i = -cnt; i < 0; i++) w[i] = qpow(w[-i], P - 2);
}
void fft(vector<ll> &x, ll ht, ll tp) {
    ll n = x.size();
    ll h = n / 2;
    if (n == 1) return;
    vector<ll> nx[2];
    nx[0].resize(h);
    nx[1].resize(h);
    for (ll i = 0; i < n; i++) nx[i & 1][i >> 1] = x[i];
    fft(nx[0], ht - 1, tp);
    fft(nx[1], ht - 1, tp);
    ll mult = 1, _w = w[tp * ht];
    for (ll i = 0; i < h; i++) {
        x[i] = (nx[0][i] + nx[1][i] * mult) % P;
        x[i + h] = (nx[0][i] - nx[1][i] * mult) % P;
        mult = mult * _w % P;
    }
}
vector<ll> mult(const vector<ll> &x, const vector<ll> &y) {
    ll len = x.size() + y.size() - 1;
    ll tmp = ceil(log2(len));
    len = 1 << tmp;
    vector<ll> _x, _y;
    _x.assign(len, 0);
    _y.assign(len, 0);
    for (ll i = 0; i < x.size(); i++) _x[i] = x[i];
    for (ll i = 0; i < y.size(); i++) _y[i] = y[i];
    fft(_x, tmp, 1);
    fft(_y, tmp, 1);
    for (ll i = 0; i < len; i++) _x[i] = _x[i] * _y[i] % P;
    fft(_x, tmp, -1);
    vector<ll> res(x.size() + y.size() - 1);
    ll inv = qpow(len, P - 2);
    for (ll i = 0; i < res.size(); i++) res[i] = _x[i] * inv % P;
    return res;
}
const ll MXN = 1e5 + 5;
ll n;
ll arr[MXN];
vector<ll> solve(ll l, ll r) {
    if (l == r) return {(1 - arr[l]) % P, arr[l]};
    ll mid = (l + r) >> 1;
    return mult(solve(l, mid), solve(mid + 1, r));
}
int main() {
    init();
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        arr[i] = qpow(x, P - 2);
    }
    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        arr[i] = arr[i] * qpow(x, P - 2) % P;
    }
    vector<ll> ans = solve(1, n);
    ll sum = 0;
    for (ll i = 0; i * 2 <= n; i++) {
        sum = (sum + ans[i]) % P;
    }
    if (sum)
        cout << (qpow(sum, P - 2) + P) % P;
    else
        cout << "-1";

    return 0;
}

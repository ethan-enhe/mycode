#include <bits/stdc++.h>

using namespace std;
#define fi first
#define se second
#define vec vector

using ll = long long;
using pi = pair<ll, ll>;
template <typename T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
const ll P = 998244353;
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() : v() {}
    template <typename T>
    mod(const T &_v) : v(_v) {
        if (v >= P || v < 0) v = incr(v % P);
    }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod operator+(const mod &y) const { return mod{redu(v + y.v)}; }
    mod operator-(const mod &y) const { return mod{incr(v - y.v)}; }
    mod operator*(const mod &y) const { return mod{1ll * v * y.v % P}; }
    mod operator/(const mod &y) const { return mod{1ll * v * (ll)qpow(y, P - 2) % P}; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = 1ll * v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = 1ll * v * (ll)qpow(y, P - 2) % P, *this; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y = mod(x), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
const char nl = '\n';
const ll MXN = 152510;

struct f {
    mod a0, a1;
    f(mod _a0 = 0, mod _a1 = 0) : a0(_a0), a1(_a1) {}
    f operator+(const f &b) const { return {a0 + b.a0, a1 + b.a1}; }
    f operator-(const f &b) const { return {a0 - b.a0, a1 - b.a1}; }
    f operator*(const f &b) const { return {a0 * b.a0, a1 * b.a0 + b.a1 * a0}; }
    f operator/(const f &b) const {
        mod inv = (mod)1 / b.a0;
        return {a0 * inv, (a1 * b.a0 - a0 * b.a1) * inv * inv};
    }
    f &operator+=(const f &b) {
        a0 += b.a0, a1 += b.a1;
        return *this;
    }
    f &operator-=(const f &b) {
        a0 -= b.a0, a1 -= b.a1;
        return *this;
    }
    bool operator!=(const f &b) const { return a0 != b.a0 || a1 != b.a1; }
};

f det(vec<vec<f>> mat, ll len) {
    f res(1);
    for (ll i = 1; i <= len; i++) {
        ll k = -1;
        for (ll j = i; j <= len; j++)
            if (mat[j][i].a0 != 0) k = j;
        if (k == -1) return f(0);
        if (k != i) {
            swap(mat[k], mat[i]);
            res = f(0) - res;
        }
        res = res * mat[i][i];
        f inv = f(1) / mat[i][i];

        for (ll j = i; j <= len; j++) mat[i][j] = mat[i][j] * inv;
        for (ll j = i + 1; j <= len; j++)
            for (ll k = len; k >= i; k--) mat[j][k] = mat[j][k] - mat[i][k] * mat[j][i];
    }
    return res;
}
vec<vec<f>> mat;
vec<pi> g[MXN];
mod res[MXN];
bool isc[MXN];

void ae(ll u, ll v, ll w) {
    mat[u][u] += {1, w};
    mat[v][v] += {1, w};
    mat[u][v] -= {1, w};
    mat[v][u] -= {1, w};
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, m;
    cin >> n >> m;
    while (m--) {
        ll u, v, w;
        cin >> u >> v >> w;
        g[w].push_back({u, v});
    }
    mat.assign(n + 1, vec<f>(n + 1));
    for (ll i = 1; i < MXN; i++) {
        ll cnt = 0;
        for (ll j = i; j < MXN; j += i) cnt += g[j].size();
        if (cnt < n - 1) continue;
        for (ll i = 1; i <= n; i++) fill(mat[i].begin(), mat[i].end(), f());
        for (ll j = i; j < MXN; j += i)
            for (pi &e : g[j]) ae(e.fi, e.se, j);
        res[i] = det(mat, n - 1).a1;
    }
    for (ll i = 2; i < MXN; i++)
        if (!isc[i]) {
            for (ll j = i * i; j < MXN; j += i) isc[j] = 1;
            for (ll j = 1; j * i < MXN; j++) res[j] -= res[j * i];
        }
    mod ans = 0;
    for (ll i = 1; i < MXN; i++) ans += res[i] * i;
    cout << ans << nl;
    return 0;
}

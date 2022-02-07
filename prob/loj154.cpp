#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define vec vector
#define endl '\n'

#define va2d(x, y) x[(y.fi)][(y.se)]
struct mll;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
typedef vec<ll> vi;
typedef vec<vi> vvi;
typedef vec<mll> vm;
typedef vec<vm> vvm;
typedef vec<pi> vpi;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
const ll INF = 1e18;
const ll P(998244353);
const ll MXN = 1e6 + 5;
//{{{ Func
template <typename T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, T y) {
    x = min(x, y);
}
ll abs(pi x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
void setp(int x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void read(vm x) {
    for (T &v : x) cin >> v;
}
template <typename T>
void prt(vm x, string join = " ") {
    for (T &v : x) cout << v << join;
}
//}}}
//{{{ Type
const pi go[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
ll redu(const ll &x) { return x >= P ? x - P : x; }
struct mll {
    ll v;
    mll() : v() {}
    template <typename T>
    mll(const T &_v) : v(_v) {
        if (v >= P || v < 0) {
            v %= P;
            if (v < 0) v += P;
        }
    }
    explicit operator ll() const { return v; }
    mll operator+(const mll &y) const { return mll{redu(v + y.v)}; }
    mll operator-(const mll &y) const { return mll{redu(P + v - y.v)}; }
    mll operator*(const mll &y) const { return mll{(v * y.v) % P}; }
    mll operator/(const mll &y) const { return mll{(v * (ll)qpow(y, P - 2)) % P}; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = v * y.v % P, *this; }
    mll &operator/=(const mll &y) { return v = v * (ll)qpow(y, P - 2) % P, *this; }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mll &y) {
        ll x;
        is >> x;
        return y = mll(x), is;
    }
    friend ostream &operator<<(ostream &os, mll &y) { return os << y.v; }
};
//}}}
void fwt(vm &x) {
    for (ll w = 1; w < x.size(); w <<= 1)
        for (ll i = 0; i < x.size(); i++)
            if (i & w) x[i] += x[i ^ w];
}
void ifwt(vm &x) {
    for (ll w = 1; w < x.size(); w <<= 1)
        for (ll i = 0; i < x.size(); i++)
            if (i & w) x[i] -= x[i ^ w];
}
vm subset_conv(vm a, vm b) {
    ll n = max(a.size(), b.size()), h = log2(n);
    vvm a_group(h + 1, vm(n)), b_group(h + 1, vm(n));
    vm tmp(n), c(n);
    for (ll i = 0; i < a.size(); i++) a_group[__builtin_popcount(i)][i] = a[i];
    for (ll i = 0; i < b.size(); i++) b_group[__builtin_popcount(i)][i] = b[i];
    for (ll i = 0; i <= h; i++) fwt(a_group[i]), fwt(b_group[i]);
    for (ll sz = 0; sz <= h; sz++) {       // 最终集合大小
        for (ll asz = 0; asz <= sz; asz++) // a 对应集合大小
            for (ll k = 0; k < n; k++) tmp[k] += a_group[asz][k] * b_group[sz - asz][k];
        ifwt(tmp);
        for (ll i = 0; i < n; i++)
            if (__builtin_popcount(i) == sz) c[i] = tmp[i];
        tmp.assign(n, 0);
    }
    return c;
}
vm add(vm a, vm b) {
    if (a.size() < b.size()) swap(a, b);
    vm c(a);
    for (ll i = 0; i < b.size(); i++) c[i] += b[i];
    return c;
}
vm magic(vm a, vm f) {
    ll h = f.size() - 1, n = a.size();
    assert(n == 1 << h);
    vec<vvm> g(h + 1);
    vm a_group;
    g[0].resize(h + 1);
    for (ll i = 0; i <= h; i++) g[0][i] = {f[i], 0};
    for (ll i = 1, w = 2; i <= h; i++, w <<= 1) {
        g[i].resize(h + 1 - i);
        a_group.resize(w);
        for (int j = 0; j < w; j++) a_group[j] = j >= (w >> 1) ? a[j] : 0;
        for (int j = 0; j <= (h - i); j++) g[i][j] = add(g[i - 1][j], subset_conv(g[i - 1][j + 1], a_group));
        g[i - 1].clear();
    }
    return g[h][0];
}

int main() {
    /* freopen("loj154.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setp(6);
    ll n, m, k;
    cin >> n >> m >> k;
    vm a(1 << n), f(n + 1), res(1 << n);
    for (int i = 0; i <= k; i++) f[i] = 1;
    for (ll i = 1, x; i <= m; i++) {
        cin >> x;
        a[x] += 1;
    }
    res = magic(a, f);
    cout << res[(1 << n) - 1];
    return cout.flush(), 0;
}

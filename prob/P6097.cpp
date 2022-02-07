#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define vec vector

#ifdef ONLINE_JUDGE
#define logf(fmt...) void()
#else
#define logf(fmt...) fprintf(stderr, fmt)
#endif

#define va2d(x, y) x[(y.fi)][(y.se)]

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
constexpr ll INF = 1e18;
constexpr ll P(1e9 + 9);
constexpr ll MXN = 1e6 + 5;
//{{{ Func
template <typename T>
constexpr T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
constexpr ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T>
constexpr void umx(T &x, T y) {
    x = max(x, y);
}
template <typename T>
constexpr void umn(T &x, T y) {
    x = min(x, y);
}
constexpr ll abs(pi x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
//}}}
//{{{ Type
constexpr pi go[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
constexpr pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
constexpr pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
constexpr pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
ll redu(const ll &x) { return x >= P ? x - P : x; }
struct mll {
    ll v;
    constexpr mll() : v() {}
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
    mll &operator=(const mll &y) { return v = y.v, *this; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = v * y.v % P, *this; }
    mll &operator/=(const mll &y) { return v = v * (ll)qpow(y, P - 2) % P, *this; }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
};
//}}}
template <typename T>
void fwt(vector<T> &x) {
    for (ll w = 1; w < x.size(); w <<= 1)
        for (ll i = 0; i < x.size(); i++)
            if (i & w) x[i] += x[i ^ w];
}
template <typename T>
void ifwt(vector<T> &x) {
    for (ll w = 1; w < x.size(); w <<= 1)
        for (ll i = 0; i < x.size(); i++)
            if (i & w) x[i] -= x[i ^ w];
}
template <typename T>
vector<T> subset_conv(vector<T> a, vector<T> b) {
    ll n = a.size(), h = 31 - __builtin_clz(n);
    assert(a.size() == b.size() && n == 1 << h);
    vector<vector<T>> ag(h + 1, vector<T>(n)), bg(h + 1, vector<T>(n));
    vector<T> tmp(n), c(n);
    for (ll i = 0; i < n; i++) ag[__builtin_popcount(i)][i] = a[i];
    for (ll i = 0; i < n; i++) bg[__builtin_popcount(i)][i] = b[i];
    for (ll i = 0; i <= h; i++) fwt(ag[i]), fwt(bg[i]);
    for (ll sz = 0; sz <= h; sz++) {
        for (ll asz = 0; asz <= sz; asz++)
            for (ll k = 0; k < n; k++) tmp[k] += ag[asz][k] * bg[sz - asz][k];
        ifwt(tmp);
        for (ll i = 0; i < n; i++)
            if (__builtin_popcount(i) == sz) c[i] = tmp[i];
        tmp.assign(n, 0);
    }
    return c;
}

int main(int argc, char *argv[]) {
    ll n;
    scanf("%lld", &n);
    n = 1 << n;
    vector<mll> a(n), b(n), c(n);
    for (mll &i : a) scanf("%lld", &i.v);
    for (mll &i : b) scanf("%lld", &i.v);
    c = subset_conv(a, b);
    for (mll &i : c) printf("%lld ", i.v);
    return 0;
}

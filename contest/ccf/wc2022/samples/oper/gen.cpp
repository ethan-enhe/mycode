
#include <bits/stdc++.h>
using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back

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
//{{{ FastMod
#ifdef __SIZEOF_INT128__
constexpr ull top64(ull x, ull y) { return (__uint128_t)x * y >> 64; }
#else
constexpr ull top64(ull x, ull y) {
    ull a = x >> 32, b = x & 0xffffffff;
    ull c = y >> 32, d = y & 0xffffffff;
    ull ac = a * c, bc = b * c, ad = a * d, bd = b * d;
    ull mid34 = (bd >> 32) + (bc & 0xffffffff) + (ad & 0xffffffff);
    ull upper64 = ac + (bc >> 32) + (ad >> 32) + (mid34 >> 32);
    return upper64;
}
#endif
struct brt {
    ull m, b;
    constexpr brt(const ull &m = 1) : m(m), b(((ull)1 << 63) / m << 1) {}
    friend constexpr ull operator/(const ull &a, const brt &mod) {
        ull r = top64(mod.b, a) + 1;
        return r - ((a - r * mod.m) >> 63);
    }
    friend constexpr ull operator%(const ull &a, const brt &mod) {
        ull r = a - mod.m * top64(mod.b, a);
        return r >= mod.m ? r - mod.m : r;
    }
};
//}}}
constexpr ll INF = 1e18;
constexpr brt P(1e9 + 7);
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
struct mll {
    ll v;
    constexpr explicit mll(ll _v = 0) : v(_v) {}
    constexpr explicit operator ll() const { return v; }
    mll operator+(const mll &y) const { return mll((v + y.v) % P); }
    mll operator-(const mll &y) const { return mll((P.m + v - y.v) % P); }
    mll operator*(const mll &y) const { return mll((v * y.v) % P); }
    mll operator/(const mll &y) const { return mll((v * (ll)qpow(y, P.m - 2)) % P); }
    mll &operator=(const mll &y) { return v = y.v, *this; }
    mll &operator+=(const mll &y) { return v = (v + y.v) % P, *this; }
    mll &operator-=(const mll &y) { return v = (P.m + v - y.v) % P, *this; }
    mll &operator*=(const mll &y) { return v = v * y.v % P, *this; }
    mll &operator/=(const mll &y) { return v = v * (ll)qpow(y, P.m - 2) % P, *this; }
    constexpr bool operator==(const mll &y) const { return v == y.v; }
    constexpr bool operator!=(const mll &y) const { return v != y.v; }
};
constexpr mll ltm(const ll &x) { return mll(x % P); }
template <typename T>
struct myvec {
    T *v;
    int sz, dsz;
    myvec() { v = NULL, sz = dsz = 0; }
    ~myvec() { free(v); }
    operator T *() const { return v; }
    T *begin() { return v; }
    T *end() { return v + sz; }
    void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
    void pb(T x) {
        if (sz == dsz) v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
        v[sz++] = x;
    }
    void fill(T x) {
        for (int i = 0; i < sz; i++) v[i] = x;
    }
};
//}}}
ll n, m;
ll arr[MXN];

int main(int argc, char *argv[]) {
    // code
    for(int i=1;i<=1e5;i++)cout<<'(';
    for(int i=1;i<=1e5;i++)cout<<')';
    return 0;
}

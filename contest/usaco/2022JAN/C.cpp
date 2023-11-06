
#include <bits/stdc++.h>
#include <math.h>

#include <cmath>
#include <ctime>
#include <random>
#include <vector>
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
constexpr ll INF = 1e18;
constexpr ll P(1e9 + 7);
constexpr ll MXN = 1e6 + 5, MXR = 1e9;
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

vector<pi> grp[MXN];

inline ld cal(const pi &x, const ld &tx, const ld &ty) { return tx * x.first + ty * x.second; }
ll getE(ld tx, ld ty) {
    pi s;
    for (int i = 1; i <= n; i++) {
        ld mx = -INF;
        ll mxj, sz = grp[i].size();
        for (int j = 0; j < sz; j++) {
            ld res = cal(grp[i][j], tx, ty);
            if (res > mx) mx = res, mxj = j;
        }
        s = s + grp[i][mxj];
        /* cout<<mx<<endl; */
    }
    /* cout<<s.first<<" "<<s.second<<endl; */
    return s.first * s.first + s.second * s.second;
}
ll getE(ld alpha) { return getE(sin(alpha), cos(alpha)); }

int main(int argc, char *argv[]) {
    freopen("test.in","r",stdin);
    /* freopen("test.out","w",stdout); */
    ll en = clock() + 1.5 * CLOCKS_PER_SEC;
    // code
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &m);
        while (m--) {
            ll x, y;
            scanf("%lld%lld", &x, &y);
            grp[i].push_back({x, y});
        }
    }
    ll ans = 0, curE = 0, nxE;
    ll cnt=0;
    while (clock() < en) {
        ++cnt;
        ld alpha = randdb(0, M_PI * 2), T = 1e18, rate = 0.95;

        normal_distribution<ld> dist(0, M_PI);

        while (T > 0.1 && clock() < en) {
            ld nx = alpha + dist(myrand);
            nxE = getE(nx);
            if (nxE > curE || randdb(0, 1) <= exp((nxE - curE) / T)) {
                alpha = nx;
                curE = nxE;
            }
            umx(ans, curE);
            T *= rate;
        }
        /* assert(0) */
        /* cout << alpha; */
        /* cout<<M_PI_2; */
        /* ld alpha=randint */

        /* ans = max(ans, getE(randint(-MXR, MXR), randint(-MXR, MXR))); */
    }
    cerr<<cnt<<endl;
    printf("%lld", ans);
    return 0;
}

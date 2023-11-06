#include <bits/stdc++.h>

#include <cstdio>
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
constexpr ll MXN = 5005;
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
ll n, m[2], arr[MXN];
ll ind[2][MXN], pre[MXN];
mll dp[MXN][MXN];
//{{{rho
inline ll qmul(ll x, ll y, ll mod) {
    ll res = x * y - mod * ll((ld)x / mod * y);
    if (res < 0) return res + mod;
    if (res < mod) return res;
    return res - mod;
}
inline ll qpow(ll x, ll y, ll mod) {
    ll res = 1;
    while (y) {
        if (y & 1) res = qmul(res, x, mod);
        x = qmul(x, x, mod), y >>= 1;
    }
    return res;
}
inline bool ispri(ll x) {
    if (x < 3) return x == 2;
    ll y = x - 1, h = 0;
    while (!(y & 1)) y >>= 1, h++;
    for (ll i = 0; i < 8; i++) {
        ll v = qpow(rand() % (x - 2) + 2, y, x), th = h;
        if (v == 1) continue;
        while (th--) {
            if (v == x - 1) break;
            v = qmul(v, v, x);
        }
        if (th == -1) return 0;
    }
    return 1;
}

inline ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
inline ll f(ll x, ll c, ll mod) {
    ll res = qmul(x, x, mod) + c;
    return res < mod ? res : res - mod;
}
inline ll rho(ll x) {
    ll c = rand() % (x - 1), s = 0;
    for (ll rg = 1;; rg <<= 1) {
        ll t = s, v = 1;
        for (ll j = 1; j <= rg; j++) {
            s = f(s, c, x);
            v = qmul(v, abs(s - t), x);
            if (!v) {
                ll g = gcd(s, x);
                if (g > 1) return g;
                return x;
            }
            if (j % 127 == 0) {
                ll g = gcd(v, x);
                if (g > 1) return g;
            }
        }
        ll g = gcd(s, x);
        if (g > 1) return g;
    }
}
vector<ll> res;
inline void fact(ll x) {
    if (x == 1) return;
    if (ispri(x)) {
        res.push_back(x);
        return;
    }
    ll p;
    do
        p = rho(x);
    while (p == x);
    do
        x /= p;
    while (x % p == 0);
    fact(x), fact(p);
}

//}}}
int main(int argc, char *argv[]) {
    freopen("B.in", "r", stdin);
    /* freopen("B.out","w",stdout); */
    // code
    int t;
    scanf("%d", &t);
    while (t--) {
        m[0] = m[1] = 0;
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", arr + i);
            ind[arr[i] & 1][++m[arr[i] & 1]] = i;
            for (ll &j = pre[i] = i - 1; j; j--) {
                ll delt = abs(arr[i] - arr[j]);
                if (delt & 1 && delt != 1) break;
            }
            /* cerr << pre[i] << " "; */
        }
        for (int i = 0; i <= m[0]; i++)
            for (int j = 0; j <= m[1]; j++) dp[i][j] = 0;
        dp[0][0] = 1;
        for (int i = 0; i <= m[0]; i++)
            for (int j = 0; j <= m[1]; j++) {
                if (pre[ind[0][i + 1]] <= ind[1][j]) dp[i + 1][j] += dp[i][j];
                if (pre[ind[1][j + 1]] <= ind[0][i]) dp[i][j + 1] += dp[i][j];
            }
        printf("%lld\n", dp[m[0]][m[1]].v);
    }
    return 0;
}

#include <bits/stdc++.h>

#include <numeric>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define vec vector
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

struct mod;

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
using vi = vec<ll>;
using vvi = vec<vi>;
using vvvi = vec<vvi>;
using vm = vec<mod>;
using vvm = vec<vm>;
using vpi = vec<pi>;
using vvpi = vec<vpi>;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
const char nl = '\n';
const ll INF = 1e18;
const ll P = 1e9 + 7;
const ll MXN = 1e6 + 5;
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
//{{{ Func
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
istream &operator>>(istream &is, pi &y) { return is >> y.fi >> y.se; }
ostream &operator<<(ostream &os, pi &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
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
bool insqr(pi x, pi lt, pi rb) { return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se; }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
void setp(ll x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
//}}}
//{{{ Type
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
//}}}

//{{{ Fast IO
namespace fio {
const int BS = 1 << 20;
char ibuf[BS], *ip1 = ibuf, *ip2 = ibuf;
char obuf[BS], *op = obuf;
#define gc() (ip1 == ip2 && (ip2 = (ip1 = ibuf) + fread(ibuf, 1, BS, stdin), ip1 == ip2) ? EOF : *ip1++)
#define flsh() (fwrite(obuf, 1, op - obuf, stdout), op = obuf)
#define pc(x) (*op++ = (x), op == obuf + BS && flsh())
struct flusher {
    inline ~flusher() { flsh(); }
} tmp;

template <class T>
inline void read(T &x) {
    bool f = 0;
    x = 0;
    char c;
    while (c = gc(), !isdigit(c))
        if (c == '-') f = 1;
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
    if (f) x = -x;
}
inline void read(char &x) {
    while (x = gc(), isspace(x))
        ;
}
inline void read(char *x) {
    while (*x = gc(), isspace(*x))
        if (*x == EOF) return;
    while (*++x = gc(), !isspace(*x) && *x != EOF)
        ;
    *x = 0;
}
template <class T>
inline void prt(T x) {
    if (x < 0) pc('-'), x = -x;
    if (x > 9) prt(x / 10);
    pc(x % 10 ^ 48);
}
inline void prt(const char x) { pc(x); }
inline void prt(char *x) {
    while (*x) pc(*x++);
}
inline void prt(const char x[]) {
    for (int i = 0; x[i]; i++) pc(x[i]);
}
#undef gc
#undef pc
#undef flsh
} // namespace fio

void prt() {}
template <typename T1, typename... T2>
void prt(const T1 x, const T2... y) {
    fio::prt(x);
    prt(y...);
}
void read() {}
template <typename T1, typename... T2>
void read(T1 &x, T2 &... y) {
    fio::read(x);
    read(y...);
}
//}}}
ll n, m;
vi a, b;
vvpi g;
int cal(vi &tmp,ll x,ll y){
    for(ll i=x;i && y;i--){
        ll delt=min(y,tmp[i]);

    }

}
void chk(int lim) {
    for (int i = n; i; i--) {
    }
}
bool cmp(const pi &x, const pi &y) { return x > y; }
int main() {
    freopen("ex_challenge1.in", "r", stdin);
    /* freopen(".out","w",stdout); */
    setp(6);
    read(n, m);
    a.resize(n + 1), b.resize(n + 1);
    g.resize(n + 1);
    for (ll i = 1; i <= n; i++) read(a[i]);
    for (ll i = 1; i <= n; i++) read(b[i]);
    for (ll i = 1, u = 0, tu, v, w; i <= m; i++) {
        read(tu, v, w);
        u += tu;
        g[u].push_back({v, w});
    }
    for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end(), cmp);
    return 0;
}


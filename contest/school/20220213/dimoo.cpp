#include <bits/stdc++.h>

#include <array>
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
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ Func
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
istream &operator>>(istream &is, pi &y) { return is >> y.fi >> y.se; }
ostream &operator<<(ostream &os, pi &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
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
template <typename T>
void read(T &x, int l, int r) {
    for (int i = l; i <= r; i++) cin >> x[i];
}
template <typename T>
void prt(T &x, int l, int r, char join = ' ') {
    for (int i = l; i <= r; i++) cout << x[i] << join;
}
//}}}
const ll P = 1e9 + 7;
//{{{ Type
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
//}}}
const ll INF = 1e18;
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const char nl = '\n';
const ll MXN = 1e7 + 5;
ll n, m;
ll cur[MXN], nx[MXN];

namespace io {
const int SIZE = (1 << 21) + 1;
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
// getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
// print the remaining part
inline void flush() {
    fwrite(obuf, 1, oS - obuf, stdout);
    oS = obuf;
}
// putchar
inline void putc(char x) {
    *oS++ = x;
    if (oS == oT) flush();
}
// input a signed integer
template <class I>
inline void gi(I &x) {
    for (f = 1, c = gc(); c < '0' || c > '9'; c = gc())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
    x *= f;
}
// print a signed integer
template <class I>
inline void print(I x) {
    if (!x) putc('0');
    if (x < 0) putc('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putc(qu[qr--]);
}
// no need to call flush at the end manually!
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
} // namespace io
using io ::gi;
using io ::print;
using io ::putc;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    freopen("dimoo.in", "r", stdin);
    freopen("dimoo.out", "w", stdout);
    gi(n), gi(m);
    for (int i = 1; i <= n; i++) gi(cur[i]);
    ll mx = 0;
    for (int i = 1; i <= n; i++) umx(mx, cur[i]);
    if (mx <= 1) {
        for (int i = 1; i <= n; i++) nx[(i + m - 1) % n + 1] = cur[i];
        swap(cur, nx);
    } else {
        for (int i = 1; i <= m; i++) {
            for (int i = 1; i <= n; i++)
                if (cur[i]) {
                    nx[i] += cur[i] - 1;
                    nx[i % n + 1]++;
                }
            for (int i = 1; i <= n; i++) cur[i] = nx[i], nx[i] = 0;
        }
    }
    ull ans = 0, M = 12345678901, v = 1;
    /* cout<<qpow(M,5)<<endl; */
    for (int i = 1; i <= n; i++) {
        v *= M;
        ans += v * (ull)(cur[i] + 1);
    }
    cout << ans << endl;

    return 0;
}


#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <vector>
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
/* #define NDEBUG */
#endif
#include <bits/stdc++.h>

using namespace std;
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = unsigned int;
const char nl = '\n';
const ll MXN = 1e6 + 5, MXM = 5e6 + 5, LG = 20;

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

struct node {
    ll r;
    ll a, b, c;
    inline node operator+(const node &y) const {
        if (r) return {min(r, y.r), a & y.a, b | y.b, __gcd(c, y.c)};
        return {0, 0, 0, 0};
    }
    bool operator<(const node &y) const { return r < y.r; }
    bool operator==(const node &y) const { return r == y.r; }
    void prt() { cerr << r << "," << a << "," << b << "," << c << " "; }
} _and[LG], _or[LG];
vector<node> _gcd;
ll n, m, a[MXN], b[MXN], c[MXN];
vector<pair<ll, ll>> ask[MXN];
ll ans[MXM];
ll c1[MXN], c2[MXN];

inline ll LowBit(ll x) { return x & -x; }

inline void mod(ll i, ll x) {
    for (ll j = i; j <= n; j += LowBit(j)) {
        c1[j] += x;
        c2[j] += i * x;
    }
}

inline ll que(ll i) {
    ll ans1 = 0, ans2 = 0;
    for (ll j = i; j; j ^= LowBit(j)) {
        ans1 += c1[j];
        ans2 += c2[j];
    }
    return ans1 * (i + 1) - ans2;
}

int main() {
    /* cerr<<__gcd(0,3); */
    freopen("test.in", "r", stdin);
    freopen("f.out", "w", stdout);
    read(n, m);
    for (ll i = 1; i <= n; i++) read(a[i]);
    for (ll i = 1; i <= n; i++) read(b[i]);
    for (ll i = 1; i <= n; i++) read(c[i]);
    for (ll i = 1; i <= m; i++) {
        ll ql, qr;
        read(ql, qr);
        ll ans = 0;
        for (ll l = ql; l <= qr; l++)
            for (ll r = l; r <= qr; r++) {
                ll x = a[l], y = b[l], z = c[l];
                for (ll i = l + 1; i <= r; i++) {
                    x &= a[i];
                    y |= b[i];
                    z = __gcd(z, c[i]);
                }
                ans+=x * y * z;
            }
        cout << ans << endl;
    }
    return 0;
}

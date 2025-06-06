// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
// #ifdef LOCAL
// #define dbg(x) cerr << #x << " = " << (x) << endl
// #else
// #define dbg(...) 42
// #define NDEBUG
// #endif
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
//{{{ Func
tpl pair<T, T> &operator+=(pair<T, T> &x, const pair<T, T> &y) { return x.fi += y.fi, x.se += y.se, x; }
tpl pair<T, T> operator+(const pair<T, T> &x, const pair<T, T> &y) { return {x.fi + y.fi, x.se + y.se}; }
tpl pair<T, T> &operator-=(pair<T, T> &x, const pair<T, T> &y) { return x.fi -= y.fi, x.se -= y.se, x; }
tpl pair<T, T> operator-(const pair<T, T> &x, const pair<T, T> &y) { return {x.fi - y.fi, x.se - y.se}; }
tpl pair<T, T> &operator*=(pair<T, T> &x, const ll &y) { return x.fi *= y, x.se *= y, x; }
tpl pair<T, T> operator*(const pair<T, T> &x, const ll &y) { return {x.fi * y, x.se * y}; }
tpl istream &operator>>(istream &is, pair<T, T> &y) { return is >> y.fi >> y.se; }
tpl ostream &operator<<(ostream &os, const pair<T, T> &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
tpl T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (!a || !b) return a | b;
    ll U = __builtin_ctzll(a), V = __builtin_ctzll(b);
    a >>= U, b >>= V;
    if (U > V) U = V;
    while (a) {
        if (a < b) swap(a, b);
        a -= b;
        a >>= __builtin_ctzll(a);
    }
    return b << U;
}
tpl void umx(T &x, const T &y) { x = max(x, y); }
tpl void umn(T &x, const T &y) { x = min(x, y); }
bool inrng(const ll &x, const ll &l, const ll &r) { return l <= x && x <= r; }
bool insqr(const pi &x, const pi &lt, const pi &rb) {
    return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se;
}
void setp(const ll &x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
}
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());
ll ri(const ll &l, const ll &r) { return uniform_int_distribution<ll>(l, r)(mr); }
ld rd(const ld &l, const ld &r) { return uniform_real_distribution<ld>(l, r)(mr); }
//}}}
const ll P = 1e9 + 7;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() {}
    tpl mod(const T &_v) : v(_v) { assert(_v >= 0 && _v < P); }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = (ll)v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = (ll)v * qpow(y, P - 2).v % P, *this; }
    mod operator+(const mod &y) const { return mod(*this) += y; }
    mod operator-(const mod &y) const { return mod(*this) -= y; }
    mod operator*(const mod &y) const { return mod(*this) *= y; }
    mod operator/(const mod &y) const { return mod(*this) /= y; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y.v = incr(x % P), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
//}}}
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

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
inline void read(char &x) { while (x = gc(), isspace(x)); }
inline void read(char *x) {
    while (*x = gc(), isspace(*x))
        if (*x == EOF) return;
    while (*++x = gc(), !isspace(*x) && *x != EOF);
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
void read(T1 &x, T2 &...y) {
    fio::read(x);
    read(y...);
}
//}}}
//

ll n, m;
auto sum = [](ll st, ll len) { return (st + st + len - 1) * len / 2; };
vector<pi> flatten(ll s, ll cnt) {
    if (cnt == 0) return {};
    ll r = ((s * 2 + cnt - 1) / cnt + cnt) / 2;
    ll suml = sum(r - cnt + 1, cnt);
    if (suml == s) {
        // assert(sum(r - cnt + 1, cnt) == s);
        return {pi{r - cnt + 1, r}};
    } else {
        ll num_move = suml - s;
        // assert(sum(r - cnt, num_move) + sum(r - cnt + num_move + 1, cnt - num_move) == s);
        return {pi{r - cnt, r - cnt + num_move - 1}, pi{r - cnt + num_move + 1, r}};
    }
};
vector<pi> stk, seg;

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    read(n);
    for (ll i = 1; i <= n; i++) {
        ll x, c;
        read(x, c);

        auto c_ext = flatten(x * c, c);
        // stk.push_back({x * c, c});
        auto chk = [](ll s1, ll c1, ll s2, ll c2) { return flatten(s1, c1).back().se < flatten(s2, c2).front().fi; };
        ll ss = x * c, cc = c;
        while (!stk.empty() && !chk(stk.back().fi, stk.back().se, ss, cc)) {
            ss += stk.back().fi;
            cc += stk.back().se;
            stk.pop_back();
        }

        stk.push_back({ss, cc});
        // if (stk.empty()) {
        //     stk.push_back({x * c, c});
        // } else {
        //     auto l_ext = flatten(stk.back().fi, stk.back().se);
        //     if (l_ext.back().se < c_ext.front().fi) {
        //         stk.push_back({x * c, c});
        //     } else {
        //         stk.back().se += c;
        //         stk.back().fi += x * c;
        //     }
        // }
    }
    for (auto [s, c] : stk) {
        for (auto [l, r] : flatten(s, c)) {
            seg.push_back({l, r});
            // cerr << l << ' ' << r << nl;
        }
        // cout << s << ' ' << c << nl;
    }

    ll q;
    read(q);
    ll i = 0, sum = 0;
    while (q--) {
        ll x;
        read(x);
        while (sum + seg[i].se - seg[i].fi + 1 < x) {
            sum += seg[i].se - seg[i].fi + 1;
            i++;
        }
        // cerr << sum << ' ' << seg[i].fi << ' ' << x << nl;
        prt(seg[i].fi + x - sum - 1);
        prt('\n');
    }
    // qio.f();
    return 0;
}

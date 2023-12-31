// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <tuple>
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
#define NDEBUG
#endif
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
const ld EPS = 1e-9;

ll n, m, a[MXN], b[MXN], c[MXN];
ld itc(pi x, pi y) { return ld(y.se - x.se) / (x.fi - y.fi); }
struct convex {
    pi q[MXN];
    ll qr;
    convex() { qr = 0; }
    void ins(pi f) {
        if (qr > 1 && itc(q[qr], f) <= itc(q[qr - 1], q[qr])) --qr;
        q[++qr] = f;
    }
    pi getmx(ld x) {
        ll l = 1, r = qr;
        while (l < r) {
            ll mid = (l + r) >> 1;
            if (itc(q[mid], q[mid + 1]) < x)
                l = mid + 1;
            else
                r = mid;
        }
        return q[l];
    }
} ca, cb, cc;
bool f[MXN];
int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    fill(f, f + n * 3 + 1, 1);
    for (ll i = 0; i <= n; i++) cin >> a[i];
    for (ll i = 0; i <= n; i++) cin >> b[i];
    for (ll i = 0; i <= n; i++) cin >> c[i];
    for (ll i = 0; i <= n; i++) {
        ca.ins({i, a[i]});
        cb.ins({i, b[i]});
        cc.ins({i, c[i]});
    }
    pi fa, fb, fc;
    ld cur = -INF;
    tie(fa, fb, fc) = make_tuple(ca.getmx(cur), cb.getmx(cur), cc.getmx(cur));
    ll ans = n * 3 + 1;
    while (1) {
        // cout << fa.fi + fb.fi + fc.fi << " " << fa.fi << " " << fb.fi << " " << fc.fi << " " << cur << endl;
        if (f[fa.fi + fb.fi + fc.fi]) --ans;
        f[fa.fi + fb.fi + fc.fi] = 0;

        ld l = cur, r = INF;
        pi na, nb, nc;
        for (ll i = 1; i <= 100; i++) {
            ld mid = (l + r) / 2;
            tie(na, nb, nc) = make_tuple(ca.getmx(mid), cb.getmx(mid), cc.getmx(mid));
            if (na != fa || nb != fb || nc != fc)
                r = mid;
            else
                l = mid;
        }
        if (l >= (ld)INF / 2) break;
        cur = l + EPS;
        tie(fa, fb, fc) = make_tuple(ca.getmx(cur), cb.getmx(cur), cc.getmx(cur));
    }
    cout << ans << nl;
    for (ll i = 0; i <= n * 3; i++) {
        if (f[i]) cout << i << " ";
    }

    return 0;
}

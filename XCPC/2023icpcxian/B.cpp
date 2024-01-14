// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <cmath>
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
const ll HY = 15;
const ll HX = 45;
const ll HN = 30;
const ll MXHX = HX + 5;
const ll MXIN = HN + 10;

mod fac[MXIN], ifac[MXIN];

ll n, x, yy, hx;
ll cnt[MXHX];
mod dp[MXIN], nx[MXIN];
mod c(ll x, ll y) {
    if (y > x || y < 0) return 0;
    return fac[x] * ifac[y] * ifac[x - y];
}
mod solve(ll y) {
    memset(cnt, 0, sizeof(cnt));
    for (ll i = 0; i < HY; i++)
        if ((y >> i) & 1)
            for (ll j = 0; j < HN; j++)
                if ((n >> j) & 1) {
                    ++cnt[i + j];
                }
    fill(dp, dp + MXIN, 0);
    fill(nx, nx + MXIN, 0);
    dp[0] = 1;
    // 考虑了i-1~0位，进了j,接下来考虑第i位
    ll mx = 0;
    for (ll i = 0; i <= hx; i++) {
        bool cur = (x >> i) & 1;
        for (ll j = 0; j <= mx; j++)
            if (dp[j].v) {
                for (ll choose = (cur ^ j) & 1; choose <= cnt[i]; choose += 2)
                    nx[(choose + j) >> 1] += dp[j] * c(cnt[i], choose);
            }
        mx = (mx + cnt[i]) >> 1;
        swap(dp, nx);
        fill(nx, nx + MXIN, 0);
    }
    return dp[0];
}
mod ans[1 << HY];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = ifac[0] = 1;
    for (ll i = 1; i < MXIN; i++) {
        fac[i] = fac[i - 1] * i;
        ifac[i] = (mod)1 / fac[i];
    }
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> x >> yy;
        hx = ceil(log2l(x));
        for (ll i = 0; i <= yy; i++)
            if ((i & yy) == i) ans[i] = solve(i);
        for (ll j = 0; j < HY; j++)
            if ((yy >> j) & 1)
                for (ll i = 0; i <= yy; i++)
                    if (i & (1 << j)) ans[i] -= ans[i ^ (1 << j)];
        for (ll i = 0; i <= yy; i++)
            if ((i & yy) == i) cout << ans[i] << " ";
        cout << nl;
    }

    return 0;
}

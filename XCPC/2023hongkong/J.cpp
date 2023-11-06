#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
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
const ll P = 998244353;
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
const ll dig = 30;
const ll half = 15;
const ll NR = 1 << half;

ll n, m;
ll hibit[NR], lobit[NR];
mod tomod(ll x) {
    x %= P;
    if (x < 0) x += P;
    return mod(x);
}
ll diff10(ll i) {
    ll tmp = (n - 1) & ((1 << (i + 1)) - 1);
    if (tmp >= (1 << i)) {
        return tmp - (1 << (i + 1)) + 1;
    } else
        return -tmp - 1;
}
ll cnt1(ll i) { return (n + diff10(i)) / 2; }
ll val[dig];
ll cnt[NR], tmp[NR];
void _srt(ll *s, ll *t, ll dig) {
    ll mask = (NR - 1ll) << dig;
    memset(cnt, 0, sizeof(cnt));
    for (ll *i = s; i != t; i++) ++cnt[((*i) & mask) >> dig];
    for (ll i = 1; i < NR; i++) cnt[i] += cnt[i - 1];
    for (ll *i = t; i != s; i--) tmp[--cnt[((*(i - 1)) & mask) >> dig]] = *(i - 1);
    for (ll *i = s; i != t; i++) *i = tmp[i - s];
}
void srt(ll *s, ll *t) {
    _srt(s, t, 0);
    _srt(s, t, 15);
    _srt(s, t, 30);
    _srt(s, t, 45);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    mod tot = 0;
    int t;
    // cin >> t;
    t = 1;
    while (t--) {
        n = 2;
        // cin >> n;
        hibit[0] = lobit[0] = 0;
        for (ll i = 0; i < dig; i++) {
            val[i] = cnt1(i) << i;
            if (i >= half) hibit[0] += val[i];
            if (i < half) lobit[0] += val[i];
        }
        --n;
        for (ll i = 1; i < NR; i++) {
            ll lbt = i & (-i);
            ll idx = 31 - __builtin_clz(lbt);
            hibit[i] = hibit[i ^ lbt] - 2 * val[idx + half];
            lobit[i] = lobit[i ^ lbt] - 2 * val[idx];
        }
        ll leftpart = n >> half, rightpart = n & ((1 << half) - 1);

        mod ans = 0;

        for (ll i = 0; i <= rightpart; i++)
            if (lobit[i] + hibit[leftpart] >= 0) ans += tomod(lobit[i]) + tomod(hibit[leftpart]);

        srt(hibit, hibit + leftpart);
        srt(lobit, lobit + NR);

        mod sum = 0;
        int ind = 0;
        for (ll i = 0; i < leftpart; i++) {
            while (ind < NR && hibit[i] + lobit[ind] >= 0) sum += tomod(lobit[ind++]);
            ans += sum + tomod(hibit[i]) * ind;
        }

        // cout << (ans / (n + 1) + (mod)n * (n + 1) / 2) / (n + 1) << nl;
        tot = (tot + (ans / (n + 1) + (mod)n * (n + 1) / 2) / (n + 1)) * 2;
    }
    cout << tot;

    return 0;
}

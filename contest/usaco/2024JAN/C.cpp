// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
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
const mod INV2 = 500000004;
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

ll n, m;
pi arr[MXN];
#define ls p << 1
#define rs p << 1 | 1
struct node {
    mod s, v, t;
    node() {
        v = t = 1;
        s = 0;
    }
} t[MXN];
void pull(ll p) { t[p].s = t[ls].s + t[rs].s; }
void addt(ll p, mod m) {
    t[p].t *= m;
    t[p].s *= m;
    t[p].v *= m;
}
void push(ll p) {
    if (t[p].t != 1) {
        addt(ls, t[p].t);
        addt(rs, t[p].t);
        t[p].t = 1;
    }
}
mod toggle(ll p, ll l, ll r, ll mi) {
    if (l == r) {
        if (t[p].s.v)
            t[p].s = 0;
        else
            t[p].s = t[p].v;
        return t[p].v;
    }
    ll mid = (l + r) >> 1;
    mod tmp;
    push(p);
    if (mi <= mid)
        tmp = toggle(ls, l, mid, mi);
    else
        tmp = toggle(rs, mid + 1, r, mi);
    pull(p);
    return tmp;
}
void mult(ll p, ll l, ll r, ll ml, ll mr, mod mv) {
    if (ml > r || mr < l) return;
    if (ml <= l && r <= mr) {
        addt(p, mv);
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    mult(ls, l, mid, ml, mr, mv);
    mult(rs, mid + 1, r, ml, mr, mv);
    pull(p);
}
mod sum(ll p, ll l, ll r, ll ml, ll mr) {
    if (ml > r || mr < l) return 0;
    if (ml <= l && r <= mr) {
        return t[p].s;
    }
    ll mid = (l + r) >> 1;
    push(p);
    return sum(ls, l, mid, ml, mr) + sum(rs, mid + 1, r, ml, mr);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    sort(arr + 1, arr + 1 + n);
    mod ans = qpow((mod)2, n) * n;
    for (ll i = 1; i <= n; i++) {
        mult(1, 1, n, 1, i - 1, 2);
    }
    for (ll i = 1; i <= n; i++) {
        mult(1, 1, n, 1, arr[i].se - 1, INV2);
        mod res = toggle(1, 1, n, arr[i].se);
        ans -= res + sum(1, 1, n, arr[i].se + 1, n);
        mult(1, 1, n, arr[i].se + 1, n, 2);
        // cerr << ans << endl;
    }
    for (int i = 1; i < MXN; i++) t[i] = node();
    for (ll i = 1; i <= n; i++) arr[i].se = n + 1 - arr[i].se;
    for (ll i = 1; i <= n; i++) {
        mult(1, 1, n, 1, i - 1, 2);
    }

    for (ll i = 1; i <= n; i++) {
        mult(1, 1, n, 1, arr[i].se - 1, INV2);
        mod res = toggle(1, 1, n, arr[i].se);
        ans -= res + sum(1, 1, n, arr[i].se + 1, n);
        mult(1, 1, n, arr[i].se + 1, n, 2);
        // cout << ans << endl;
    }
    // cout << ans << endl;
    cout << (ans) * 2 << nl;
    return 0;
}

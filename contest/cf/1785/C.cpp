// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
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

ll n, m, arr[MXN], ord[MXN], rev[MXN];
struct node {
    ll tag, sum;
    pi mn;
    node operator+(const node &b) const { return {0, sum + b.sum, min(mn, b.mn)}; }
} t[MXN << 2];
#define ls p << 1
#define rs p << 1 | 1
void addt(ll p, ll k) {
    t[p].tag += k;
    t[p].mn.fi += k;
}
void push(ll p) {
    if (t[p].tag) {
        addt(ls, t[p].tag);
        addt(rs, t[p].tag);
        t[p].tag = 0;
    }
}
void pull(ll p) { t[p] = t[ls] + t[rs]; }
void build(ll p, ll l, ll r) {
    if (l == r) {
        t[p] = {0, 0, {arr[ord[l]], l}};
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pull(p);
}
ll touch(ll p, ll l, ll r, ll qi) {
    if (qi < l || qi > r) return 0;
    if (l == r) {
        t[p].sum = 1;
        return t[p].mn.fi;
    }
    ll mid = (l + r) >> 1;
    push(p);
    ll s = touch(ls, l, mid, qi) + touch(rs, mid + 1, r, qi);
    pull(p);
    return s;
}
node qry(ll p, ll l, ll r, ll ql, ll qr) {
    if (ql > qr) return {0, 0, {INF, INF}};
    if (ql > r || qr < l) return {0, 0, {INF, INF}};
    if (ql <= l && r <= qr) return t[p];
    ll mid = (l + r) >> 1;
    push(p);
    return qry(ls, l, mid, ql, qr) + qry(rs, mid + 1, r, ql, qr);
}
void mdf(ll p, ll l, ll r, ll ql, ll qr, ll qv) {
    if (ql > qr) return;
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        addt(p, qv);
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    mdf(ls, l, mid, ql, qr, qv);
    mdf(rs, mid + 1, r, ql, qr, qv);
    pull(p);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) {
            cin >> arr[i];
            ord[i] = i;
        }
        sort(ord + 1, ord + 1 + n, [](ll x, ll y) { return arr[x] < arr[y]; });
        for (ll i = 1; i <= n; i++) rev[ord[i]] = i;
        build(1, 1, n);
        ll ans = 0;
        for (ll i = 1; i <= n; i++) {
            ans += touch(1, 1, n, rev[i]);
            // cout << ans << " ";
            auto q = qry(1, 1, n, rev[i], n);
            ll r = n;
            if (q.mn.fi == 0) r = q.mn.se - 1;
            ans -= qry(1, 1, n, rev[i], r).sum;
            mdf(1, 1, n, rev[i], r, -1);
            cout << ans << " ";
        }
        cout<<nl;
    }
    return 0;
}

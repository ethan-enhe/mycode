// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <vector>
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
const ll MXN = 2e5 + 5;

ll n, m, arr[MXN];

struct node {
    ll tag, mn;
} t[MXN << 2];
#define ls p << 1
#define rs p << 1 | 1
void pull(ll p) { t[p].mn = min(t[ls].mn, t[rs].mn); }
void addt(ll p, ll k) {
    t[p].tag += k;
    t[p].mn += k;
}
void push(ll p) {
    if (t[p].tag) {
        addt(ls, t[p].tag);
        addt(rs, t[p].tag);
        t[p].tag = 0;
    }
}
void add(ll p, ll l, ll r, ll al, ll ar, ll ak) {
    if (al > r || ar < l) return;
    if (al <= l && r <= ar) {
        addt(p, ak);
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    add(ls, l, mid, al, ar, ak);
    add(rs, mid + 1, r, al, ar, ak);
    pull(p);
}
ll qry(ll p, ll l, ll r, ll ql, ll qr) {
    if (ql > r || qr < l) return INF;
    if (ql <= l && r <= qr) return t[p].mn;
    ll mid = (l + r) >> 1;
    push(p);
    return min(qry(ls, l, mid, ql, qr), qry(rs, mid + 1, r, ql, qr));
}
vector<pi> p[MXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, m, a, sum = 0;
    cin >> m >> n >> a;
    for (ll i = 1; i <= m; i++) {
        ll x, y, c;
        cin >> x >> y >> c;
        y = n - y;
        // cout << x << y << c << endl;
        p[y].push_back({x, c});
        sum += c;
    }
    // for (ll i = -1; i <= n; i++) {
    //     add(1, -1, n, i, i, -(i + 1) * a);
    // }

    for (ll i = 0; i <= n; i++) {
        for (auto &nx : p[i]) {
            add(1, -1, n, -1, nx.fi - 1, -nx.se);
        }
        ll cur = qry(1, -1, n, -1, i - 1) + i * a;
        // cout << cur << nl;
        if (i == n) {
            cout << cur + sum << nl;
        }
        add(1, -1, n, i, i, cur - (i + 1) * a);
    }
    return 0;
}

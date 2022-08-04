#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

ll n, m, arr[MXN];

const ll SZ = 5;
struct mat {
    ll v[SZ][SZ];
    mat() {
        memset(v, ~0x3f, sizeof(v));
        v[0][0] = v[1][1] = v[2][2] = v[3][3] = v[4][4] = 0;
    }
    mat(ll x, ll type) {
        memset(v, ~0x3f, sizeof(v));
        v[0][0] = v[1][1] = v[2][2] = v[3][3] = v[4][4] = 0;
        x = x * x;
        if (type == 1) {
            v[0][1] = v[1][2] = x;
            v[2][3] = v[3][4] = -x;
        } else {
            v[0][1] = v[2][3] = x;
            v[1][2] = v[3][4] = -x;
        }
    }
    mat operator+(const mat &y) const {
#define upd(i, j, k) res.v[i][j] = max(res.v[i][j], v[i][k] + y.v[k][j])
        mat res;
        upd(0, 0, 0);
        upd(0, 1, 0);
        upd(0, 2, 0);
        upd(0, 3, 0);
        upd(0, 4, 0);
        upd(0, 1, 1);
        upd(0, 2, 1);
        upd(0, 3, 1);
        upd(0, 4, 1);
        upd(0, 2, 2);
        upd(0, 3, 2);
        upd(0, 4, 2);
        upd(0, 3, 3);
        upd(0, 4, 3);
        upd(0, 4, 4);
        upd(1, 1, 1);
        upd(1, 2, 1);
        upd(1, 3, 1);
        upd(1, 4, 1);
        upd(1, 2, 2);
        upd(1, 3, 2);
        upd(1, 4, 2);
        upd(1, 3, 3);
        upd(1, 4, 3);
        upd(1, 4, 4);
        upd(2, 2, 2);
        upd(2, 3, 2);
        upd(2, 4, 2);
        upd(2, 3, 3);
        upd(2, 4, 3);
        upd(2, 4, 4);
        upd(3, 3, 3);
        upd(3, 4, 3);
        upd(3, 4, 4);
        upd(4, 4, 4);
        return res;
    }
    void prt() {
        for (ll i = 0; i < SZ; i++, cout << endl)
            for (ll j = 0; j < SZ; j++) cout << v[i][j] << " ";
    }
};

using pm = pair<mat, mat>;
pm v[MXN];
#define ls p << 1
#define rs p << 1 | 1
void build(ll p, ll l, ll r) {
    if (l == r) {
        v[p] = {mat(arr[l], 1), mat(arr[l], 2)};
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    v[p] = v[ls] + v[rs];
}
pm qry(ll p, ll l, ll r, ll ql, ll qr) {
    if (qr < l || ql > r) return pm();
    if (ql <= l && r <= qr) return v[p];
    ll mid = (l + r) >> 1;
    return qry(ls, l, mid, ql, qr) + qry(rs, mid + 1, r, ql, qr);
}

int main() {
	/* freopen("test.in","r",stdin); */
	/* freopen("test.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (ll i = 1; i <= n; i++) cin >> arr[i];
        build(1, 1, n);
        while (m--) {
            ll l, r;
            cin >> l >> r;
            pm res = qry(1, 1, n, l, r);
            cout << max(res.fi.v[0][4], res.se.v[0][4]) << nl;
        }
    }
    return 0;
}

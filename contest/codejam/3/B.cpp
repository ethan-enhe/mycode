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

ll T, n, m, arr[MXN], nx[MXN];
ll A[MXN], B[MXN];
ll lp[MXN], rp[MXN];
ll last[MXN];
void jmp(ll *x, ll y) {
    if (x[y] == 0)
        x[y] = last[y];
    else if (x[y] <= n * 2)
        x[y] = nx[x[y]];
}

pi mrg(pi x, pi y) {
    if (x.fi == y.fi) return {x.fi, x.se + y.se};
    return max(x, y);
}

struct node {
    pi mx;
    ll tag;
} t[MXN << 2];
#define ls p << 1
#define rs p << 1 | 1
void pull(ll p) { t[p].mx = mrg(t[ls].mx, t[rs].mx), t[p].tag = 0; }
void addt(ll p, ll k) {
    t[p].tag += k;
    t[p].mx.fi += k;
}
void push(ll p) {
    if (t[p].tag) {
        addt(ls, t[p].tag);
        addt(rs, t[p].tag);
        t[p].tag = 0;
    }
}
void build(ll p = 1, ll l = 1, ll r = n * 2) {
    if (l == r) {
        t[p] = {{0, 1}, 0};
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pull(p);
}
void mdf(ll ml, ll mr, ll mv, ll p = 1, ll l = 1, ll r = n * 2) {
    if (mr < l || ml > r) return;
    if (ml <= l && r <= mr) {
        addt(p, mv);
        return;
    }
    push(p);
    ll mid = (l + r) >> 1;
    mdf(ml, mr, mv, ls, l, mid);
    mdf(ml, mr, mv, rs, mid + 1, r);
    pull(p);
}
pi qry(ll ml, ll mr, ll p = 1, ll l = 1, ll r = n * 2) {
    if (mr < l || ml > r) return {-INF, 0};
    if (ml <= l && r <= mr) return t[p].mx;
    push(p);
    ll mid = (l + r) >> 1;
    return mrg(qry(ml, mr, ls, l, mid), qry(ml, mr, rs, mid + 1, r));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (ll _t = 1; _t <= T; _t++) {
        cin >> n >> m;
        for (ll i = 1; i <= m; i++) {
            cin >> A[i] >> B[i];
            lp[i] = rp[i] = 0;
            last[i] = 2 * n + 1;
        }
        for (ll i = 1; i <= n; i++) {
            cin >> arr[i];
            arr[i + n] = arr[i];
        }
        for (ll i = n * 2; i; i--) {
            nx[i] = last[arr[i]];
            last[arr[i]] = i;
        }
        build();
        for (ll i = 1; i <= m; i++) {
            ++B[i];
            for (ll j = 1; j <= A[i]; j++) jmp(lp, i);
            for (ll j = 1; j <= B[i]; j++) jmp(rp, i);
            mdf(lp[i], rp[i] - 1, 1);
            if (A[i]) mdf(0, last[i] - 1, 1);
            /* cerr<<lp[i]<<" "<<rp[i]<<nl; */
        }
        ll ans = 0;
        for (ll i = 1; i <= n; i++) {
            pi r = qry(i + 1, i + n - 1);
            /* for (ll i = 1; i <= n * 2; i++) cout << qry(i, i).fi; */
            /* cout << endl; */
            if (r.fi == m) ans += r.se;
            ll x = lp[arr[i]], y = rp[arr[i]];
            jmp(lp, arr[i]);
            jmp(rp, arr[i]);
            mdf(x, lp[arr[i]] - 1, -1);
            mdf(y, rp[arr[i]] - 1, 1);
            if (A[arr[i]]) mdf(i, nx[i] - 1, 1);
        }
        cout << "Case #" << _t << ": " << ans << nl;
    }
    return 0;
}

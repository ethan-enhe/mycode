#include <algorithm>
#include <vector>
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
const ll MXN = 5e5 + 5;

ll n, m;
ll A[MXN], B[MXN];

pi stk[MXN];
ll top;
void clr() { top = 0; }
//从小到大的单调栈
void ins(pi x) {
    while (top && stk[top].fi >= x.fi) --top;
    stk[++top] = x;
}
//最靠前小于x的se
ll qry(ll x) {
    ll ind = lower_bound(stk + 1, stk + 1 + top, pi{x, -1}) - stk;
    return stk[ind - 1].se;
}

vector<pi> seg[MXN];
vector<ll> lind[MXN];

#define ls p << 1
#define rs p << 1 | 1
mod v[MXN];
bool tag[MXN];
void pull(ll p) { v[p] = v[ls] + v[rs]; }
void addt(ll p) {
    tag[p] = 1;
    v[p] += v[p];
}
void push(ll p) {
    if (tag[p]) {
        addt(ls);
        addt(rs);
        tag[p] = 0;
    }
}
void mult(ll ml, ll mr, ll p = 1, ll l = 1, ll r = n + 1) {
    if (ml > r || mr < l) return;
    if (ml <= l && r <= mr) {
        addt(p);
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    mult(ml, mr, ls, l, mid);
    mult(ml, mr, rs, mid + 1, r);
    pull(p);
}
void add(ll mi, mod mv, ll p = 1, ll l = 1, ll r = n + 1) {
    if (l == r) {
        v[p] += mv;
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    if (mi <= mid)
        add(mi, mv, ls, l, mid);
    else
        add(mi, mv, rs, mid + 1, r);
    pull(p);
}
mod que(ll ml, ll mr, ll p = 1, ll l = 1, ll r = n + 1) {
    if (ml > r || mr < l) return 0;
    if (ml <= l && r <= mr) return v[p];
    ll mid = (l + r) >> 1;
    push(p);
    return que(ml, mr, ls, l, mid) + que(ml, mr, rs, mid + 1, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (ll i = 0; i <= n + 1; i++) {
            seg[i].clear();
            lind[i].clear();
        }
        for (ll i = 1; i <= n; i++) cin >> A[i] >> B[i];
        B[0] = B[n + 1] = INF;
        while (m--) {
            ll x, l, r;
            cin >> x >> l >> r;
            seg[x].push_back({l, r});
        }

        auto addseg = [](ll l, ll r) { lind[r + 1].push_back(l); };
        clr();
        for (ll i = 1; i <= n; i++) {
            ins({A[i] - B[i - 1], i});
            for (auto &j : seg[i]) j.fi = qry(j.fi);
        }
        clr();
        for (ll i = n; i; i--) {
            ins({A[i] - B[i + 1], i});
            for (auto &j : seg[i]) {
                j.se = qry(j.se);
                addseg(j.fi, j.se);
                /* cerr << j.fi << "-" << j.se << endl; */
            }
        }
        for (ll i = 0; i < MXN; i++) v[i] = tag[i] = 0;
        add(1, 1);
        /* cout<<que(2, 2); */
        for (ll i = 2; i <= n + 1; i++) {
            sort(all(lind[i]), [](ll x, ll y) { return x > y; });
            for (ll j : lind[i]) {
                add(i, que(j, i));
                if (j > 1) mult(1, j - 1);
            }
        }
        cout << que(n + 1, n + 1) << nl;
    }
    return 0;
}

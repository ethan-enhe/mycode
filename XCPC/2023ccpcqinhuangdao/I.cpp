// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
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
const ll LG = 19;

ll n, m, k, arr[MXN], _div[MXN];
ll mod[MXN], pool[MXN];

ll pre[MXN];
void mdf(ll x, ll y) {
    for (; x <= m; x += x & (-x)) pre[x] += y;
}
ll sum(ll x) {
    ll r = 0;
    for (; x; x -= x & (-x)) r += pre[x];
    return r;
}
ll kth(ll k) {
    ll x = 0;
    for (ll i = (1 << LG); i; i >>= 1) {
        if (x + i <= m && k > pre[x + i]) {
            k -= pre[x + i];
            x += i;
        }
    }
    return x + 1;
}
ll divk, cnt, tot; // 当前维护的区间除k,有多少个数要+k，总共多少个数；
void ins(ll i) {
    mdf(mod[i], 1);
    ++tot;
}
void solve(ll t) {
    ll _t = t;
    while (t) {
        ll nx = arr[n - tot];
        ll nxdiv = nx / k;
        ll nxmod = mod[n - tot];
        if (nxdiv < divk && cnt <= t) {
            --divk;
            t -= cnt;
            cnt = tot;
        }
        ll delt = min(t / tot, divk - nxdiv); // 整体-k 次数
        t -= delt * tot;
        divk -= delt;

        if (divk == nxdiv) {
            delt = cnt - sum(nxmod);
            if (t >= delt) {
                cnt -= delt;
                t -= delt;
                ins(n - tot);
            } else {
                cnt -= t;
                t = 0;
            }
        } else {
            cnt -= t;
            t = 0;
        }
        // cerr << "solve" << _t << " " << t <<" "<<divk<< " " << cnt << " " << tot << endl;
    }
}
ll qry(ll x) {
    if (x <= tot) {
        if (x <= cnt) {
            return (divk + 1) * k + pool[kth(cnt - x + 1)];
        } else {
            // cerr << "!" <<" "<<sum(1,m)<< endl;
            return divk * k + pool[kth(tot - x + cnt + 1)];
        }
    } else
        return arr[n - x + 1];
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll q;
    cin >> n >> q >> k;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        pool[i] = arr[i] % k;
    }
    sort(arr + 1, arr + 1 + n);
    sort(pool + 1, pool + 1 + n);
    m = unique(pool + 1, pool + 1 + n) - pool - 1;
    for (ll i = 1; i <= n; i++) {
        mod[i] = lower_bound(pool + 1, pool + 1 + m, arr[i] % k) - pool;
    }
    arr[0] = -INF;

    divk = arr[n] / k;
    cnt = 0;
    ins(n);
    while (q--) {
        char x;
        ll y;
        cin >> x >> y;
        if (x == 'C')
            solve(y);
        else
            cout << qry(y) << nl;
    }

    return 0;
}

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <numeric>
#include <sstream>
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
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN];
char str[MXN];

namespace SA {
typedef int arrn[MXN];
arrn sa, rk, tmp, ork, cnt;
int h[MXN];
inline bool cmp(int x, int y, int w) { return ork[x] == ork[y] && ork[x + w] == ork[y + w]; }
template <typename T>
inline void init(int n, int m, T *arr) {
    for (int i = 1; i <= m; i++) cnt[i] = 0;
    for (int i = 1; i <= n; i++) cnt[rk[i] = arr[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i; i--) sa[cnt[rk[i]]--] = i;
    for (int w = 1; w <= n; w <<= 1) {
        int ind = 0;
        for (int i = n - w + 1; i <= n; i++) tmp[++ind] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w) tmp[++ind] = sa[i] - w;
        for (int i = 1; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) cnt[rk[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i; i--) sa[cnt[rk[tmp[i]]]--] = tmp[i], ork[i] = rk[i];
        m = 0;
        for (int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? m : ++m;
        if (m == n) break;
    }

    arr[n + 1] = -1;
    for (int i = 1, lcp = 0; i <= n; i++) {
        lcp -= !!lcp;
        while (arr[i + lcp] == arr[sa[rk[i] - 1] + lcp]) ++lcp;
        h[rk[i]] = lcp;
    }
}
} // namespace SA

struct node {
    ll fa, lastl;
    //维护后缀最大值
    set<pi> stk;
} p[MXN];

void ins(set<pi> &x, pi v) {
    auto l = x.upper_bound({v.fi, 0});
    if (l != x.end() && l->second >= v.se) return;
    auto r = l;
    while (l != x.begin()) {
        --l;
        if (l->se > v.se) break;
    }
    if (l->se > v.se) ++l;
    x.erase(l, r);
    x.insert(v);
}

void upd(set<pi> &x, set<pi> &y) {
    for (auto &v : y) ins(x, v);
    y.clear();
}
ll find(ll x) { return x == p[x].fa ? x : p[x].fa = find(p[x].fa); }

ll ans[MXN];
void add(ll l, ll r, ll k) {
    ans[l] += k;
    ans[r + 1] -= k;
}
void mrg(ll x, ll y, ll curl) {
    x = find(x), y = find(y);
    add(curl + 1, p[x].lastl, p[x].stk.size());
    add(curl + 1, p[y].lastl, p[y].stk.size());
    if (p[y].stk.size() > p[x].stk.size()) swap(p[y].stk, p[x].stk);
    upd(p[x].stk, p[y].stk);
    p[x].lastl = curl;
    p[y].fa = x;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> (str + 1);
    n = strlen(str + 1);
    reverse(str + 1, str + 1 + n);
    for (ll i = 1; i <= n; i++) cin >> arr[n - i + 1];

    SA::init(n, 200, str);
    for (ll i = 1; i <= n; i++) {
        p[i].fa = i;
        p[i].lastl = n - SA::sa[i] + 1;
        p[i].stk.insert({SA::sa[i], arr[SA::sa[i]]});
    }
    vector<ll> ord(n);
    iota(all(ord), 1);
    sort(all(ord), [](ll x, ll y) { return SA::h[x] > SA::h[y]; });
    for (ll i : ord) mrg(i, i - 1, SA::h[i]);
    partial_sum(ans + 1, ans + 1 + n, ans + 1);
    for (ll i = 1; i <= n; i++) cout << ans[i] << " ";

    return 0;
}

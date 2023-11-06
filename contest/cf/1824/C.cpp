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
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN];
// 先加后取min
pi tag[MXN];
// 空位的值
ll emp[MXN];
// 实施tag之后取min
ll mn[MXN];
map<ll, ll> dp[MXN];
pi mrg(pi x, pi y) { return {x.fi + y.fi, min(x.se + y.fi, y.se)}; }
ll apply(ll y, pi x) { return min(y + x.fi, x.se); }
ll unapply(ll y, pi x) { return y - x.fi; }
void merge(ll x, ll y) {
    if (dp[x].size() < dp[y].size()) {
        swap(dp[x], dp[y]);
        swap(tag[x], tag[y]);
        swap(mn[x], mn[y]);
        swap(emp[x], emp[y]);
    }
    if (dp[y].size()) {
        ll resmn = min(mn[x] + emp[y], mn[y] + emp[x]);
        pi restag = {tag[x].fi + emp[y], tag[x].se + emp[y]};
        ll resemp = emp[x] + emp[y];
        for (auto &i : dp[y]) {
            assert(i.second==0);
            auto it = dp[x].find(i.first);
            if (it == dp[x].end()) {
                ll tmp = emp[x] + apply(i.second, tag[y]);
                dp[x][i.first] = unapply(tmp, restag);
            } else {
                ll tmp = apply(it->second, tag[x]) + apply(i.second, tag[y]);
                umn(resmn, tmp);
                it->second = unapply(tmp, restag);
            }
        }
        dp[y].clear();
        tag[x] = restag;
        mn[x] = resmn;
        emp[x] = resemp;
    }
}

void updself(ll p) {
    tag[p].second = min(tag[p].second, mn[p] + 1);
    emp[p] = min(tag[p].second, mn[p] + 1);
}

vector<ll> g[MXN];
void dfs(ll p, ll fa) {
    for (ll nx : g[p])
        if (nx != fa) {
            arr[nx] ^= arr[p];
            dfs(nx, p);
        }
}
void dfs2(ll p, ll fa) {
    for (ll nx : g[p])
        if (nx != fa) {
            dfs2(nx, p);
            merge(p, nx);
        }
    if (dp[p].empty()) {
        tag[p] = {0, INF};
        dp[p][arr[p]] = mn[p] = 0;
        emp[p] = INF;
    }
    updself(p);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) cin >> arr[i];
    for (ll i = 1; i < n; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    // for (ll i = 1; i <= n; i++) cout << arr[i];
    dfs(1, 0);
    dfs2(1, 0);
    ll ans = emp[1];
    auto it = dp[1].find(0);
    if (it != dp[1].end()) {
        ans = min(ans, apply(it->second, tag[1]));
    }
    cout << ans;

    return 0;
}

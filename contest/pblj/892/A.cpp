// #pragma GCC optimize("Ofast", "-funroll-loops")
// #pragma GCC target("sse4.1", "sse4.2", "ssse3", "sse3", "sse2", "sse", "avx2", "avx", "popcnt")
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
//{{{ Func
template <typename T>
pair<T, T> operator+(const pair<T, T> &x, const pair<T, T> &y) {
    return {x.fi + y.fi, x.se + y.se};
}
template <typename T>
istream &operator>>(istream &is, pair<T, T> &y) {
    return is >> y.fi >> y.se;
}
template <typename T>
ostream &operator<<(ostream &os, const pair<T, T> &y) {
    return os << '(' << y.fi << ',' << y.se << ')';
}
template <typename T>
T qpow(T x, ll y) {
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
template <typename T>
void umx(T &x, const T &y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, const T &y) {
    x = min(x, y);
}
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
    template <typename T>
    mod(const T &_v) : v(_v) {}
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod operator+(const mod &y) const { return mod(redu(v + y.v)); }
    mod operator-(const mod &y) const { return mod(incr(v - y.v)); }
    mod operator*(const mod &y) const { return mod((ll)v * y.v % P); }
    mod operator/(const mod &y) const { return mod((ll)v * qpow(y, P - 2).v % P); }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = (ll)v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = (ll)v * qpow(y, P - 2).v % P, *this; }
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

ll n, m, cnt, arr[MXN];
mod invn;
unordered_map<ll, mod> dp;
mod dfs(ll x) {
    if (!x) return 0;
    auto it = dp.find(x);
    if (it != dp.end()) return it->se;
    mod ans = 0;
    for (ll i = 2, nx; i <= n; i = nx) {
        nx = min(n, i <= x ? x / (x / i) : INF) + 1;
        ans += dfs(x / i) * (nx - i);
    }
    ++cnt;
    return dp[x] = invn * (ans + n);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    invn = (mod)1 / (n - 1);
    cout << dfs(m) << nl;
    return 0;
}

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstring>
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
const ll MXN = 5005, MXM = 805;

ll n, m, arr[MXN], brr[MXN], crr[MXN];
pi q[MXM][MXM];
ll ql[MXM], qr[MXM];
ll dp[MXM];
void upd(ll a, ll b, ll c) {
    if (b > m) return;
    umn(c, m);
    for (ll i = 0; i < b; i++) qr[i] = -1, ql[i] = 0;
    for (ll i = 0; i <= m; i++) {
        ll div = i / b, mod = i % b;
        ll curv = dp[i] - a * div;
        while (ql[mod] <= qr[mod] && q[mod][qr[mod]].se <= curv) --qr[mod];
        q[mod][++qr[mod]] = {div, curv};

        while (ql[mod] <= qr[mod] && q[mod][ql[mod]].fi < div - c) ++ql[mod];
        dp[i] = div * a + q[mod][ql[mod]].se;
    }
}
ll res[MXN][MXM];

void dfs(ll l, ll r) {
    if (l == r) {
        memcpy(res[l], dp, sizeof(dp));
        return;
    }
    ll bckup[MXN], mid = (l + r) >> 1;
    memcpy(bckup, dp, sizeof(dp));
    for (ll i = mid + 1; i <= r; i++) upd(arr[i], brr[i], crr[i]);
    dfs(l, mid);
    memcpy(dp, bckup, sizeof(dp));
    for (ll i = l; i <= mid; i++) upd(arr[i], brr[i], crr[i]);
    dfs(mid + 1, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("reflect.in", "r", stdin);
    freopen("reflect.out","w",stdout);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) cin >> arr[i];
    for (ll i = 1; i <= n; i++) cin >> brr[i];
    for (ll i = 1; i <= n; i++) cin >> crr[i];
    memset(dp, ~0x3f, sizeof(dp));
    dp[0] = 0;
    dfs(1, n);
    /* for (ll i = 1; i <= n; i++) { */
    /*     for (ll j = 0; j <= m; j++) cout << res[i][j] << " "; */
    /*     cout << nl; */
    /* } */
    ll q;
    cin >> q;
    while (q--) {
        ll x, a, b, c, ans = -INF;
        cin >> x >> a >> b >> c;
        for (ll i = 0; i <= m; i++) umx(ans, res[x][i] + min(c, (m - i) / b) * a);
        cout << ans << nl;
    }
    return 0;
}

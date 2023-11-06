// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
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
const ll MXN = 105;

int n, m;
ll x, y;
char arr[MXN][MXN];
ll row[MXN][MXN];
ll col[MXN][MXN];
ll dp[2][MXN][MXN][MXN];
ll rowsum(ll x, ll y, ll z) {
    if (z < y) return 0;
    return row[x][z] - row[x][y - 1];
}
ll colsum(ll x, ll y, ll z) {
    if (z < y) return 0;
    return col[z][x] - col[y - 1][x];
}
int main() {
    // freopen("1.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> (arr[i] + 1);
        for (ll j = 1; j <= m; j++) {
            if (arr[i][j] == 'E') x = i, y = j;
            row[i][j] = row[i][j - 1] + (arr[i][j] == 'o');
            col[i][j] = col[i - 1][j] + (arr[i][j] == 'o');
        }
    }
    ll ans = 0;
    for (ll i = 0; i <= n; i++) {
        ll ci = i & 1;
        memset(dp[!ci], 0, sizeof(dp[0]));
        for (ll j = 0; i + j <= n; j++) {
            for (ll k = 0; k <= m; k++) {
                for (ll l = 0; k + l <= m; l++) {
                    // cerr<<i<<' '<<j<<" "<<k<<" "<<l<<" "<<dp[ci][j][k][l]<<nl;
                    umx(ans, dp[ci][j][k][l]);
                    // i++,新增i+1行
                    ll add =
                        (x + i >= i + 1 && x - j <= i + 1) ? rowsum(i + 1, max(k + 1, y - l), min(m - l, y + k)) : 0;
                    umx(dp[!ci][j][k][l], dp[ci][j][k][l] + add);

                    // j--新增n-j行
                    add = (x + i >= n - j && x - j <= n - j) ? rowsum(n - j, max(k + 1, y - l), min(m - l, y + k)) : 0;
                    umx(dp[ci][j + 1][k][l], dp[ci][j][k][l] + add);

                    // k++, 新增k+1列
                    add = (y + k >= k + 1 && y - l <= k + 1) ? colsum(k + 1, max(i + 1, x - j), min(n - j, x + i)) : 0;
                    umx(dp[ci][j][k + 1][l], dp[ci][j][k][l] + add);

                    add = (y + k >= m - l && y - l <= m - l) ? colsum(m - l, max(i + 1, x - j), min(n - j, x + i)) : 0;
                    umx(dp[ci][j][k][l + 1], dp[ci][j][k][l] + add);
                }
            }
        }
    }
    cout << ans << nl;
    return 0;
}

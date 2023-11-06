#include <vector>
#pragma GCC optimize("Ofast", "-funroll-loops")
#pragma GCC target("sse4.1", "sse4.2", "ssse3", "sse3", "sse2", "sse", "avx2", "avx", "popcnt")
#include <bits/stdc++.h>

#include <cstring>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (63 - __builtin_clzll(x))
#define popc(x) __builtin_popcountll(x)
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ull, ll>;
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ Func
template <typename T1, typename T2>
pair<T1, T2> operator+(const pair<T1, T2> &x, const pair<T1, T2> &y) {
    return {x.fi + y.fi, x.se + y.se};
}
template <typename T1, typename T2>
pair<T1, T2> operator-(const pair<T1, T2> &x, const pair<T1, T2> &y) {
    return {x.fi - y.fi, x.se - y.se};
}
template <typename T1, typename T2>
pair<T1, T2> operator*(const pair<T1, T2> &x, const ll &y) {
    return {x.fi * y, x.se * y};
}
template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &y) {
    return is >> y.fi >> y.se;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &y) {
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
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T>
void umx(T &x, const T &y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, const T &y) {
    x = min(x, y);
}
ll abs(const pi &x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
bool insqr(const pi &x, const pi &lt, const pi &rb) {
    return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se;
}
ll ri(const ll &l, const ll &r) {
    uniform_int_distribution<ll> res(l, r);
    return res(mr);
}
ld rd(const ld &l, const ld &r) {
    uniform_real_distribution<ld> res(l, r);
    return res(mr);
}
void setp(const ll &x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void prt(T &x, const ll &l, const ll &r, const char *join = " ") {
    for (ll i = l; i <= r; i++) cout << x[i] << join;
}
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
}
//}}}
const char nl = '\n';
const ll MXN = 2505;
const ll INF = 1e18;
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const ull P = 131;

ll n, ind, A, B, C;
char str[MXN];
ull pw[MXN], h[MXN];
ull geth(ll l, ll r) { return h[r] - h[l - 1] * pw[r - l + 1]; }
ll dp[MXN][MXN];
int main() {
    /* freopen("copypaste.in", "r", stdin); */
    /* freopen("copypaste.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n >> (str + 1) >> A >> B >> C;
    pw[0] = 1;
    for (ll i = 1; i <= n; i++) {
        h[i] = h[i - 1] * P + str[i];
        pw[i] = pw[i - 1] * P;
    }
    memset(dp, 0x3f, sizeof(dp));

    for (ll i = n; i; i--)
        for (ll j = i; j <= n; j++) {
            if (j == i) dp[i][j] = A;
            umn(dp[i - 1][j], dp[i][j] + A);
            umn(dp[i][j + 1], dp[i][j] + A);
            ll c = dp[i][j] + B + C, last = j;
            ull ch = geth(i, j);
            for (ll k = j + 1; k <= n; k++) {
                c += A;
                if (k - j + i > last && geth(k - j + i, k) == ch) {
                    c -= A * (j - i + 1);
                    c += C;
                    last = k;
                    umn(dp[i][k], c);
                }
            }
        }
    cout << dp[1][n] << nl;
    return 0;
}

#include <cstdio>
#include <cstring>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

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
using pi = pair<ll, ll>;
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
const ll P = 1e9 + 7;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() : v() {}
    template <typename T>
    mod(const T &_v) : v(_v) {
        if (v >= P || v < 0) v = incr(v % P);
    }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod operator+(const mod &y) const { return mod{redu(v + y.v)}; }
    mod operator-(const mod &y) const { return mod{incr(v - y.v)}; }
    mod operator*(const mod &y) const { return mod{1ll * v * y.v % P}; }
    mod operator/(const mod &y) const { return mod{1ll * v * (ll)qpow(y, P - 2) % P}; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = 1ll * v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = 1ll * v * (ll)qpow(y, P - 2) % P, *this; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y = mod(x), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
//}}}
const char nl = '\n';
const ll MXN = 1e5 + 5;
const ll INF = 1e18, LG = 10, LIM = 300;
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ll n, m, dp[MXN][LG];
ll mnk[MXN][LG], lastbig[LG];
ll upd(ll i, ll j, ll k) {
    ll nxi = (i + k - 1) / k, mn = INF;
    bool f = k != 2;
    for (ll l = 0; l <= j - 1 - f; l++) {
        //正好边界,一边边界，两边边界，里面
        ll tmp = max({dp[k][l] + dp[nxi][j - l], dp[k - 1][l] + dp[nxi][j - 1 - l],
                      dp[k - 2][l] + dp[nxi][(j - 1 - f - l) / 2], dp[nxi][j]});
        umn(mn, tmp);
    }
    if (mn < dp[i][j]) {
        dp[i][j] = mn;
        mnk[i][j] = k;
    }
    return mn;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    /* freopen("test.in","r",stdin); */
    freopen("B.out", "w", stdout);
    /* cin >> n; */
    n = 3000;
    memset(dp, 0x3f, sizeof(dp));
    memset(dp[1], 0, sizeof(dp[1]));
    memset(dp[0], 0, sizeof(dp[1]));
    for (ll i = 2; i <= n; i++) {
        if (i % 1000 == 0) cerr << i << nl;
        for (ll j = 0; j < LG; j++) {
            //叉数
            dp[i][j] = i * (i + 1) / 2;
            if (j - i + 1 >= 0) dp[i][j] = 0;
            for (ll k = 2; k < i; k++) upd(i, j, k);
            cout << i << " " << j << " " << dp[i][j] << " " << mnk[i][j] << nl;
        }
    }
    for (ll i = 0; i < LG; i++) {
        cerr << i << " " << dp[n][i] << " " << mnk[n][i] << nl;
    }
    return 0;
}

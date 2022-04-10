// #pragma GCC optimize("Ofast", "-funroll-loops")
// #pragma GCC target("sse4.1", "sse4.2", "ssse3", "sse3", "sse2", "sse", "avx2", "avx", "popcnt")
#include <bits/stdc++.h>

#include <algorithm>
#include <numeric>
#include <vector>

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
const ll P = 1e9 + 7;
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

ll n, k;
vector<ll> arr, brr;

void upd(vector<vector<ll>> &x) {
    for (ll j = 1; j <= n; j++) umn(x[0][j], x[0][j - 1]);
    for (ll i = 1; i <= n; i++) {
        umn(x[i][i], x[i - 1][i]);
        for (ll j = i + 1; j <= n; j++) umn(x[i][j], min(x[i - 1][j], x[i][j - 1]));
    }
}
ll force() {
    vector<vector<ll>> cur(n + 1, vector<ll>(n + 1, INF)), nx(n + 1, vector<ll>(n + 1, INF));
    cur[0][0] = 0;
    for (ll l = 1; l <= k; l++) {
        upd(cur);
        fill(all(nx[0]), INF);
        for (ll i = 1; i <= n; i++) {
            nx[i][0] = INF;
            for (ll j = i; j <= n; j++) nx[i][j] = cur[i - 1][j - 1] + arr[i] + brr[j];
        }
        swap(cur, nx);
    }
    upd(cur);
    return cur[n][n];
}
ll A() {
    for (ll i = 1; i <= n; i++) arr[i] += brr[i];
    sort(1 + all(arr));
    return accumulate(arr.begin() + 1, arr.begin() + 1 + k, 0);
}

int main() {
    freopen("world.in", "r", stdin);
    freopen("world.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    arr.resize(n + 1);
    brr.resize(n + 1);
    generate(1 + all(arr), nxt<ll>);
    generate(1 + all(brr), nxt<ll>);
    if (n <= (ll)1e4 + 5)
        cout << force();
    else
        cout << A();
    return 0;
}

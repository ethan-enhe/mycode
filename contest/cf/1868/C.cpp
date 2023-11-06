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
const ll MXN = 1e6 + 5;

mod pw2[MXN];
ll n, m, arr[MXN];
ll dig;
// mod len[MXN];
// void cnt(ll a, ll b) {
//     // 前a位紧贴上限,接着b位公有(b为0特判)，然后一位区分，接下来随便了
//     if (a == 0)
//         return;
//     else if (b == 0) {
//         for (ll i = 1; a + i <= dig + 1; i++) {
//             len[i] += (a + i == dig + 1) ? (n & ((1ll << i) - 1)) % P : pw2[i];
//         }
//         if ((n & (1 << (dig - a))) == 1) {
//             for (ll i = 0; a + 1 + i <= dig + 1; i++) {
//                 mod tmp = (a + i == dig + 1) ? (n & ((1ll << i) - 1)) % P : pw2[i];
//                 for (ll j = 0; a + 1 + j <= dig + 1; j++) {
//                     len[i + j + 2] += tmp * pw2[j];
//                 }
//             }
//         }
//     } else {
//         if ((n & (1 << (dig - a))) == 0) return;
//         for (ll i = 0; a + b + 1 + i <= dig + 1; i++) {
//             for (ll j = 0; a + b + 1 + j <= dig + 1; j++) {
//                 len[i + j + 2] += pw2[i + j] * pw2[b - 1];
//             }
//         }
//         for (ll i = 1; a + b + i <= dig + 1; i++) len[i] += pw2[i] * pw2[b - 1];
//     }
// }
const ll LG = 70;
mod dp[LG][LG][3][3];
void solve() {
    dp[dig][0][0][0] = 1;
    for (ll i = dig; i; i--) {
        for (ll l = 0; l < LG; l++) {
            for (ll a = 0; a < 3; a++) {
                for (ll b = 0; b < 3; b++) {
                    for (ll x = 0; x < 2; x++)
                        for (ll y = 0; y < 2; y++) {
                        }
                }
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    pw2[0] = 1;
    for (ll i = 1; i < MXN; i++) pw2[i] = pw2[i - 1] * 2;
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        dig = 31 - __builtin_clz(n);
        // cout << dig;
        // for (ll i = 1; i < dig + 1; i++)
        //     for (ll j = 0; i + j <= dig + 1; j++) {
        //         cnt(i, j);
        //     }
        cnt(1, 1);
        for (ll i = 0; i <= dig * 2 + 5; i++) {
            cout << i << " " << len[i] << endl;
        }
    }
    return 0;
}

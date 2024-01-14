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
tpl T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
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
const ll INF = 3e18;
const ll MXN = 1e6 + 5;

ll n, A[2], arr[MXN];
mod dp[2][MXN], sum[2][MXN];
ll pre[2][MXN];
ll small_gap[2][MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    cin >> A[0] >> A[1];
    arr[0] = -INF, arr[n + 1] = INF;
    for (ll i = 1; i <= n + 1; i++) {
        if (i <= n) cin >> arr[i];
        auto calc = [&](bool f) {
            pre[f][i] = pre[f][i - 1];
            while (arr[i] - arr[pre[f][i] + 1] >= A[f]) ++pre[f][i];
            small_gap[f][i] = arr[i] - arr[i - 1] < A[f] ? i : small_gap[f][i - 1];
        };
        calc(0);
        calc(1);
    }
    dp[1][0] = dp[0][0] = sum[1][0] = sum[0][0] = (mod)1;
    auto psum = [&](bool f, ll i) -> mod {
        if (i == -1) return 0;
        return sum[f][i];
    };
    for (ll i = 1; i <= n; i++) {
        auto calc = [&](bool f) {
            ll jl = max(0ll, small_gap[f][i] - 1);
            ll jr = min(i - 1, pre[!f][i + 1]);
            if (jl <= jr) dp[f][i] = psum(!f, jr) - psum(!f, jl - 1);
            sum[f][i] = sum[f][i - 1] + dp[f][i];
        };
        calc(0);
        calc(1);
    }
    cout << dp[1][n] + dp[0][n];
    return 0;
}

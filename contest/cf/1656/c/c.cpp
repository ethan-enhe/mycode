// #pragma GCC optimize("Ofast", "-funroll-loops")
// #pragma GCC target("sse4.1", "sse4.2", "ssse3", "sse3", "sse2", "sse", "avx2", "avx", "popcnt")
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
    mod() {}
    template <typename T>
    mod(const T &_v) : v(_v) {}
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod operator+(const mod &y) const { return mod(redu(v + y.v)); }
    mod operator-(const mod &y) const { return mod(incr(v - y.v)); }
    mod operator*(const mod &y) const { return mod((ll)v * y.v % P); }
    mod operator/(const mod &y) const { return mod((ll)v * (ll)qpow(y, P - 2) % P); }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = (ll)v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = (ll)v * (ll)qpow(y, P - 2) % P, *this; }
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
const ll MXN = 1e6 + 5;
const ll INF = 1e18;

ll n, m, arr[MXN];
char str[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        bool f1 = 0;
        for (ll i = 1; i <= n; i++) {
            cin >> arr[i];
            if (arr[i] == 1) f1 = 1;
        }
        if (!f1)
            cout << "YES" << nl;
        else {
            bool f = 1;
            sort(arr + 1, arr + 1 + n);
            for (ll i = 1; i < n; i++)
                if (arr[i] + 1 == arr[i + 1]) f = 0;
            if (f)
                cout << "YES" << nl;
            else
                cout << "NO" << nl;
        }
    }

    return 0;
}

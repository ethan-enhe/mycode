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
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN], ord[MXN];
char ans[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    /* cin >> n; */
    for (ll i = 1; i <= 100; i++) {
        ll sum = 0;
        n = ri(1, 1e6);
        for (ll i = 1; i <= n; i++) {
            arr[i] = ri(1, 1e9);
            /* cin >> arr[i]; */
            ord[i] = i;
            sum += arr[i];
            ans[i] = 'Z';
        }
        sort(ord + 1, ord + 1 + n, [](ll x, ll y) { return arr[x] > arr[y]; });
        ll s1 = 0, last = 0;
        for (ll i = 1; i <= n; i++) {
            if ((s1 + arr[ord[i]]) * 2 < sum) {
                s1 += arr[ord[i]];
                ans[ord[i]] = 'B';
                last = i;
            } else
                break;
        }
        if (!last)
            cout << "Internationale!" << nl;
        else {
            ll s2 = 0, _last;
            for (_last = last + 1; _last <= n; _last++) {
                ll cur = arr[ord[_last]];
                if ((s2 + cur) * 2 > (sum - s1)) break;
                s2 += arr[ord[_last]];
                ans[ord[_last]] = 'Y';
            }
            ll s3 = sum - s2 - s1;
            if (s3 - s2 < s1) {
            } else {
                assert(s3 - s2 >= s1 && s3 - s2 < s1 * 2);
                if (s3 - s2 > s1) {
                    ans[ord[_last]] = 'Y';
                } else {
                    if (arr[ord[n]] < arr[ord[1]])
                        ans[ord[n]] = 'Y';
                    else {
                        ll tmp = n / 3;
                        for (ll i = 1; i <= tmp; i++) ans[i] = 'B';
                        for (ll i = tmp + 1; i <= tmp * 2; i++) ans[i] = 'Y';
                        for (ll i = tmp * 2 + 1; i <= n; i++) ans[i] = 'Z';
                    }
                }
            }
            s1 = s2 = s3 = 0;
            for (ll i = 1; i <= n; i++) {
                if (ans[i] == 'B')
                    s1 += arr[i];
                else if (ans[i] == 'Y')
                    s2 += arr[i];
                else
                    s3 += arr[i];
            }
            if (s1 + s2 > s3 && s2 + s3 > s1 && s1 + s3 > s2)
                cerr << "OK" << endl;
            else
                assert(0);
            /* cout << ans + 1; */
        }
    }
    return 0;
}

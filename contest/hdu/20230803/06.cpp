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

using ll = int;
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
const char nl = '\n';
const ll MXN = 300 * 300 + 5;
const int ZERO = 400;

ll n, m, arr[MXN];
bool f[MXN];
ll cnt[MXN];
void delt(ll l, ll r, ll k) {
    ll s = arr[r] - arr[l - 1];
    for (ll i = 1; i <= 300; i++) {
        if (abs(i * i - s) <= 300) {
            cnt[ZERO + i * i - s] += k;
        }
    }
    // cout<<l<<" "<<r<<" "<<k<<endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (ll i = 1; i * i < MXN; i++) f[i * i] = 1;
    ll t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) cin >> arr[i];
        ll mx = 0;
        ll ans = 0;
        for (ll i = 1; i <= n; i++) {
            arr[i] += arr[i - 1];
            for (ll j = i; j; j--) ans += f[arr[i] - arr[j - 1]];
        }
        for (ll i = 1; i <= n; i++) {
            for (ll j = i; j <= n; j++) delt(i, j, 1);
            for (ll j = 1; j <= i - 1; j++) delt(j, i - 1, -1);

            for (ll j = 1; j <= 300; j++) {
                umx(mx, cnt[j - arr[i] + arr[i - 1] + ZERO] - cnt[ZERO]);
                // if (cnt[j - arr[i] + arr[i - 1] + ZERO] - cnt[ZERO]==2) cout <<i<<" "<< j << endl;
            }
        }
        cout << mx + ans << nl;
    }
    return 0;
}

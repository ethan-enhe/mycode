// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <vector>
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

ll t, a1, b1, a2, b2, n;
struct opt {
    ll time, tp;
};
struct qry {
    ll dis, sum, sum1;
};
map<ll, qry> ans;

int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        ans.clear();
        cin >> a1 >> b1 >> a2 >> b2 >> n;
        ll loop = (a1 + b1) / __gcd(a1 + b1, a2 + b2) * (a2 + b2);
        vector<opt> arr;
        vector<ll> ask(n);
        for (ll i = 0; i < loop; i += a1 + b1) {
            arr.push_back({i, 1});
            arr.push_back({i + a1, 1});
        }
        for (ll i = 0; i < loop; i += a2 + b2) {
            arr.push_back({i, 2});
            arr.push_back({i + a2, 2});
        }
        for (ll &i : ask) {
            cin >> i;
            arr.push_back({(i - 1) % loop + 1, 0});
        }
        sort(all(arr), [](auto x, auto y) { return x.time < y.time; });
        ll tp1 = 0, tp2 = 0, dis = 0, sum = 0;
        ll sum1 = 0;
        for (ll i = 0; i < arr.size(); i++) {
            if (arr[i].tp == 0) {
                ans[arr[i].time] = {dis, sum, sum1};
                // cerr << arr[i].time << " "
                // << " " << sum1 << dis << endl;
            } else {
                if (arr[i].tp == 1)
                    tp1 = !tp1;
                else
                    tp2 = !tp2;
            }
            if (i + 1 < arr.size()) {
                sum1 += tp1 * (arr[i + 1].time - arr[i].time);
                dis = max(0ll, dis + (tp1 - tp2) * (arr[i + 1].time - arr[i].time));
                sum = sum + (tp1 - tp2) * (arr[i + 1].time - arr[i].time);
            }
        }
        for (ll &i : ask) {
            ll tmp = (i - 1) % loop + 1;
            qry res = ans[tmp];
            ll cnt = (i - tmp) / loop;
            if (cnt) {
                umx(res.dis, res.sum + dis);
                umx(res.dis, res.sum + dis + sum * (cnt - 1));
            }
            // cerr << res.sum1 + cnt * sum1 << " " << res.dis << nl;
            cout << res.sum1 + cnt * sum1 - res.dis << nl;
        }
    }
    return 0;
}

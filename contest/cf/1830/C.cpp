// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <stack>
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

ll n, m;
pi arr[MXN];
set<ll> stk[MXN];
set<ll> not_calc;
mod fac[MXN], ifac[MXN];
mod comb(ll x, ll y) {
    if (y > x || y < 0) return 0;
    return fac[x] * ifac[x - y] * ifac[y];
}
mod ans(ll len) {
    if (len & 1) return 0;
    return comb(len, len / 2) - comb(len, len / 2 + 1);
}
mod res;
void calc(set<ll> &x) {
    ll last = -1;
    for (auto &i : x) {
        if (last != -1) {
            ll cnt = 0;
            while (1) {
                auto it = not_calc.upper_bound(last);
                if (it == not_calc.end() || *it > i)
                    break;
                else {
                    last = *it;
                    not_calc.erase(it);
                }
                ++cnt;
            }
            res = res * ans(cnt);
            // cout << i << cnt << " ";
        }
        last = i;
    }
    x.clear();
    // cout << nl;
}
void mrg(set<ll> &x, set<ll> &y) {
    if (y.size() > x.size()) swap(x, y);
    for (auto &i : y) x.insert(i);
    y.clear();
}
int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    stk[0].insert(-INF);
    stk[0].insert(INF);
    fac[0] = ifac[0] = 1;
    for (ll i = 1; i < MXN; i++) {
        fac[i] = fac[i - 1] * i;
        ifac[i] = (mod)1 / fac[i];
    }
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        // cout << "!!!" << n << " " << m << endl;
        not_calc.clear();
        for (ll i = 1; i <= n; i++) not_calc.insert(i);
        for (ll i = 1; i <= m; i++) {
            cin >> arr[i].first >> arr[i].second;
            --arr[i].first;
        }
        arr[++m] = {0, n};
        sort(arr + 1, arr + 1 + m);
        ll top = 0;
        res = 1;
        for (ll i = 1; i <= m; i++) {
            auto it = stk[top].lower_bound(arr[i].first);
            while (it == stk[top].end()) { // 结束
                calc(stk[top]);
                stk[top].clear();
                --top;
                it = stk[top].lower_bound(arr[i].first);
            }
            if (*it > arr[i].second) {
                ++top;
                stk[top].insert(arr[i].first);
                stk[top].insert(arr[i].second);
            } else if (*it <= arr[i].second) {
                stk[top].insert(arr[i].first);
                stk[top].insert(arr[i].second);
                while (1) {
                    auto it = stk[top - 1].lower_bound(arr[i].first);
                    if (*it <= arr[i].second)
                        mrg(stk[top - 1], stk[top]), --top;
                    else
                        break;
                }
            }
            // cerr << i << top << endl;
        }
        while (top) calc(stk[top--]);
        cout << res << nl;
        // cout<<endl;
    }
    return 0;
}

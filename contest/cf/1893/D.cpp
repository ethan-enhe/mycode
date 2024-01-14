// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstdio>
#include <numeric>
#include <queue>
#include <stack>
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

ll n, m, arr[MXN], s[MXN], d[MXN], ds[MXN];
ll cnt[MXN], col[MXN];
vector<ll> distr[MXN];
struct cmp {
    bool operator()(ll x, ll y) { return (ld)s[x] / d[x] < (ld)s[y] / d[y]; }
};
priority_queue<ll, vector<ll>, cmp> q;

ll tcnt[MXN];
void solve(vector<ll> &x, ll d) {
    for (auto &i : x) tcnt[i]++;
    sort(all(x), [](ll x, ll y) {
        if (tcnt[x] == tcnt[y]) return x < y;
        return tcnt[x] > tcnt[y];
    });
    vector<ll> tmp(x.size()), res(x.size());
    iota(all(tmp), 0);
    sort(all(tmp), [&](ll x, ll y) {
        if (x % d == y % d) return x > y;
        return x % d < y % d;
    });
    for (ll i = 0; i < x.size(); i++) {
        res[tmp[i]] = x[i];
    }
    for (auto &i : res) cout << i << " ";
    cout << nl;
}

int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        // cout << t << endl;
        while (!q.empty()) {
            q.pop();
        }
        cin >> n >> m;
        for (ll i = 1; i <= n; i++) arr[i] = 0;
        for (ll i = 1; i <= n; i++) {
            ll x;
            cin >> x;
            ++arr[x];
        }
        for (ll i = 1; i <= m; i++) {
            cin >> s[i];
        }
        for (ll i = 1; i <= m; i++) {
            cin >> d[i];
            ds[i] = d[i];
            d[i] = (s[i] - 1) / d[i] + 1;
            q.push(i);
            distr[i].clear();
            col[i] = -1;
        }
        bool f = 1;
        stack<ll> tmp;
        for (ll i = 1; i <= n; i++) {
            // cout << t << " " << i << endl;
            while (arr[i]--) {
                // cout<<arr[i]<<endl;
                if (q.empty()) {
                    f = 0;
                    break;
                }
                ll x = q.top();
                // cout << i << "->" << x << " " << (ld)s[x] / d[x] << endl;
                q.pop();
                if (!s[x]) {
                    f = 0;
                    break;
                }
                if (col[x] != i) cnt[x] = 0;
                col[x] = i;
                ++cnt[x];
                --s[x];
                distr[x].push_back(i);
                if (cnt[x] == d[x]) {
                    tmp.push(x);
                } else
                    q.push(x);
            }
            // cerr << n << " " << q.size() << endl;
            if (!f) break;
            while (!tmp.empty()) {
                q.push(tmp.top());
                tmp.pop();
            }
        }
        if (!f)
            cout << "-1" << nl;
        else {
            for (ll i = 1; i <= m; i++) solve(distr[i], ds[i]);
            // cout << "yes" << nl;
        }
    }
    return 0;
}

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
const ll MXN = 4005;

ll n, m, arr[MXN];
char str[MXN][MXN];
bool vis[MXN];
vector<ll> connect;
void dfs(ll p) {
    if (vis[p]) return;
    vis[p] = 1;
    connect.push_back(p);
    for (ll nx = 1; nx <= n; nx++)
        if (str[p][nx] == '1') dfs(nx);
}
ll _dfs(ll p, ll ban) {
    if (p == ban || vis[p]) return 0;
    vis[p] = 1;
    ll sum = 1;
    for (ll nx = 1; nx <= n; nx++)
        if (str[p][nx] == '1') sum += _dfs(nx, ban);
    return sum;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll task;
    cin >> task;
    while (task--) {
        ll not_tuan_i = -1;
        ll mn_tuan = INF, mn_tuan_i;
        ll lastlast_tuan, last_tuan;
        ll cnt = 0;
        cin >> n;
        for (ll i = 1; i <= n; i++) {
            cin >> (str[i] + 1);
            vis[i] = 0;
        }
        for (ll i = 1; i <= n; i++)
            if (!vis[i]) {
                ++cnt;
                connect.clear();
                dfs(i);
                bool f = 1;
                for (ll i = 0; i < connect.size(); i++) {
                    for (ll j = i + 1; j < connect.size(); j++) {
                        if (str[connect[i]][connect[j]] != '1') {
                            not_tuan_i = connect[i];
                            f = 0;
                            break;
                        }
                    }
                    if (!f) break;
                }
                if (f) {
                    last_tuan = lastlast_tuan, lastlast_tuan = i;
                    if (connect.size() < mn_tuan) {
                        mn_tuan = connect.size();
                        mn_tuan_i = i;
                    }
                }
            }
        if (cnt == 1)
            cout << 0 << nl;
        else if (not_tuan_i != -1) {
            for (ll i = 1; i <= n; i++) vis[i] = 0;
            connect.clear();
            dfs(not_tuan_i);
            for (ll i = 0; i < connect.size(); i++) {
                // if (i % 100 == 0) cerr << i << endl;
                ll s = i ? connect[0] : connect[1];
                for (auto &j : connect) vis[j] = 0;
                if (_dfs(s, connect[i]) + 1 == connect.size()) {
                    cout << 1 << " " << connect[i] << nl;
                    break;
                }
            }
        } else {
            if (mn_tuan == 1)
                cout << 1 << " " << mn_tuan_i << nl;
            else if (cnt >= 3)
                cout << 2 << " " << last_tuan << " " << lastlast_tuan << nl;
            else {
                connect.clear();
                for (ll i = 1; i <= n; i++) vis[i] = 0;
                dfs(mn_tuan_i);
                cout << connect.size() << " ";
                for (auto &i : connect) cout << i << " ";
                cout << nl;
            }
        }
    }
    return 0;
}

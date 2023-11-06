#include <bits/stdc++.h>

#include <cstddef>
#include <cstring>
#include <vector>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
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
ll randint(const ll &l, const ll &r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(const ld &l, const ld &r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
void setp(const ll &x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void read(T &x, const ll &l, const ll &r) {
    for (ll i = l; i <= r; i++) cin >> x[i];
}
template <typename T>
void prt(T &x, const ll &l, const ll &r, const char &join = ' ') {
    for (ll i = l; i <= r; i++) cout << x[i] << join;
}
//}}}
const ll P = 1e9 + 7;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() : v() {}
    template <typename T>
    mod(const T &_v) : v(_v) {
        if (v >= P || v < 0) v = incr(v % P);
    }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod operator+(const mod &y) const { return mod{redu(v + y.v)}; }
    mod operator-(const mod &y) const { return mod{incr(v - y.v)}; }
    mod operator*(const mod &y) const { return mod{1ll * v * y.v % P}; }
    mod operator/(const mod &y) const { return mod{1ll * v * (ll)qpow(y, P - 2) % P}; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = 1ll * v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = 1ll * v * (ll)qpow(y, P - 2) % P, *this; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y = mod(x), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
//}}}
const ll INF = 1e18;
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const char nl = '\n';
const ll MXN = 6e3 + 5;

ll n, m, ask;
ll deg[MXN];
vector<ll> g[MXN], domi[MXN];
bool vis[MXN];
ll q[MXN], ql, qr;
void cal(ll x) {
    memset(vis, 0, sizeof(vis));
    vis[x] = 1;
    q[ql = qr = 1] = 1;
    while (ql <= qr) {
        ll p = q[ql++];
        if (vis[p]) continue;
        vis[p] = 1;
        for (ll nx : g[p]) q[++qr] = nx;
    }
    for (ll i = 1; i <= n; i++)
        if (!vis[i]) {
            domi[x].push_back(i);
            ++deg[i];
        }
}
ll sum[MXN], fa[MXN];
bool f[MXN];
void bld() {
    q[ql = qr = 1] = 1;
    while (ql <= qr) {
        ll p = q[ql++];
        for (ll nx : domi[p])
            if (!(--deg[nx])) {
                cout << p << " " << nx << endl;
                fa[nx] = p;
                q[++qr] = nx;
            }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n >> m >> ask;
    while (m--) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    for (ll i = 1; i <= n; i++) cal(i);
    bld();
    while (ask--) {
        ll u, v;
        cin >> u >> v;
        memset(sum, 0, sizeof(sum));
        ++sum[u], ++sum[v];
        for (ll i = n; i; i--) {
            ll p = q[i];
            sum[fa[p]] += sum[p];
        }
        ll cnt = 0;
        for (ll i = n; i; i--) {
            ll p = q[i];
            f[p] = (sum[p] == 1) && (u != fa[p] && v != fa[p]);
        }
        for (ll i = 1; i <= n; i++) {
            ll p = q[i];
            f[p] |= f[fa[p]];
            cnt += f[p];
        }
        cout << cnt << nl;
    }
    return 0;
}

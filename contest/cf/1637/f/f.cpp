#include <bits/stdc++.h>

#include <numeric>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define vec vector
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

struct mod;

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ Func
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
istream &operator>>(istream &is, pi &y) { return is >> y.fi >> y.se; }
ostream &operator<<(ostream &os, pi &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
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
void umx(T &x, T y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, T y) {
    x = min(x, y);
}
ll abs(pi x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
bool insqr(pi x, pi lt, pi rb) { return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se; }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
void setp(ll x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void read(T &x, int l, int r) {
    for (int i = l; i <= r; i++) cin >> x[i];
}
template <typename T>
void prt(T &x, int l, int r, char join = ' ') {
    for (int i = l; i <= r; i++) cout << x[i] << join;
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
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const char nl = '\n';
const ll MXN = 1e6 + 5;
const ll INF = 1e18;

ll n, m, arr[MXN];
vec<ll> g[MXN];

struct mymx {
    ll x, xid, y, yid;
    mymx() { x = y = 0; }
    void upd(ll v, ll id = -2) {
        if (v > x) {
            y = x, yid = xid;
            x = v, xid = id;
        } else if (v > y)
            y = v, yid = id;
    }
    ll get(ll excl = -1) { return excl == xid ? y : x; }
};

ll dfn[MXN], dfnc, sz[MXN];
ll mx_in[MXN], mx_out[MXN];
void dfs1(ll p, ll fa) {
    dfn[p] = ++dfnc;
    sz[p] = 1;
    mx_in[p] = arr[p];
    for (ll nx : g[p])
        if (nx != fa) {
            dfs1(nx, p);
            sz[p] += sz[nx];
            umx(mx_in[p], mx_in[nx]);
        }
}
ll diff[MXN];
void add(ll l, ll r, ll v) {
    diff[l] += v;
    diff[r + 1] -= v;
}
void dfs2(ll p, ll fa) {
    mymx mx;
    mx.upd(mx_out[p], fa);
    for (ll nx : g[p])
        if (nx != fa) mx.upd(mx_in[nx], nx);
    for (ll nx : g[p])
        if (nx != fa) {
            mx_out[nx] = max(arr[p], mx.get(nx));
            dfs2(nx, p);
        }
    // solve
    add(dfn[p], dfn[p], max(0ll, arr[p] - mx.get()));
    ll tmp = max(0ll, arr[p] - mx.get(fa));
    add(1, n, tmp);
    add(dfn[p], dfn[p] + sz[p] - 1, -tmp);
    for (ll nx : g[p])
        if (nx != fa) {
            ll tmp = max(0ll, arr[p] - mx.get(nx));
            add(dfn[nx], dfn[nx] + sz[nx] - 1, tmp);
        }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n;
    read(arr, 1, n);
    for (int i = 1; i < n; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    mx_out[1] = 0;
    dfs2(1, 0);
    /* prt(mx_in, 1, n); */
    /* cout << nl; */
    /* prt(mx_out, 1, n); */
    /* cout << nl; */
    partial_sum(diff + 1, diff + 1 + n, diff + 1);
    ll ans = INF;
    for (int i = 1; i <= n; i++) umn(ans, diff[i] + mx_in[1]);
    cout << ans << endl;
    return 0;
}

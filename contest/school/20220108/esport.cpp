#include <bits/stdc++.h>

#include <vector>
using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back

#ifdef ONLINE_JUDGE
#define log(fmt...) void()
#else
#define log(fmt...) fprintf(stderr, fmt)
#endif

#define va2d(x, y) x[(y.fi)][(y.se)]

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
const ll INF = 1e18;
const ll P = 1e9 + 7;
const ll MXN = 5e5 + 5, LG = 31 - __builtin_clz(MXN);
//{{{ Func
ll redu(const ll &x) {
    if (x < P) return x;
    if (x < (P << 1)) return x - P;
    return x % P;
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
void umx(T &x, T y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, T y) {
    x = min(x, y);
}
ll abs(pi x) { return abs(x.fi) + abs(x.se); }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
//}}}
//{{{ Type
const pi go[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
struct mll {
    ll v;
    explicit mll(ll _v = 0) : v(_v) {}
    explicit operator ll() const { return v; }
    mll operator+(const mll &y) const { return mll(redu(v + y.v)); }
    mll operator-(const mll &y) const { return mll(redu(P + v - y.v)); }
    mll operator*(const mll &y) const { return mll(redu(v * y.v)); }
    mll operator/(const mll &y) const { return mll(redu(v * (ll)qpow(y, P - 2))); }
    mll &operator=(const mll &y) { return v = y.v, *this; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = redu(v * y.v), *this; }
    mll &operator/=(const mll &y) { return v = redu(v * (ll)qpow(y, P - 2)), *this; }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
};
mll ltm(const ll &x) { return mll(redu(x % P + P)); }
template <typename T>
struct myvec {
    T *v;
    int sz, dsz;
    myvec() { v = NULL, sz = dsz = 0; }
    ~myvec() { free(v); }
    operator T *() const { return v; }
    T *begin() { return v; }
    T *end() { return v + sz; }
    void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
    void pb(T x) {
        if (sz == dsz) v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
        v[sz++] = x;
    }
    void fill(T x) {
        for (int i = 0; i < sz; i++) v[i] = x;
    }
};
//}}}
ll n, m;
ll tmp[MXN], w[MXN], ans;
vector<ll> g[MXN];
struct fwt {
    ll data[MXN];
    void mod(ll x, ll y) {
        for (; x <= n; x += x & (-x)) data[x] += y;
    }
    ll pre(ll x) {
        ll r = 0;
        for (; x; x ^= x & (-x)) r += data[x];
        return r;
    }
} anc, cnt;
ll fa[MXN][LG + 1], dpth[MXN], dfn[MXN], sz[MXN], id[MXN], dfnc;
void dfs(ll p) {
    ++dpth[p], sz[p] = 1;
    id[dfn[p] = ++dfnc] = p;
    for (ll i = 1; i < LG; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (ll nx : g[p])
        if (nx != fa[p][0]) {
            fa[nx][0] = p;
            dpth[nx] = dpth[p];
            dfs(nx);
            sz[p] += sz[nx];
        }
}
void modw(ll x, ll y) {
    ll _cnt = cnt.pre(dfn[x] + sz[x] - 1) - cnt.pre(dfn[x] - 1), delt = y - w[x];
    if (_cnt) ans += delt;
    anc.mod(dfn[x], delt);
    anc.mod(dfn[x] + sz[x], -delt);
    w[x] = y;
}
ll lca(ll x, ll y) {
    if (dpth[x] < dpth[y]) swap(x, y);
    ll tmp = dpth[x] - dpth[y];
    for (ll i = LG; ~i; i--)
        if ((tmp >> i) & 1) x = fa[x][i];
    if (x == y) return x;
    for (ll i = LG; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
ll lca(ll x, ll y, ll z) {
    ll a = lca(x, y), b = lca(y, z);
    return dpth[a] > dpth[b] ? a : b;
}
set<ll> q;
void add(ll p) {
    auto cur = q.insert(dfn[p]).fi, pre = cur, suf = cur;
    --pre, ++suf;
    ll _lca = lca(id[*pre], id[*cur], id[*suf]);
    ans += anc.pre(dfn[p]) - anc.pre(dfn[_lca]);
	cnt.mod(dfn[p],1);
}
void del(ll p) {
    auto cur = q.find(dfn[p]), pre = cur, suf = cur;
    --pre, ++suf;
    ll _lca = lca(id[*pre], id[*cur], id[*suf]);
    ans -= anc.pre(dfn[p]) - anc.pre(dfn[_lca]);
    q.erase(cur);
	cnt.mod(dfn[p],-1);
}

int main(int argc, char *argv[]) {
    freopen("esport.in", "r", stdin);
    freopen("esport.out","w",stdout);
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) scanf("%lld", tmp + i);
    for (ll i = 1; i < n; i++) {
        ll u, v;
        scanf("%lld%lld", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    for (ll i = 1; i <= n; i++) modw(i, tmp[i]);
    // for (ll i = 1; i <= n; i++) printf("%lld %lld %lld\n", i, dfn[i], anc.pre(dfn[i]));
    q.insert(0);
    q.insert(n + 1);
    scanf("%lld", &m);
    for (ll i = 1; i <= m; i++) {
        ll tmp;
        scanf("%lld", &tmp);
        add(tmp);
    }
    printf("%lld\n", ans);
    scanf("%lld", &m);
    while (m--) {
        ll opt, x, y;
        scanf("%lld%lld", &opt, &x);
        if (opt == 1)
            add(x);
        else if (opt == 2)
            del(x);
        else {
            scanf("%lld", &y);
            modw(x, y);
        }
		printf("%lld\n", ans);
    }
    return 0;
}

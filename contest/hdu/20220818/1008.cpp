#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <iterator>
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
const char nl = '\n';
const ll MXN = 1e5 + 5, LG = 17;

ll n, m;
vector<ll> g[MXN];
ll anc[MXN][LG + 1], dpth[MXN];
pi e[MXN];
void dfs(ll p, ll f) {
    anc[p][0] = f, dpth[p] = dpth[f] + 1;
    for (ll i = 0; anc[p][i]; i++) anc[p][i + 1] = anc[anc[p][i]][i];
    for (ll nx : g[p])
        if (nx ^ f) dfs(nx, p);
}
inline ll lca(ll x, ll y) {
    if (dpth[x] < dpth[y]) swap(x, y);
    ll tmp = dpth[x] - dpth[y];
    for (ll i = LG; ~i; i--)
        if ((tmp >> i) & 1) x = anc[x][i];
    if (x == y) return x;
    for (ll i = LG; ~i; i--)
        if (anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}
inline ll dis(ll x, ll y) { return dpth[x] + dpth[y] - dpth[lca(x, y)] * 2; }

struct node {
    ll x, y, d, fa;
} rt[MXN];
ll find(ll x) {
    while (rt[x].fa != x) x = rt[x].fa = rt[rt[x].fa].fa;
    return x;
}
pair<pi, ll> getmax(ll a, ll b, ll c, ll d) {
    ll res = -1;
    pi pr;
    auto upd = [&](ll x, ll y) {
        ll tmp = dis(x, y);
        if (tmp > res) {
            res = tmp;
            pr = {x, y};
        }
    };
    upd(a, b);
    upd(a, c);
    upd(a, d);
    upd(b, c);
    upd(b, d);
    upd(c, d);
    return {pr, res};
}
set<pi> d;
ll inner_d;
void merge(ll x, ll y) {
    x = find(x), y = find(y);
    pair<pi, ll> res = getmax(rt[x].x, rt[x].y, rt[y].x, rt[y].y);
    d.erase({rt[x].d, x});
    d.erase({rt[y].d, y});
    rt[y].fa = x;
    rt[x].d = res.se;
    rt[x].x = res.fi.fi;
    rt[x].y = res.fi.se;
    d.insert({rt[x].d, x});
    umx(inner_d, res.se);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        inner_d = 0;
        d.clear();
        cin >> n >> m;
        for (ll i = 1; i <= n; i++) {
            dpth[i] = 0;
            g[i].clear();
            rt[i].x = rt[i].y = rt[i].fa = i;
            rt[i].d = 0;
            d.insert({0, i});
            memset(anc[i],0,sizeof(anc[i]));
        }
        for (ll i = 1; i <= m; i++) {
            cin >> e[i];
            g[e[i].fi].push_back(e[i].se);
            g[e[i].se].push_back(e[i].fi);
        }
        for (ll i = 1; i <= n; i++)
            if (!dpth[i]) dfs(i, 0);
        for (ll i = 1; i <= m; i++) {
            ll u = e[i].fi, v = e[i].se;
            merge(u, v);
            ll ans = inner_d;
            if (d.size() >= 2) {
                auto back = d.rbegin();
                auto back1 = next(back);
                umx(ans, (back->first + 1) / 2 + (back1->first + 1) / 2 + 1);
                if (d.size() >= 3) {
                    auto back2 = next(back1);
                    umx(ans, (back2->first + 1) / 2 + (back1->first + 1) / 2 + 2);
                }
            }
            cout << ans << nl;
        }
    }
    return 0;
}

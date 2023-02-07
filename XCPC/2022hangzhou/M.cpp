#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
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
tpl void umx(T &x, const T &y) { x = max(x, y); }
tpl void umn(T &x, const T &y) { x = min(x, y); }
//}}}
const ll P = 1e9 + 7;
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 2e6 + 5;

ll n, m, arr[MXN];
ll dpth[MXN];
ll spec[MXN];
ll dfl[MXN], dfr[MXN], rev[MXN], dfnc;
ll t1 = 0;

#define ls (p << 1)
#define rs (p << 1 | 1)
struct node {
    ll g, s, len, ss;
    node(ll g = 0, ll s = 0, ll len = 0, ll ss = 0) : g(g), s(s), len(len), ss(ss) {}
    node operator+(const node &y) const { return {__gcd(g, y.g), s + y.s, len + y.len, ss + y.ss + s * y.len}; }
} t[MXN];
void pull(ll p) { t[p] = t[ls] + t[rs]; }
void build(ll p = 1, ll l = 1, ll r = m) {
    if (l == r) {
        ll cd = dpth[rev[spec[l]]] - dpth[rev[spec[l - 1]]];
        if (l == 1) {
            t1 = cd;
        } else
            t[p] = {cd, cd, 1, cd};
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pull(p);
    // cerr << l << " " << r << " " << t[p].ss << nl;
}
void mod(ll mi, ll md, ll p = 1, ll l = 1, ll r = m) {
    if (mi < l || mi > r) return;
    if (l == r) {
        t[p].g += md;
        t[p].s += md;
        t[p].ss += md;
        return;
    }
    ll mid = (l + r) >> 1;
    mod(mi, md, ls, l, mid);
    mod(mi, md, rs, mid + 1, r);
    pull(p);
}

void add(ll l, ll r, ll d) {
    l = lower_bound(spec + 1, spec + 1 + m, l) - spec;
    r = upper_bound(spec + 1, spec + 1 + m, r) - spec - 1;
    if (l <= r) {
        if (l == 1) {
            t1 += d;
        } else
            mod(l, d);
        mod(r + 1, -d);
    }
}
ll qry() {
    // cerr << t[1].ss << " " << t[1].g << endl;
    ll ss = t[1].ss + t1 * m;
    ll g = abs(__gcd(t1, t[1].g));
    return ss ? ss / g : 0;
}
vector<pi> g[MXN];

void init(ll p, ll fa) {
    dfl[p] = ++dfnc;
    rev[dfnc] = p;
    for (auto nx : g[p])
        if (nx.fi != fa) {
            dpth[nx.fi] = dpth[p] + nx.se;
            init(nx.fi, p);
        }
    dfr[p] = dfnc;
}
ll mn = INF;
void dfs(ll p, ll fa) {
    // cerr << p << ": ";
    umn(mn, qry());
    for (auto nx : g[p])
        if (nx.fi != fa) {
            add(1, n, nx.se);
            add(dfl[nx.fi], dfr[nx.fi], -nx.se * 2);
            dfs(nx.fi, p);
            add(1, n, -nx.se);
            add(dfl[nx.fi], dfr[nx.fi], nx.se * 2);
        }
}
int main() {
    // freopen("test.out", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= m; i++) cin >> spec[i];
    for (ll i = 1; i < n; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    init(1, 0);
    for (ll i = 1; i <= m; i++) spec[i] = dfl[spec[i]];
    sort(spec + 1, spec + m + 1);
    build();
    // qry();
    dfs(1, 0);
    cout << mn * 2 << nl;
    // qry();

    // for (auto &i : spec) cerr << i << endl;

    // while (n--) {
    //     ll a, b, c;
    //     cin >> a >> b >> c;
    //     add(a, b, c);
    //     cout << qry() << endl;
    // }
    return 0;
}

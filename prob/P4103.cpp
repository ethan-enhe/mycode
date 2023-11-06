#include <bits/stdc++.h>
using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())

using ll = long long;
using pi = pair<ll, ll>;
//}}}
//{{{ Func
template <typename T>
void umx(T &x, const T &y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, const T &y) {
    x = min(x, y);
}
//}}}
const int BS = 1 << 20;
char ibuf[BS], *ip1 = ibuf, *ip2 = ibuf;
#define gc() (ip1 == ip2 && (ip2 = (ip1 = ibuf) + fread(ibuf, 1, BS, stdin), ip1 == ip2) ? EOF : *ip1++)
ll nxt() {
    bool f = 0;
    ll x = 0;
    char c;
    while (c = gc(), !isdigit(c))
        if (c == '-') f = 1;
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
    return f ? -x : x;
}
const ll INF = 1e18;
const char nl = '\n';
const ll MXN = 1e6 + 5;

typedef ll arrn[MXN];
ll n, m, k, dfnc;
arrn fa, sz, dpth;
arrn dfn, top, son;
vec<ll> g[MXN];
void csz(const ll &p) {
    sz[p] = 1;
    for (ll nx : g[p])
        if (nx != fa[p]) {
            dpth[nx] = dpth[p] + 1;
            fa[nx] = p;
            csz(nx);
            sz[p] += sz[nx];
            if (sz[nx] > sz[son[p]]) son[p] = nx;
        }
}
void ctop(const ll &p) {
    dfn[p] = ++dfnc;
    if (son[p]) {
        top[son[p]] = top[p];
        ctop(son[p]);
        for (ll nx : g[p])
            if (nx != fa[p] && nx != son[p]) {
                top[nx] = nx;
                ctop(nx);
            }
    }
}
ll lca(ll x, ll y) {
    while (top[x] != top[y]) {
        if (dpth[top[y]] > dpth[top[x]]) swap(x, y);
        x = fa[top[x]];
    }
    return dpth[x] < dpth[y] ? x : y;
}

bool cmp(const ll &x, const ll &y) { return dfn[x] < dfn[y]; }

bool vis[MXN];
ll mnd, mxd, sum;
struct res {
    ll mn, mx, sz;
};
res cal(const ll &p) {
    res cr = {INF, -INF, vis[p]};
    for (ll nx : g[p]) {
        res nr = cal(nx);
        ll dis = dpth[nx] - dpth[p];

        umn(mnd, cr.mn + nr.mn + dis);
        umx(mxd, cr.mx + nr.mx + dis);
        sum += dis * nr.sz * (k - nr.sz);

        umn(cr.mn, nr.mn + dis);
        umx(cr.mx, nr.mx + dis);
        cr.sz += nr.sz;
    }
    if (vis[p]) {
        umn(mnd, cr.mn);
        umx(mxd, cr.mx);
        umn(cr.mn, 0ll);
        umx(cr.mx, 0ll);
    }
    g[p].clear();
    vis[p] = 0;
    return cr;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    n = nxt();
    for (ll i = 1, u, v; i < n; i++) {
        u = nxt(), v = nxt();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    top[1] = 1;
    csz(1);
    ctop(1);
    m = nxt();
    for (ll i = 1; i <= n; i++) g[i].clear();
    while (m--) {
        k = nxt();
        vec<ll> ask(k);
        for (ll &x : ask) vis[x = nxt()] = 1;
        sort(all(ask), cmp);
        for (ll i = 0; i < k - 1; i++) ask.push_back(lca(ask[i], ask[i + 1]));
        sort(all(ask), cmp);
        unq(ask);
        for (ll i = 1; i < ask.size(); i++) {
            ll l = lca(ask[i], ask[i - 1]);
            if (l != ask[i]) g[l].push_back(ask[i]);
        }
        mnd = INF, mxd = -INF, sum = 0;
        cal(ask[0]);
        cout << sum << " " << mnd << " " << mxd << nl;
    }
    return 0;
}

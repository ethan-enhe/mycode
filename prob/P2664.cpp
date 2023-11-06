#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MXN = 1e5 + 5;
ll n, c[MXN];
vector<ll> g[MXN];

bool vis[MXN];
ll sz[MXN];
void dfssz(ll p, ll fa) {
    sz[p] = 1;
    for (ll nx : g[p])
        if (!vis[nx] && nx != fa) {
            dfssz(nx, p);
            sz[p] += sz[nx];
        }
}
ll dfsrt(ll p, ll fa, ll tot) {
    bool f = (sz[p] << 1) >= tot;
    for (ll nx : g[p])
        if (!vis[nx] && nx != fa) {
            ll nxr = dfsrt(nx, p, tot);
            if (nxr) return nxr;
            f &= (sz[nx] << 1) <= tot;
        }
    return f ? p : 0;
}

ll instk[MXN], ans[MXN];
//到根路径上有这个颜色的节点数
ll hasc[MXN], curans;
void dfsm(ll p, ll fa, ll tp) {
    if (!instk[c[p]]++) {
        hasc[c[p]] += tp * sz[p];
        curans += tp * sz[p];
    }
    for (ll nx : g[p])
        if (!vis[nx] && nx != fa) dfsm(nx, p, tp);
    --instk[c[p]];
}
void dfsq(ll p, ll fa, ll outofsubt) {
    if (!instk[c[p]]++) curans += outofsubt - hasc[c[p]];
    ans[p] += curans;
    for (ll nx : g[p])
        if (!vis[nx] && nx != fa) dfsq(nx, p, outofsubt);
    if (!--instk[c[p]]) curans -= outofsubt - hasc[c[p]];
}
void dfz(ll p) {
    dfssz(p, 0);
    p = dfsrt(p, 0, sz[p]);
    vis[p] = 1;
    dfssz(p, 0);

    instk[c[p]] = 1;
    for (ll nx : g[p])
        if (!vis[nx]) dfsm(nx, p, 1);
    //到根
    ans[p] += curans + sz[p];
    for (ll nx : g[p])
        if (!vis[nx]) {
            dfsm(nx, p, -1);
            curans += sz[p] - sz[nx];
            dfsq(nx, p, sz[p] - sz[nx]);
            curans -= sz[p] - sz[nx];
            dfsm(nx, p, 1);
        }
    for (ll nx : g[p])
        if (!vis[nx]) dfsm(nx, p, -1);
    instk[c[p]] = 0;
    for (ll nx : g[p])
        if (!vis[nx]) dfz(nx);
}
int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) scanf("%lld", c + i);
    for (ll i = 1; i < n; i++) {
        ll u, v;
        scanf("%lld%lld", &u, &v);
        g[v].push_back(u);
        g[u].push_back(v);
    }
    dfz(1);
    for (ll i = 1; i <= n; i++) printf("%lld\n", ans[i]);

    return 0;
}
/*
5
1 2 3 2 3
1 2
2 3
2 4
1 5
*/

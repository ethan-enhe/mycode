#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 2e5 + 5;

ll n;
ll c[MXN];
vector<ll> g[MXN];

ll anc[MXN], ans[MXN];

ll c2(ll x) { return x * (x + 1) >> 1; }

map<ll, ll> csz[MXN];
ll sz[MXN];
void dfs1(ll u, ll f) {
    sz[u] = 1;
    for (ll v : g[u])
        if (v != f) {
            dfs1(v, u);
            sz[u] += sz[v];
        }
}

void dfs2(ll u, ll f) {
    ll a = anc[c[u]];
    csz[a][c[u]] -= sz[u];
    for (ll v : g[u])
        if (v != f) {
            anc[c[u]] = v;
            csz[v][c[u]] = sz[v];
            dfs2(v, u);
            ans[c[u]] -= c2(csz[v][c[u]]);
        }
    anc[c[u]] = a;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (ll i = 1; i < n; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (ll i = 1; i <= n; i++) anc[i] = 1, ans[i] = c2(n), csz[1][i] = n;
    dfs1(1, 0);
    dfs2(1, 0);
    for (auto [c, v] : csz[1]) {
        ans[c] -= c2(v);
    }
    for (ll i = 1; i <= n; i++) cout << ans[i] << '\n';
    return 0;
}

#include <bits/stdc++.h>

#include <algorithm>
#define fi first
#define se second
using namespace std;
using pii = pair<int, int>;
const int MAXN = 5e5 + 5;
int n, m;
vector<pii> g[MAXN];
int sk[MAXN], tp;
bool insk[MAXN];
int dfn[MAXN], low[MAXN], dsz;
int ecc[MAXN], esz;
void tarjan(int nw, int fa) {
    sk[++tp] = nw;
    insk[nw] = true;
    dfn[nw] = low[nw] = ++dsz;
    for (pii e : g[nw]) {
        int nxtn = e.fi;
        if (e.se == fa) continue;
        if (!dfn[nxtn]) {
            tarjan(nxtn, e.se);
            low[nw] = min(low[nw], low[nxtn]);
        } else if (insk[nxtn])
            low[nw] = min(low[nw], dfn[nxtn]);
    }
    if (dfn[nw] == low[nw]) {
        esz++;
        while (sk[tp] != nw) {
            ecc[sk[tp]] = esz;
            insk[sk[tp--]] = false;
        }
        ecc[sk[tp]] = esz;
        insk[sk[tp--]] = false;
    }
}

int sz[MAXN];
vector<pii> h[MAXN];
vector<pii> ans;
pii edge[MAXN];
int vis[MAXN];
bool clean[MAXN];
bool solve(int p, int fa) {
    clean[p] = sz[p] <= 1;
    for (auto [nx, i] : h[p]) {
        if (nx == fa) continue;
        clean[p] &= solve(nx, p);
    }
    for (auto [nx, i] : h[p]) {
        if (nx == fa) continue;
        if (!clean[p] && clean[nx]) {
            if (ecc[edge[i].fi] == p)
                ans.push_back({edge[i].fi, edge[i].se});
            else
                ans.push_back({edge[i].se, edge[i].fi});
        }
    }
    return clean[p];
}
void solve2(int p, int fa) {
    if (h[p].size() == 1) {
        int i = h[p][0].se;
        if (ecc[edge[i].fi] == p)
            ans.push_back({edge[i].fi, edge[i].se});
        else
            ans.push_back({edge[i].se, edge[i].fi});
    }
    for (auto [nx, i] : h[p]) {
        if (nx == fa) continue;
        solve2(nx, p);
    }
}

void mark(int p, int fa, int color) {
    vis[p] = color;
    for (auto [nx, i] : h[p]) {
        if (nx == fa) continue;
        mark(nx, p, color);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edge[i] = {u, v};
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i, 0);
    for (int i = 1; i <= n; i++) {
        // cout << ecc[i] << endl;
        ++sz[ecc[i]];
        for (auto [v, j] : g[i])
            if (ecc[i] != ecc[v]) h[ecc[i]].push_back({ecc[v], j});
    }
    for (int i = 1; i <= esz; i++) {
        if (!vis[i] && sz[i] > 1) {
            bool res = solve(i, 0);
            mark(i, 0, 2);
        }
    }
    for (int i = 1; i <= esz; i++) {
        if (vis[i] < 2) {
            solve2(i, 0);
            mark(i, 0, 2);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto [u, v] : ans) cout << u << " " << v << "\n";
    return 0;
}

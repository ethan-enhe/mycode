// File:             mcmf.cpp
// Author:           ethan
// Created:          01/07/22
// Description:      mcmf

#include <bits/stdc++.h>


typedef long long ll;
using namespace std;
// {{{ flow
template <const int MXN, typename T = int>
struct flow {
    const T INF = numeric_limits<T>::max();
    struct edge {
        int v, o;
        T c, w;
        edge(int _v, T _c, T _w, int _o) : v(_v), c(_c), w(_w), o(_o) {}
    };
    vector<edge> g[MXN];
    queue<int> q;
    int s, t, cure[MXN];
    bool vis[MXN];
    T dis[MXN];
    void addedge(int u, int v, T c, T w) {
        g[u].push_back(edge(v, c, w, g[v].size()));
        g[v].push_back(edge(u, 0, -w, g[u].size() - 1));
    }
    void adduedge(int u, int v, T c) {
        g[u].push_back(edge(v, c, 1, g[v].size()));
        g[v].push_back(edge(u, 0, 1, g[u].size() - 1));
    }
    bool spfa() {
        for (int i = 1; i < MXN; i++) dis[i] = INF, cure[i] = 0;
        dis[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            vis[p] = 0;
            for (edge &nx : g[p])
                if (nx.c && dis[nx.v] > dis[p] + nx.w) {
                    dis[nx.v] = dis[p] + nx.w;
                    if (!vis[nx.v]) {
                        vis[nx.v] = 1;
                        q.push(nx.v);
                    }
                }
        }
        return dis[t] != INF;
    }
    T dinic(int p, T fi) {
        if (p == t) return fi;
        T fo = 0;
        vis[p] = 1;
        for (int &i = cure[p]; i < (int)g[p].size(); i++) {
            edge &nx = g[p][i];
            if (dis[nx.v] == dis[p] + nx.w && !vis[nx.v] && nx.c) {
                T delt = dinic(nx.v, min(fi - fo, nx.c));
                if (delt) {
                    nx.c -= delt;
                    g[nx.v][nx.o].c += delt;
                    fo += delt;
                    if (fi == fo) return vis[p] = 0, fo;
                } else
                    dis[nx.v] = -1;
            }
        }
        return vis[p] = 0, fo;
    }
    pair<T, T> run(int _s, int _t) {
        s = _s, t = _t;
        pair<T, T> res = {0, 0};
        while (spfa()) {
            T delt = dinic(s, INF);
            res.first += delt, res.second += delt * dis[t];
        }
        return res;
    }
};
template <const int MXN, typename T = int>
struct limflow {
    const T INF = numeric_limits<T>::max();
    flow<MXN, T> f;
    T deg[MXN];
    pair<T, T> res;
    void addedge(int u, int v, T l, T r, T w, bool cycle = 0) {
        if (cycle && w < 0) {
            w = -w;
            swap(v, u), swap(l, r);
            l = -l, r = -r;
        }
        deg[u] -= l, deg[v] += l;
        res.second += l * w;
        f.addedge(u, v, r - l, w);
    }
    void adduedge(int u, int v, T l, T r) {
        deg[u] -= l, deg[v] += l;
        f.adduedge(u, v, r - l);
    }
    // Option:
    // 0->min_cost_valid_flow
    // 1->min_cost_max_flow
    // 2->min_cost_min_flow
    pair<T, T> run(int ss, int st, int s, int t, int opt = 1) {
        T all = 0;
        for (int i = 1; i < MXN; i++) {
            if (deg[i] > 0)
                f.addedge(ss, i, deg[i], 0), all += deg[i];
            else if (deg[i] < 0)
                f.addedge(i, st, -deg[i], 0);
        }
        f.addedge(t, s, INF, 0);
        pair<T, T> tres = f.run(ss, st);
        if (tres.first != all) return {-1, -1};
        res.second += tres.second;
        res.first += f.g[s].rbegin()->c;
        f.g[s].rbegin()->c = 0;
        f.g[t].rbegin()->c = 0;
        if (opt == 1) {
            tres = f.run(s, t);
            res.first += tres.first, res.second += tres.second;
        } else if (opt == 2) {
            tres = f.run(t, s);
            res.first -= tres.first, res.second += tres.second;
        }
        return res;
    }
};
// }}}
const ll MXN = 35, INF = 1e9;
ll n, m;
ll type[MXN][MXN], id[MXN][MXN][2], va[MXN][MXN][2];
ll nodec = 4;
limflow<1100,ll> f;
int main() {
    // freopen("P4486.in", "r", stdin);
    // freopen("P4486.out","w",stdout);
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++) scanf("%lld", &type[i][j]);
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++) {
            if (type[i][j]==4) scanf("%lld", &va[i][j][0]);
            if ((type[i][j] >> 0) & 1) {
                scanf("%lld", &va[i][j][0]);
                ++nodec;
                for (ll k = i; k <= n; k++) id[k][j][0] = nodec;
            }
            if ((type[i][j] >> 1) & 1) {
                scanf("%lld", &va[i][j][1]);
                ++nodec;
                for (ll k = j; k <= m; k++) id[i][k][1] = nodec;
            }
            // printf("(%2d,%2d) ", id[i][j][0], id[i][j][1]);
        }
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++) {
            ll tmp;
            if (type[i][j]==4) {
                scanf("%lld", &tmp);
                f.addedge(id[i][j][0], id[i][j][1], va[i][j][0], va[i][j][0], 0);
                if (~tmp) {
                    f.addedge(id[i][j][0], id[i][j][1], 0, INF, tmp);
                    f.addedge(id[i][j][1], id[i][j][0], 0, va[i][j][0]-1, tmp);
                }
            }
            if ((type[i][j] >> 0) & 1) {
                scanf("%lld", &tmp);
                f.addedge(3, id[i][j][0], va[i][j][0], va[i][j][0], 0);
                if (~tmp) {
                    f.addedge(3, id[i][j][0], 0, INF, tmp);
                    f.addedge(id[i][j][0], 3, 0, va[i][j][0]-1, tmp);
                }
            }
            if ((type[i][j] >> 1) & 1) {
                scanf("%lld", &tmp);
                f.addedge(id[i][j][1], 4, va[i][j][1], va[i][j][1], 0);
                if (~tmp) {
                    f.addedge(id[i][j][1], 4, 0, INF, tmp);
                    f.addedge(4, id[i][j][1], 0, va[i][j][1], tmp);
                }
            }
        }
	auto res=f.run(1, 2, 3, 4,0);
	printf("%lld",res.second);
    return 0;
}


// File:             mcmf.cpp
// Author:           ethan
// Created:          01/07/22
// Description:      mcmf

#include <bits/stdc++.h>

#include <limits>
#include <vector>

using namespace std;

// {{{ flow
// 原始版费用流
template <const int MXN, typename T = int>
struct raw_flow {
    const T INF = numeric_limits<T>::max();
    struct edge {
        int v, o;
        T c, w;
        edge(int _v, T _c, T _w, int _o) : v(_v), o(_o), c(_c), w(_w) {}
    };
    vector<edge> g[MXN];
    queue<int> q;
    int s, t, cure[MXN];
    bool vis[MXN];
    T dis[MXN];
    void clear() {
        for (int i = 0; i < MXN; i++) {
            g[i].clear();
            cure[i] = 0;
            vis[i] = 0;
            dis[i] = 0;
        }
        s = t = 0;
        while (!q.empty()) q.pop();
    }
    void addedge(int u, int v, T c, T w) {
        g[u].push_back(edge(v, c, w, g[v].size()));
        g[v].push_back(edge(u, 0, -w, g[u].size() - 1));
    }
    void adduedge(int u, int v, T c) {
        g[u].push_back(edge(v, c, 1, g[v].size()));
        g[v].push_back(edge(u, 0, 1, g[u].size() - 1));
    }
    bool spfa() {
        for (int i = 0; i < MXN; i++) dis[i] = INF, cure[i] = 0;
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
// 封装的上下界网络流
template <const int MXN, typename T = int>
struct lim_flow {
    const T INF = numeric_limits<T>::max();
    raw_flow<MXN, T> f;
    T deg[MXN];
    pair<T, T> res;
    void clear() {
        f.clear();
        for (int i = 0; i < MXN; i++) deg[i] = 0;
        res = {0, 0};
    }
    // 加边函数 起点 终点 流量下界 流量上界 [是否有负环=false]
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
    // 加单位边的函数（只求最大流，不求费用的时候用这个加边，跑的比较快）
    void adduedge(int u, int v, T l, T r) {
        /* cerr << u << " " << v << " " << l << " " << r << endl; */
        deg[u] -= l, deg[v] += l;
        f.adduedge(u, v, r - l);
    }
    // 超级源点 超级汇点 源点 汇点 [选项=1]
    // 选项：
    // 0->最小费用可行流
    // 1->最小费用最大流
    // 2->最小费用最小流
    pair<T, T> run(int ss, int st, int s, int t, int opt = 1) {
        T all = 0;
        for (int i = 0; i < MXN; i++) {
            if (deg[i] > 0)
                f.addedge(ss, i, deg[i], 0), all += deg[i];
            else if (deg[i] < 0)
                f.addedge(i, st, -deg[i], 0);
        }
        f.addedge(t, s, INF, 0);
        pair<T, T> tres = f.run(ss, st);
        if (tres.first != all) return {-1, -1};
        res.second += tres.second;
        res.first += f.g[s].back().c;
        f.g[s].back().c = 0;
        f.g[t].back().c = 0;
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

using ll = long long;
const ll MXN = 150, INF = 1e18;
lim_flow<MXN, ll> f;
struct e {
    ll u, v, w;
};
vector<e> arr;
vector<ll> cdn;
ll n, m, type[MXN];
bool cdn_enable[MXN];

#define node_in(x) x
#define node_out(x) (x + n)
#define ss n * 2 + 1
#define tt n * 2 + 2
bool chk(ll mn) {
    f.clear();
    for (ll i = 1; i <= n; i++) {
        ll self_lower, copy_upper, stop_lower = 0;
        if (type[i] == 0)
            self_lower = 0, copy_upper = 0;
        else if (type[i] == 1) {
            if (cdn_enable[i])
                self_lower = 1, copy_upper = INF;
            else
                self_lower = 0, copy_upper = 0;
        } else
            stop_lower = 1, self_lower = 1, copy_upper = 0;

        f.adduedge(node_in(i), node_out(i), self_lower, INF);
        f.adduedge(node_out(i), tt, stop_lower, INF);
        if (copy_upper) f.adduedge(ss, node_out(i), 0, copy_upper);
    }
    f.adduedge(ss, node_in(1), 1, 1);
    f.adduedge(tt, ss, 0, INF);
    for (auto i : arr) f.adduedge(node_out(i.u), node_in(i.v), 0, mn ? i.w / mn : INF);
    auto ans = f.run(MXN - 1, MXN - 2, ss, tt, 0);
    return ans.first != -1;
}
bool dfs(ll ind, ll mn) {
    if (ind == cdn.size()) return chk(mn);
    cdn_enable[cdn[ind]] = 1;
    if (dfs(ind + 1, mn)) return 1;
    cdn_enable[cdn[ind]] = 0;
    if (dfs(ind + 1, mn)) return 1;
    return 0;
}

void solve() {
    arr.clear();
    cdn.clear();
    cin >> n >> m;
    type[1] = 1;
    for (ll i = 2; i <= n; i++) {
        cin >> type[i];
        if (type[i] == 1) cdn.push_back(i);
    }
    while (m--) {
        ll u, v, w;
        cin >> u >> v >> w;
        arr.push_back({u, v, w});
    }
    cdn_enable[1] = 1;
    ll l = 0, r = 1e9;
    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        if (dfs(0, mid))
            l = mid;
        else
            r = mid - 1;
    }
    cout << l << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}

// File:             flow.cpp
// Author:           ethan
// Created:          01/04/22
// Description:      mcmf
#include <bits/stdc++.h>

using namespace std;
const int MXN = 5e3 + 5, INF = 1e9;
int n, m, s, t, ansf, answ;
struct edge {
    int v, c, w, o;
};
vector<edge> g[MXN];
void ae(int u, int v, int c, int w) {
    g[u].push_back({v, c, w, (int)g[v].size()});
    g[v].push_back({u, 0, -w, (int)g[u].size() - 1});
}
bool vis[MXN];
int cure[MXN], dis[MXN];
queue<int> q;
bool spfa() {
    for (int i = 1; i <= n; i++) dis[i] = INF, cure[i] = 0;
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
int dinic(int p, int fi) {
    if (p == t) return fi;
    int fo = 0;
    vis[p] = 1;
    for (int &i = cure[p]; i < (int)g[p].size(); i++) {
        edge &nx = g[p][i];
        if (dis[nx.v] == dis[p] + nx.w && !vis[nx.v] && nx.c) {
            int delt = dinic(nx.v, min(fi - fo, nx.c));
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
int main() {
	// freopen("mcmf.in","r",stdin);
	// freopen("mcmf.out","w",stdout);
    // scanf("%d%d%d%d", &n, &m, &s, &t);
    scanf("%d%d", &n, &m);
	s=1,t=n;
    while (m--) {
        int u, v, c, w;
        scanf("%d%d%d%d", &u, &v, &c, &w);
        ae(u, v, c, w);
    }
    while (spfa()) {
        int flow = dinic(s, INF);
        ansf += flow;
        answ += flow * dis[t];
    }
    printf("%d %d", ansf, answ);
    return 0;
}

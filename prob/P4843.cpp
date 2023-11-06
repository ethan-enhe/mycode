// File:             mcmf.cpp
// Author:           ethan
// Created:          01/07/22
// Description:      mxmf

#include <bits/stdc++.h>

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
    pair<T, T> mcmf(int _s, int _t) {
        tie(s, t) = {_s, _t};
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
    flow<MXN> f;
    T deg[MXN];
    pair<T, T> res;
    void addedge(int u, int v, T l, T r, T w, bool cycle = 1) {
        if (cycle && w < 0) {
            w = -w;
            swap(v, u);
            tie(l, r) = make_tuple(-r, -l);
        }
        deg[u] -= l, deg[v] += l;
        res.second += l * w;
        f.addedge(u, v, r - l, w);
    }
    pair<T, T> run(int ss, int st, int s, int t, bool ismx = 1) {
        T all = 0;
        for (int i = 1; i < MXN; i++) {
            if (deg[i] > 0)
                f.addedge(ss, i, deg[i], 0), all += deg[i];
            else if (deg[i] < 0)
                f.addedge(i, st, -deg[i], 0);
        }
        f.addedge(t, s, INF, 0);
        pair<T, T> tres = f.mcmf(ss, st);
        if (tres.first != all) return {-1, -1};
        res.second += tres.second;
        res.first += f.g[s].rbegin()->c;
        f.g[s].rbegin()->c = 0;
        f.g[t].rbegin()->c = 0;
        if (ismx) {
            tres = f.mcmf(s, t);
            res.first += tres.first, res.second += tres.second;
        } else {
            tres = f.mcmf(t, s);
            res.first -= tres.first, res.second += tres.second;
        }
        return res;
    }
};
// }}}

const int INF=1e9;
limflow<110> f;
int main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int cnt,k;
		scanf("%d",&cnt);
		while(cnt--){
			scanf("%d",&k);
			f.addedge(i, k, 1, INF, 0);
		}
		f.addedge(n+1, i, 0, INF, 0);
		f.addedge(i, n+2, 0, INF, 0);
	}
	printf("%d",f.run(n+3, n+4, n+1, n+2,0).first);
    return 0;
}


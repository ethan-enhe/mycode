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
template <const int MXN, typename T = int> struct flow {
	const T INF = numeric_limits<T>::max();
	struct edge {
		int v, o;
		T c, w;
		bool fwd;
		edge(int _v, T _c, T _w, int _o, bool _fwd = 0)
			: v(_v), c(_c), w(_w), o(_o), fwd(_fwd) {}
	};
	vector<edge> g[MXN];
	queue<int> q;
	int s, t, cure[MXN];
	bool vis[MXN];
	T dis[MXN];
	void addedge(int u, int v, T c, T w) {
		g[u].push_back(edge(v, c, w, g[v].size(), 1));
		g[v].push_back(edge(u, 0, -w, g[u].size() - 1));
	}
	void adduedge(int u, int v, T c) {
		g[u].push_back(edge(v, c, 1, g[v].size(), 1));
		g[v].push_back(edge(u, 0, 1, g[u].size() - 1));
	}
	void clear() {
		for (int i = 1; i < MXN; i++)
			for (edge &nx : g[i])
				if (nx.fwd) {
					nx.c += g[nx.v][nx.o].c;
					g[nx.v][nx.o].c = 0;
				}
	}
	bool spfa() {
		for (int i = 1; i < MXN; i++)
			dis[i] = INF, cure[i] = 0;
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
		if (p == t)
			return fi;
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
					if (fi == fo)
						return vis[p] = 0, fo;
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
// }}}
constexpr int MXN = 505, INF = 1e9;
flow<MXN> f;
int n, m, ans[MXN][MXN];
vector<pair<int, int>> t[MXN];
void build(vector<int> p) {
	if (p.size() == 1)
		return;
	int _s = p[0], _t = p[1];
	f.clear();
	auto res = f.run(_s, _t);
	// cerr << _s << " " << _t << " " << res.first << endl;
	t[_s].push_back({_t, res.first});
	t[_t].push_back({_s, res.first});
	vector<int> t1, t2;
	for (int i : p) {
		if (f.dis[i] < INF)
			t1.push_back(i);
		else
			t2.push_back(i);
	}
	p.clear();
	build(t1), build(t2);
}
void dfs(int p, int fa, int *arr) {
	for (auto nx : t[p])
		if (nx.first != fa) {
			arr[nx.first] = min(arr[p], nx.second);
			dfs(nx.first, p, arr);
		}
}
int main() {
	// freopen("P4897.in","r",stdin);
	// freopen("P4897.out","w",stdout);
	scanf("%d%d", &n, &m);
	while (m--) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		f.adduedge(u, v, c);
		f.adduedge(v, u, c);
	}
	vector<int> node;
	for (int i = 1; i <= n; i++)
		node.push_back(i);
	build(node);
	for (int i = 1; i <= n; i++) {
		ans[i][i] = INF;
		dfs(i, 0, ans[i]);
	}
	scanf("%d", &m);
	while (m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", ans[x][y]);
	}
	return 0;
}

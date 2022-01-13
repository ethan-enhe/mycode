
// File:             mcmf.cpp
// Author:           ethan
// Created:          01/07/22
// Description:      mcmf

#include <bits/stdc++.h>
#include <limits>

using namespace std;

// {{{ flow
// 原始版费用流
template <const int MXN, typename T = int> struct flow {
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
// 封装的上下界网络流
template <const int MXN, typename T = int> struct limflow {
	const T INF = numeric_limits<T>::max();
	flow<MXN, T> f;
	T deg[MXN];
	pair<T, T> res;
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
		for (int i = 1; i < MXN; i++) {
			if (deg[i] > 0)
				f.addedge(ss, i, deg[i], 0), all += deg[i];
			else if (deg[i] < 0)
				f.addedge(i, st, -deg[i], 0);
		}
		f.addedge(t, s, INF, 0);
		pair<T, T> tres = f.run(ss, st);
		if (tres.first != all)
			return {-1, -1};
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

constexpr int MXN=45,INF=1e9,go[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
#define id(x,y,z) (x)*MXN*MXN+(y)*MXN+(z)
int s=1,t=2,p,q,r,d;
flow<MXN*MXN*MXN> f;
int main() {
	scanf("%d%d%d%d",&p,&q,&r,&d);
	for(int k=1;k<=r;k++)
		for(int i=1;i<=p;i++)
			for(int j=1;j<=q;j++){
				int tmp;
				scanf("%d",&tmp);
				if(k==r)f.adduedge(id(i,j,k), t, tmp);
				else f.adduedge(id(i,j,k), id(i,j,k+1), tmp);
				if(k==1)f.adduedge(s, id(i,j,k), INF);
				if(k>d){
					for(int l=0;l<4;l++){
						int nxi=i+go[l][0],nxj=j+go[l][1];
						if(nxi<1 || nxi>p)continue;
						if(nxj<1 || nxj>q)continue;
						f.adduedge(id(i,j,k), id(nxi,nxj,k-d), INF);
					}
				}
			}
	auto res=f.run(s, t);
	printf("%d\n",res.first);
	return 0;
}

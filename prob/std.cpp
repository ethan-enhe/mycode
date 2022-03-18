# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 10005;
const int MAXM = 10005;
const int MAXV = 4 * MAXM + 5 * MAXN;
const int MAXE = MAXV + 5 * MAXN + 6 * MAXM;
const ll INF = 0x3f3f3f3f3f3f3f3f;
struct Edge{
	int t;
	ll c;
	int nxt;
	Edge(int t = 0, ll c = 0, int nxt = 0): t(t), c(c), nxt(nxt){}
} g[MAXE * 2];
int gsz = 1;
int fte[MAXV], curE[MAXV];
void addedge(int u, int v, ll c){
	// cout << "addedge " << u << ' ' << v <<' ' << c << '\n';
	g[++gsz] = Edge(v, c, fte[u]);
	fte[u] = gsz;
	g[++gsz] = Edge(u, 0, fte[v]);
	fte[v] = gsz;
}
int dep[MAXV];
int q[MAXV], ql, qr;
bool bfs(int S, int T){
	memset(dep, -1, sizeof(dep));
	dep[S] = 0;
	q[ql = qr = 1] = S;
	while (ql <= qr){
		int nw = q[ql++];
		for (int i = fte[nw]; i; i = g[i].nxt){
			int nxtn = g[i].t;
			if (!g[i].c || dep[nxtn] != -1) continue;
			dep[nxtn] = dep[nw] + 1;
			q[++qr] = nxtn;
			if (nxtn == T) return true;
		}
	}
	return dep[T] != -1;
}
ll dfs(int nw, ll mxf, int T){
	if (nw == T) return mxf;
	if (!mxf) return 0;
	ll df = 0;
	for (int &i = curE[nw]; i; i = g[i].nxt){
		int nxtn = g[i].t;
		if (!g[i].c || dep[nxtn] != dep[nw] + 1) continue;
		ll nwf = dfs(nxtn, min(mxf - df, g[i].c), T);
		if (!nwf) dep[nxtn] = -1;
		g[i].c -= nwf;
		g[i ^ 1].c += nwf;
		if ((df += nwf) == mxf) break;
	}
	return df;
}
ll dinic(int S, int T){
	ll ans = 0;
	while (bfs(S, T)){
		// cout << "dinic " << S << ' ' << T << ' ' << ans << '\n';
		memcpy(curE, fte, sizeof(fte));
		ans += dfs(S, INF, T);
	}
	return ans;
}
ll ans = 0;
int n, m, nsz;
ll c[MAXN], d[MAXN], e[MAXN];
int addnd(ll val, int S, int T){
	int nw = ++nsz;
	if (val < 0) addedge(nw, T, -val);
	else {
		ans += val;
		addedge(S, nw, val);
	}
	return nw;
}
int p[MAXN];
int cp[MAXN];
int main(){
	cin >> n >> m;
	int S = ++nsz;
	int T = ++nsz;
	for (int i = 1; i <= 2 * n; i++){
		cin >> c[i] >> d[i] >> e[i];
		ans += -d[i];
		p[i] = addnd(d[i] - c[i], S, T);
		addedge(p[i], addnd(-e[i], S, T), INF);
	}
	for (int i = 1; i <= n; i++){
		int nw = addnd(e[2 * i - 1] + e[2 * i], S, T);
		addedge(nw, p[i * 2 - 1], INF);
		addedge(nw, p[i * 2], INF);
        nw = addnd(0, S, T);
        addedge(nw, p[i * 2 - 1], INF);
        addedge(nw, p[i * 2], INF);
		cp[i * 2 - 1] = cp[i * 2] = nw;
	}
	for (int i = 1; i <= m; i++){
		int u, v;
		ll a, b;
		cin >> u >> v >> a >> b;
		addedge(p[v], addnd(-a, S, T), INF);
		int nw = addnd(a, S, T);
		addedge(nw, cp[u], INF);
		addedge(nw, p[v], INF);

		addedge(cp[v], addnd(-b, S, T), INF);
		nw = addnd(b, S, T);
		addedge(nw, p[u], INF);
		addedge(nw, cp[v], INF);
	}
	ans -= dinic(S, T);
	cout << -ans << '\n';
	return 0;
}

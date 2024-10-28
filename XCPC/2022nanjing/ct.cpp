# include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
# define fi first
# define se second
const int MAXN = 100051;
const int MAXV = MAXN * 2;
int T, n;
int a[MAXN];
int b[MAXN], bsz;
int c[MAXN], csz;
vector<pii> g[MAXV];
int fa[MAXV];
bool vis[MAXV];
bool flg[MAXN];
int dfs(int u){
	vis[u] = true;
	int sm = (g[u].size() & 1) && (u <= n);
	for (pii e : g[u]){
		int v = e.fi;
		if (v == fa[u]) continue;
		fa[v] = u;
		flg[e.se] = dfs(v);
		sm ^= flg[e.se];
	}
	return sm;
}
vector<int> adj[MAXN];
vector<int> bdj[MAXN];
bool chk(){
	for (int i = 1; i <= bsz; i++){
		if (vis[i]) continue;
		if (dfs(i)) return false;
	}
	return true;
}
int main(){
	for(int i=1;i<=100;i++){
		system("./gen.exe");
	}
	
}


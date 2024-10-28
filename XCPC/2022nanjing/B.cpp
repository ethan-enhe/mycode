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
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1; i <= n; i++) flg[i] = false;
		for (int i = 1; i <= 2 * n; i++){
			vis[i] = false;
			fa[i] = 0;
		}
		for (int i = 1; i <= n; i++) cin >> a[i];
		bsz = csz = 0;
		for (int i = 1; i <= n; i++) b[++bsz] = a[i] + i;
		for (int i = 1; i <= n; i++) c[++csz] = a[i] - i;
		sort(b + 1, b + bsz + 1);
		bsz = unique(b + 1, b + bsz + 1) - b - 1;
		sort(c + 1, c + csz + 1);
		csz = unique(c + 1, c + csz + 1) - c - 1;
		for (int i = 1; i <= n; i++){
			int u = lower_bound(b + 1, b + bsz + 1, a[i] + i) - b;
			int v = lower_bound(c + 1, c + csz + 1, a[i] - i) - c;
			adj[u].push_back(i);
			bdj[v].push_back(i);
			g[u].push_back(pii(v + n, i));
			g[v + n].push_back(pii(u, i));
		}
		if (!chk()) cout << "No\n";
		else {
			cout << "Yes\n";
			for (int i = 1; i <= bsz; i++){
				int lst = 0;
				for (int u : adj[i]){
					// cerr << "i " << i << ' ' << u << ' ' << flg[u] << '\n';
					if (flg[u]) continue;
					if (!lst) lst = u;
					else {
						cout << lst << ' ' << u << '\n';
						lst = 0;
					}
				}
			}
			for (int i = 1; i <= csz; i++){
				int lst = 0;
				for (int u : bdj[i]){
					if (!flg[u]) continue;
					if (!lst) lst = u;
					else {
						cout << lst << ' ' << u << '\n';
						lst = 0;
					}
				}
			}
		}
		for (int i = 1; i <= n; i++){
			adj[i].clear();
			bdj[i].clear();
		}
		for (int i = 1; i <= 2 * n; i++) g[i].clear();
	}
	return 0;
}

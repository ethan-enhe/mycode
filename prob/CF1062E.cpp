#include <bits/stdc++.h>

#include <cstdio>
#include <vector>
using namespace std;
const int MXN = 5e5 + 5, LG = 19;
int n, m, dfnc, dfn[MXN][LG+1];
vector<int> g[MXN];
int anc[MXN][LG + 1], dpth[MXN];
void dfs(int p) {
    dfn[p][0] = ++dfnc;
    dpth[p] = dpth[anc[p][0]] + 1;
    for (int i = 0; (1 << i) <= dpth[p]; i++) anc[p][i + 1] = anc[anc[p][i]][i];
    for (int nx : g[p]) dfs(nx);
}
inline int lca(int x, int y) {
    if (dpth[x] < dpth[y]) swap(x, y);
    int tmp = dpth[x] - dpth[y];
    for (int i = LG; ~i; i--)
        if ((tmp >> i) & 1) x = anc[x][i];
    if (x == y) return x;
    for (int i = LG; ~i; i--)
        if (anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        scanf("%d", &anc[i][0]);
        g[anc[i][0]].push_back(i);
    }
    dfs(1);
	for(int i=0;i<=LG;i++)
		for(int j=n-(1<<i)+1;j;j--)

    return 0;
}

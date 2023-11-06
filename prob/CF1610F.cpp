#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back

typedef pair<int, int> pi;
const int MXN = 2e6 + 5;
int n, m;
int e[MXN][3], cure[MXN], ans[MXN];
bool cnt[MXN][3], has[MXN][3];
int trans(int x, int y) {
    if (cnt[x][1]) {
        if (cnt[x][y] && !has[x][y]) {
            has[x][y] = 1;
            return x;
        }
        return x + n * y;
    }
    return x;
}
vector<pi> g[MXN];
void ae(int x, int y, int z) {
    g[x].pb({y, z});
    g[y].pb({x, -z});
}
void build(int x, int y, int w, int id) { ae(trans(x, w), trans(y, w), id); }
void dfs(int p) {
    for (int &i = cure[p]; i < g[p].size();) {
        pi &nx = g[p][i++];
        if (ans[abs(nx.se)]) continue;
        ans[abs(nx.se)] = 1 + (nx.se < 0);
        dfs(nx.fi);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < 3; j++) scanf("%d", &e[i][j]);
        cnt[e[i][0]][e[i][2]] ^= 1;
        cnt[e[i][1]][e[i][2]] ^= 1;
    }
    for (int i = 1; i <= m; i++) build(e[i][0], e[i][1], e[i][2], i);
    int last = 0, res = 0, ec = m;
    for (int i = 1; i <= n * 3; i++)
        if (g[i].size() & 1) {
            if (last) {
                ae(last, i, ++ec);
                last = 0;
            } else
                last = i;
        }
    for (int i = 1; i <= n * 3; i++) dfs(i);
    for (int i = 1; i <= n; i++) res += cnt[i][1];
    printf("%d\n", res);
    for (int i = 1; i <= m; i++) putchar('0' + ans[i]);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int MXN = 3e5 + 5;
struct edge {
    int v, w;
};
int n, m, fa[MXN], dpth[MXN];
vector<edge> g[MXN];
bool ban[MXN];
inline int dfs(int p) {
    int mx = p;
    ban[p] = 1;
    for (edge &nx : g[p])
        if (!ban[nx.v]) {
            dpth[nx.v] = dpth[p] + nx.w;
            fa[nx.v] = p;
            int tmp = dfs(nx.v);
            if (dpth[tmp] > dpth[mx]) mx = tmp;
        }
    return mx;
}
int dia[MXN], dis2s[MXN], dis2d[MXN], diac;
inline void init() {
    int s = dfs(1);
    memset(ban, 0, sizeof(ban));
    dpth[s] = fa[s] = 0;
    s = dfs(s);
    while (s) {
        ++diac;
        dia[diac] = s, dis2s[diac] = dpth[s];
        s = fa[s];
    }
}
int q[MXN], ql = 1, qr;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int tu, tv, tw;
        scanf("%d%d%d", &tu, &tv, &tw);
        g[tu].push_back({tv, tw});
        g[tv].push_back({tu, tw});
    }
    init();
    memset(ban, 0, sizeof(ban));
    int ind = 1, ans = 1e9;
    for (int i = 1; i <= diac; i++) {
        ban[dia[i - 1]] = ban[dia[i + 1]] = 1;
        dpth[dia[i]] = ban[dia[i]] = 0;
        dis2d[i] = dpth[dfs(dia[i])];
        while (qr >= ql && dis2d[i] >= dis2d[q[qr]]) qr--;
        q[++qr] = i;
        while (dis2s[ind] - dis2s[i] > m) ind++;
        while (qr >= ql && q[ql] < ind) ql++;
        ans = min(ans, max(max(dis2s[i], dis2s[1] - dis2s[ind]), dis2d[q[ql]]));
    }
    printf("%d", ans);
    return 0;
}

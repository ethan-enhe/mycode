#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <vector>
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
#define NDEBUG
#endif
#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
const int MXN = 2e3 + 5;

int n, m, arr[MXN];
char str[MXN];
vector<int> g[MXN];

int _fa[MXN][MXN];
int dp[MXN][MXN];

void umx(int &x, int y) { x = max(x, y); }
void dfs(int p, int rt, int fa) {
    _fa[rt][p] = fa;
    for (int nx : g[p])
        if (nx != fa) dfs(nx, rt, p);
}
int cal(int u, int v) {
    if (u == v) return 1;
    if (dp[u][v] == -1) {
        dp[u][v] = 0;
        if (str[u] == str[v]) {
            if (_fa[v][u] == v)
                umx(dp[u][v], 2);
            else
                umx(dp[u][v], 2 + cal(_fa[v][u], _fa[u][v]));
        }
        umx(dp[u][v], cal(_fa[v][u], v));
        umx(dp[u][v], cal(u, _fa[u][v]));
    }
    return dp[u][v];
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        cin >> (str + 1);
        for (int i = 0; i <= n; i++) {
            g[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= n; i++) dfs(i, i, 0);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) umx(ans, cal(i, j));
        cout << ans << '\n';
    }
    return 0;
}

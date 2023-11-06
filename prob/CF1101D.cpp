#include <bits/stdc++.h>
using namespace std;
const int MXN = 2e5 + 5;
vector<int> fac[MXN], g[MXN];
int n, mx, ans, arr[MXN], dp[MXN][6];
void dfs(int p, int fa) {
    int szp = fac[arr[p]].size(), sznx;
    for (int i = 0; i < szp; i++) dp[p][i] = 1;
    for (int nx : g[p])
        if (nx != fa) {
            dfs(nx, p);
            sznx = fac[arr[nx]].size();
            for (int i = 0; i < szp; i++)
                for (int j = 0; j < sznx; j++)
                    if (fac[arr[p]][i] == fac[arr[nx]][j]) {
                        ans = max(ans, dp[p][i] + dp[nx][j]);
                        dp[p][i] = max(dp[p][i], dp[nx][j] + 1);
                    }
        }
    ans = max(ans, dp[p][0]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", arr + i), mx = max(mx, arr[i]);
    for (int i = 2; i <= mx; i++)
        if (fac[i].empty())
            for (int j = i; j <= mx; j += i) fac[j].push_back(i);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1, 0);
    printf("%d", ans);
    return 0;
}

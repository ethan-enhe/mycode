#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e5 + 5, INF = 1e9;
int n, dfnc, SQRT;
int dp[MXN], fa[MXN], dfn[MXN];
vector<int> g[MXN];
void dfs(int p, int f) {
    fa[dfn[p] = ++dfnc] = dfn[f];
    for (int nx : g[p])
        if (nx != f) dfs(nx, p);
}
inline int cal(int lim) {
    int ans = dp[1] = 0;
    for (int i = n; i > 1; i--) {
        int &dpf = dp[fa[i]];
        dp[i] += 1;
        if (~dpf) {
            if (dpf + dp[i] + 1 >= lim) {
                ans++;
                dpf = -1;
            } else
                dpf = max(dpf, dp[i]);
        }
        dp[i] = 0;
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    SQRT = sqrt(n * log(n) / log(2));
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1, 0);

    printf("%d\n", n);
    for (int i = 2; i <= SQRT; i++) printf("%d\n", cal(i));
    int curi = SQRT + 1;
    while (curi <= n) {
        int tmp = cal(curi), l = curi, r = n;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (cal(mid) == tmp)
                l = mid;
            else
                r = mid - 1;
        }
        do
            printf("%d\n", tmp);
        while (++curi <= l);
    }
    return 0;
}

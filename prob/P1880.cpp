#include <bits/stdc++.h>
using namespace std;
const int MXN = 5000;
int n, arr[MXN], dp[MXN][MXN], t[MXN][MXN];
int main() {
    memset(dp, 0x3f, sizeof dp);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", arr + i);
        dp[i][i] = 0, t[i][i] = i;
        arr[i] += arr[i - 1];
    }
    for (int i = n; i; i--)
        for (int j = i + 1; j <= n; j++) {
            for (int k = t[i][j - 1]; k <= t[i + 1][j]; k++)
                if (dp[i][j] > dp[i][k] + dp[k + 1][j]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j];
                    t[i][j] = k;
                }
            dp[i][j] += arr[j] - arr[i - 1];
        }
    printf("%d", dp[1][n]);
    return 0;
}

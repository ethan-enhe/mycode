#include <bits/stdc++.h>

using namespace std;
constexpr int MXN = 55, INF = 1e9;
template <typename T>
constexpr void umn(T &x, T y) {
    x = min(x, y);
}
int n, m = INF;
char str[MXN];
int dp[MXN][MXN];

int main(int argc, char *argv[]) {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[i][j] < INF) {
                umn(dp[i][i], dp[i][j] + 1);
                umn(dp[i + 1][j], dp[i][j] + 1);
                int len = (i - j);
                if (i + len > n) continue;
                bool f = 1;
                for (int k = 1; k <= len; k++)
                    if (str[i + k] != str[j + k]) {
                        f = 0;
                        break;
                    }
                if (f) umn(dp[i + len][j], dp[i][j] + 1);
            }
        }
        umn(dp[i + 1][i], dp[i][i] + 1);
    }
    for (int i = 0; i <= n; i++) umn(m, dp[n][i]);
    printf("%d", m);
    return 0;
}

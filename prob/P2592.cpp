#include <bits/stdc++.h>
using namespace std;
const int P = 12345678, MXN = 305, MXK = 25;
int n, m, k;
int dp[MXN][MXK][2];
inline void madd(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}
inline int cal(int lim) {
    memset(dp, 0, sizeof(dp));
    dp[0][-lim][!lim] = 1;
    for (int i = 0; i < n + m; i++)
        for (int j = (i ^ lim) & 1; j <= k; j += 2) {
            int tj = j + lim, boys = (i + tj) >> 1, girls = (i - tj) >> 1;
            for (int l = 0; l < 2; l++) {
                if (n != boys) madd(dp[i + 1][j + 1][l], dp[i][j][l]);
                if (j && m != girls)
                    madd(dp[i + 1][j - 1][l | (j - 1 == 0)], dp[i][j][l]);
            }
        }
    int r = 0;
    for (int i = 0; i <= k; i++) madd(r, dp[n + m][i][1]);
    return r;
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    int res = 0;

    for (int i = -k; i <= 0; i++) madd(res, cal(i));
    printf("%d\n", res);
    return 0;
}

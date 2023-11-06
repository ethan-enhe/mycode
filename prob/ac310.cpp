#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MXD = 12;
ll t, x, dig[MXD], dp[MXD][4][2];
inline ll cal(ll x) {
    ll cnt = 0;
    while (x) {
        dig[cnt++] = x % 10;
        x /= 10;
    }
    memset(dp, 0, sizeof(dp));
    dp[cnt][0][1] = 1;
    for (int i = cnt; i; i--)
        for (int j = 0; j <= 3; j++)
            for (int k = 0; k <= 9; k++) {
                int nj = (j == 3 ? 3 : (k == 6 ? j + 1 : 0));
                dp[i - 1][nj][0] += dp[i][j][0];
                if (k <= dig[i - 1]) dp[i - 1][nj][k == dig[i - 1]] += dp[i][j][1];
            }
    return dp[0][3][0] + dp[0][3][1];
}
int main() {
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld", &x);
        ll l = 1, r = 5e10, mid;
        while (l < r) {
            mid = (l + r) >> 1;
            if (cal(mid) < x)
                l = mid + 1;
            else
                r = mid;
        }
        printf("%lld\n", l);
    }
    return 0;
}

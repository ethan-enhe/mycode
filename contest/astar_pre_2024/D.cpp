#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll P = 998244353;
const ll MXN = 5005;
ll n, m, k;
char str[MXN];
int dp[MXN][MXN][3]; // 修改次数，当前位数，匹配位数
int main() {
    cin >> n >> k;
    cin >> str;
    for (ll i = n; i; i--) str[i] = str[i - 1];
    dp[0][0][0] = 1;
    for (ll i = 0; i <= k; i++)
        for (ll j = 0; j < n; j++)
            for (ll l = 0; l < 3; l++)
                if (dp[i][j][l]) {
                    for (char f = '0'; f <= '1'; f++) {
                        ll nxi = i + (f != str[j + 1]);
                        ll nxj = j + 1;
                        ll nxl = f == "110"[l] ? l + 1 : (l == 2 ? l : 0);
                        if (nxl == 3) continue;
                        dp[nxi][nxj][nxl] = (dp[nxi][nxj][nxl] + dp[i][j][l]) % P;
                    }
                    // cout << i << " " << j << " " << l << " " << dp[i][j][l] << endl;
                }
    ll ans = 0;
    for (ll i = 0; i <= k; i++)
        for (ll l = 0; l < 3; l++) {
            ans = (ans + dp[i][n][l]) % P;
        }
    cout << ans;
    return 0;
}

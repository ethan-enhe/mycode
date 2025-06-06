#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 2e5 + 5;
ll n;
char a[MXN], b[MXN];
bool dp[MXN][7]; // 进行完前i局，余数为j，谁必胜:0->a, 1->b
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    cin >> (a + 1) >> (b + 1);
    for (int i = 0; i < 7; i++) dp[n][i] = (i == 0);
    for (ll i = n - 1; ~i; i--) {
        for (ll j = 0; j < 7; j++) {
            ll op1 = j * 10 % 7, op2 = (j * 10 + a[i + 1] - '0') % 7;
            bool has0 = dp[i + 1][op1] == 0 || dp[i + 1][op2] == 0;
            bool has1 = dp[i + 1][op1] == 1 || dp[i + 1][op2] == 1;
            if (b[i + 1] == 'a')
                dp[i][j] = !has0;
            else
                dp[i][j] = has1;
            // if (i == n - 1 && j == 1)
            //     cout << endl << op1 << " " << op2 << " " << dp[i + 1][op1] << dp[i + 1][op2] << endl;
            // cout << dp[i][j];
        }
        // cout << endl;
    }
    cout << (dp[0][0] ? "bob" : "alice");
    return 0;
}

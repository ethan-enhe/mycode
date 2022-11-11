#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 40;
const ll P = 1e9 + 7;
ll x, y, dp[MXN][2][2];
void add(ll &x, ll y) {
    x += y;
    if (x >= P) x -= P;
}
ll solve(ll hdig) {
    memset(dp, 0, sizeof(dp));
    dp[hdig + 1][(x >> (hdig + 1)) == 0][(y >> (hdig + 1)) == 0] = 1;
    for (ll i = hdig + 1; i; i--) {
        ll xdig = (x >> (i - 1)) & 1;
        ll ydig = (y >> (i - 1)) & 1;
        for (ll a = 0; a <= 1; a++)
            for (ll b = 0; b <= 1; b++)
                if (dp[i][a][b]) {
                    // c0d0
                    if (i != hdig + 1) add(dp[i - 1][a && (0 == xdig)][b && (0 == ydig)], dp[i][a][b]);
                    // c1d0
                    if (!a || xdig == 1) add(dp[i - 1][a && (1 == xdig)][b && (0 == ydig)], dp[i][a][b]);
                    if (!b || ydig == 1) add(dp[i - 1][a && (0 == xdig)][b && (1 == ydig)], dp[i][a][b]);
                }
    }
    return dp[0][0][0] + dp[0][0][1] + dp[0][1][0] + dp[0][1][1];
}
int main() {
    ll t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> x >> y;
        ll ans = 0, tans = 0;

        for (ll i = 0; i <= 33; i++) ans = (ans + solve(i) * (i + 1)) % P;

        cout << ans << '\n';
    }

    return 0;
}

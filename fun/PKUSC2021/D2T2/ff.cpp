
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';
const ll MXN = 1000 + 5;
ll n, m, c, arr[MXN], dp[MXN][MXN];
void umn(ll &x, ll y) { x = min(x, y); }
ll solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < MXN; j++)
            for (ll k = 0; k <= min(j, arr[i + 1]); k++)
                umn(dp[i + 1][j - k + (arr[i + 1] - k) / c], dp[i][j] + arr[i + 1] - k);
    }
    ll ans = 1e18;
    for (ll j = 0; j < MXN; j++) umn(ans, dp[n][j]);
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> c;
    for (ll i = 1; i <= n; i++) cin >> arr[i];
    cout << solve() << nl;
    while (m--) {
        ll x, y;
        cin >> x >> y;
        arr[x] = y;
        cout << solve() << nl;
    }
    return 0;
}

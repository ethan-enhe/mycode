#include <bits/stdc++.h>

#include <vector>

using namespace std;
#define fi first
#define se second

using ll = long long;
using pi = pair<ll, ll>;
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1005;

ll t, n, m, r;
vector<pi> lim[MXN];
bool dp[MXN][MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> m >> r;
        for (ll i = 0; i <= n; i++) lim[i].clear();
        while (m--) {
            ll i, l, r;
            cin >> i >> l >> r;
            lim[i].push_back({l, r});
        }
        for (ll j = 0; j <= r; j++) dp[0][j] = 1;
        for (ll i = 0; i <= n; i++) {
            for (auto [lj, rj] : lim[i])
                for (ll j = lj; j <= rj; j++) dp[i][j] = 0;
            for (ll j = 0; j <= r; j++) dp[i + 1][j] = dp[i][j] | (j ? dp[i][j - 1] : 0) | (j == r ? 0 : dp[i][j + 1]);
        }
        bool f = 0;
        for (ll j = 0; j <= r; j++)
            if (dp[n][j]) f = 1;
        cout << (f ? "YES" : "NO") << nl;
    }
    return 0;
}

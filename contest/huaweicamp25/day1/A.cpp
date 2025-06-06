#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e5 + 5;
const ll MXK = 17;
const ll MXU = 1 << MXK;
const ll INF = 1e10;
ll n, m, k;
vector<ll> g[MXN];
ll c[MXK];
ll dis[MXK][MXK];
ll dp[MXU][MXK];
void bfs(ll i) {
    static ll tdis[MXN];
    ll u = c[i];
    memset(tdis, 0x3f, sizeof(tdis));
    tdis[u] = 0;
    queue<ll> q;
    q.push(u);
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (auto v : g[u])
            if (tdis[v] >= INF) {
                tdis[v] = tdis[u] + 1;
                q.push(v);
            }
    }
    for (ll j = 0; j < k; j++) {
        dis[i][j] = tdis[c[j]];
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    while (m--) {
        ll a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cin >> k;
    for (ll i = 0; i < k; i++) {
        cin >> c[i];
    }
    for (ll i = 0; i < k; i++) {
        bfs(i);
        // for (ll j = 0; j < k; j++) {
        //     cout << dis[i][j] << " ";
        // }
        // cout << endl;
    }
    memset(dp, 0x3f, sizeof(dp));
    for (ll i = 0; i < k; i++) {
        dp[1 << i][i] = 1;
    }

    for (ll s = 0; s < (1 << k); s++) {
        for (ll i = 0; i < k; i++) {
            if (dp[s][i] < INF) {
                for (ll j = 0; j < k; j++) {
                    if (s & (1 << j)) continue;
                    ll nxs = s | (1 << j);
                    dp[nxs][j] = min(dp[nxs][j], dp[s][i] + dis[i][j]);
                }
            }
        }
    }
    ll ans = INF;
    for (ll i = 0; i < k; i++) ans = min(ans, dp[(1 << k) - 1][i]);
    if (ans < INF)
        cout << ans;
    else
        cout << -1;

    return 0;
}

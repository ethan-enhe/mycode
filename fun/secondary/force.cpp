#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e6 + 5;
const ll INF = 1e18;
map<ll, ll> dp[MXN];
ll ans[MXN], sum[MXN];

ll n;
ll arr[MXN];
vector<ll> g[MXN];

void umx(ll &x, ll y) { x = max(x, y); }
void mrg(ll x, ll y) {
    ans[x] += ans[y];
    for (auto &it : dp[x]) it.second += ans[y];
    for (auto &it : dp[y]) it.second += sum[x];

    for (auto &it : dp[y]) {
        ll pre = -INF;
        ll suf = -INF;
        for (auto &_it : dp[x]) {
            if (_it.first <= it.first)
                umx(pre, _it.first + _it.second);
            else
                umx(suf, _it.second);
        }
        umx(ans[x], it.second + pre - ans[y] - sum[x]);
        umx(ans[x], it.second + it.first + suf - ans[y] - sum[x]);
    }

    for (auto &it : dp[y]) {
        umx(dp[x][it.first], it.second);
    }
    sum[x] += ans[y];
}

void dfs(ll p, ll fa) {
    dp[p][arr[p]] = 0;
    ans[p] = 0;
    for (ll nx : g[p])
        if (nx != fa) {
            dfs(nx, p);
            mrg(p, nx);
        }
}

int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) cin >> arr[i];
    for (ll i = 1; i < n; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    cout << ans[1];
    return 0;
}

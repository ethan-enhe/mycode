#include <bits/stdc++.h>

#include <vector>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 2e5 + 5;
ll n, m, sum;
vector<pi> g[MXN];
vector<ll> path[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        sum += w;
    }
    ll pcnt = 0;
    for (auto [v, w] : g[1]) {
        ++pcnt;
        path[pcnt].push_back(0);
        path[pcnt].push_back(w);
        ll x = v;
        while (x != n) {
            path[pcnt].push_back(g[x][0].second);
            x = g[x][0].first;
        }
        sort(path[pcnt].begin(), path[pcnt].end());
    }
    sum /= path[1].size() - 1;
    ll l = 0, r = path[1].size() - 1;
    auto chk = [&](ll x) {
        ll r = 0;
        for (ll i = 1; i <= pcnt; i++) r += path[i][x];
        return r;
    };
    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        if (chk(mid) <= sum) {
            l = mid;
        } else
            r = mid - 1;
    }
    // cerr<<l<<endl;
    ll ans = 0;
    for (ll i = 1; i <= pcnt; i++) {
        for (ll j = 1; j <= l; j++) ans += (path[i][j] - path[i][j - 1]) * (j - 1);
    }
    ans += (sum - chk(l)) * l;
    cout << ans;

    return 0;
}

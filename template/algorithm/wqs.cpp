// File:             P4383
// Author:           ethan
// Created:          03/05/22
// Description:      wqs 二分

#include <bits/stdc++.h>

#include <cmath>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector

using ll = long long;
using pi = pair<ll, ll>;
//}}}
//{{{ Func
inline pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
inline pi &operator+=(pi &x, const pi &y) { return x.fi += y.fi, x.se += y.se, x; }
istream &operator>>(istream &is, pi &y) { return is >> y.fi >> y.se; }
ostream &operator<<(ostream &os, const pi &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
template <typename T>
inline void umx(T &x, const T &y) {
    x = max(x, y);
}
template <typename T>
inline void umn(T &x, const T &y) {
    x = min(x, y);
}
//}}}
const ll MXN = 3e5 + 5;

vector<pi> g[MXN];
ll n, m, cost, sumw;
pi dp[MXN][2];
ll fa[MXN], dfn[MXN], dfnc;

void dfs(ll p) {
    dfn[++dfnc] = p;
    for (pi &nx : g[p])
        if (nx.fi != fa[p]) {
            fa[nx.fi] = p;
            dfs(nx.fi);
        }
}
bool chk(ll x, bool cut = 1) {
    cost = x;
    for (ll i = n; i; i--) {
        ll p = dfn[i];
        pi tmp = dp[p][0] = {0, 0};
        dp[p][1] = {-cost, 1};
        for (pi &nx : g[p])
            if (nx.fi != fa[p]) {
                dp[p][0] += dp[nx.fi][0];
                umx(dp[p][0], dp[p][1] + dp[nx.fi][1] + pi{nx.se + cost, -1});

                dp[p][1] += dp[nx.fi][0];
                umx(dp[p][1], tmp + dp[nx.fi][1] + pi{nx.se, 0});
                tmp += dp[nx.fi][0];
            }
        umx(dp[p][0], dp[p][1]);
        if (cut && dp[p][0].se >= m) return 1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    ++m;
    for (ll i = 1; i < n; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        sumw += abs(w);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    dfs(1);
    ll l = -sumw, r = sumw;
    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        if (chk(mid))
            l = mid;
        else
            r = mid - 1;
    }
    chk(l, 0);
    cout << dp[1][0].fi + l * dp[1][0].se;
    return 0;
}

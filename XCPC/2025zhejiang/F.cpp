#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using pi = pair<int, int>;
const int MXN = 1e6 + 5;
const int INF = 1e9;
int t;
int n, m, k;
int c[MXN];
vector<int> g[MXN];

pair<pi, pi> dis[MXN];
bool upd(pair<pi, pi> &x, pi y) {
    if (y.se == 0) return 0;
    if (!x.fi.se) {
        x.fi = y;
        return 1;
    } else if (!x.se.se && x.fi.se != y.se) {
        x.se = y;
        return 1;
    }
    return 0;
}
bool upd(pair<pi, pi> &x, pair<pi, pi> y) {
    bool f = upd(x, y.fi);
    bool g = upd(x, y.se);
    return f || g;
}
queue<int> q;
bool bfs(int color) {
    for (int i = 1; i <= n; i++) {
        dis[i] = {{INF, 0}, {INF, 0}};
        if (c[i] == color) {
            dis[i].fi = {0, i};
            q.push(i);
        }
    }
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        // cerr<<p<<endl;
        auto cd = dis[p];
        ++cd.fi.fi;
        ++cd.se.fi;
        for (int nx : g[p]) {
            if (upd(dis[nx], cd)) q.push(nx);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dis[i].fi.fi + dis[i].se.fi <= k - 1) {
            return 1;
        }
    }
    return 0;
}
int main() {
    // freopen("./test.in","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
            g[i].clear();
        }
        while (m--) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        bool f = 0;
        for (int i = 1; i <= 50; i++) {
            if (bfs(i)) {
                // cerr<<i<<endl;
                f = 1;
            }
        }
        cout << (f ? "NO" : "YES") << '\n';
    }
    return 0;
}

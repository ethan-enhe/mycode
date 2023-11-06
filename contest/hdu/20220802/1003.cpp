#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
using ll = long long;
using pi = pair<ll, ll>;
const char nl = '\n';
const ll MXN = 4e6 + 5;

ll n, m, k, p, st, en, arr[MXN];
vector<pi> g[MXN];
vector<ll> nodes[MXN];
void dfs(ll p, ll fa, ll dpth) {
    nodes[dpth].push_back(p);
    for (auto nx : g[p])
        if (nx.fi != fa) dfs(nx.fi, p, dpth + 1);
}
struct node {
    ll p, dis;
    node(ll p, ll dis) : p(p), dis(dis) {}
    inline bool operator<(const node &b) const { return dis > b.dis; }
};
priority_queue<node> q;
ll dis[MXN];
bool vis[MXN];
void dj() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[st] = 0;
    q.push(node(st, 0));
    while (!q.empty()) {
        ll cur = q.top().p;
        q.pop();
        if (vis[cur]) continue;
        vis[cur] = 1;
        for (auto &nx : g[cur]) {
            ll nd = dis[cur] + nx.se;
            if (dis[nx.fi] > nd) {
                dis[nx.fi] = nd;
                q.push(node(nx.fi, nd));
            }
        }
    }
    cout << dis[en] << endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int task;
    cin >> task;
    while (task--) {
        cin >> n;
        m = n;
        for (ll i = 1; i < n; i++) {
            ll u, v, w;
            cin >> u >> v >> w;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        cin >> k >> p >> st >> en;
        dfs(1, 0, 1);
        for (ll i = 1; i <= n; i++)
            if (nodes[i].size() && nodes[i + k].size()) {
                for (ll j : nodes[i]) {
                    g[j].push_back({m + 1, p});
                    g[m + 2].push_back({j, 0});
                }
                for (ll j : nodes[i + k]) {
                    g[m + 1].push_back({j, 0});
                    g[j].push_back({m + 2, p});
                }
                m += 2;
            }
        dj();
        for (ll i = 1; i <= m; i++) {
            g[i].clear();
            nodes[i].clear();
        }
    }
    return 0;
}

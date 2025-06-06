#include <bits/stdc++.h>
using namespace std;
const int MXN = 1000005;
int n, m;
int deg[MXN], ans[MXN];
vector<int> G[MXN];
void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
    deg[u]++;
    deg[v]++;
}
struct node {
    int u, d;
    bool operator<(const node &rhs) const { return d > rhs.d; }
};
priority_queue<node> q;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        q.push({i, deg[i]});
        ans[i] = -1;
    }
    int mx = 0;
    while (!q.empty()) {
        int u = q.top().u;
        q.pop();
        if (ans[u] != -1) continue;
        mx = max(mx, deg[u]);
        ans[u] = mx;
        for (int v : G[u]) {
            --deg[v];
            q.push({v, deg[v]});
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " \n"[i == n];
        // if (ans[i] >= 100) cerr << "ERROR: " << i << endl;
    }
    return 0;
}

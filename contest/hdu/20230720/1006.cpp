#include <bits/stdc++.h>

#include <vector>
using namespace std;
const int MXN = 505;

vector<int> g[MXN];
int dis[MXN];
queue<int> q;
int n, circle;

void bfs(int x) {
    for (int i = 1; i <= n; i++) dis[i] = -1;
    dis[x] = 0;
    q.push(x);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
            if (v == x) circle = min(circle, dis[u] + 1);
        }
    }
}
void calc(int _n, const vector<pair<int, int>> &e) {
    n = _n;
    circle = 1e9;
    for (auto &i : e) g[i.first].push_back(i.second);
    for (int i = 1; i <= n; i++) bfs(i);
    cout << (circle >= (1e8) ? -1 : circle);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    calc(4,
         vector<pair<int, int>>{make_pair(1, 3), make_pair(1, 4), make_pair(3, 2), make_pair(3, 4), make_pair(4, 2)});
    return 0;
}

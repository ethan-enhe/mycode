#include <bits/stdc++.h>

#include <queue>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ld = long double;
using pi = pair<ld, ld>;
const ll MXN = 1e3 + 5;
const ld INF = 1e16;
ll n;
pi coor[MXN];
ld V1, V2;

ld spendt(ll i, ll j) {
    pi x = coor[i], y = coor[j];

    ld dx = y.fi - x.fi;
    ld dy = y.se - x.se;
    ld d = sqrtl(dx * dx + dy * dy);
    if (i == 0) {
        return d / V1;
    } else {
        if (V2 * 3. >= d)
            return d / V2;
        else
            return 3. + (d - V2 * 3) / V1;
    }
}
ld dis[MXN];
bool vis[MXN];
struct node {
    ld dis;
    ll v;
    bool operator<(const node &b) const { return dis > b.dis; }
};

priority_queue<node> q;
void dij() {
    q.push({dis[0] = 0, 0});
    while (!q.empty()) {
        ll p = q.top().v;
        q.pop();
        // cout << p << " " << dis[p] << endl;
        if (vis[p]) continue;
        vis[p] = 1;
        for (ll nx = 0; nx <= n + 1; nx++) {
            ld nd = dis[p] + spendt(p, nx);
            if (nd < dis[nx]) {
                q.push({dis[nx] = nd, nx});
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> coor[i].first >> coor[i].second;
        dis[i] = INF;
    }
    dis[n + 1] = INF;

    cin >> coor[0].first >> coor[0].second;
    cin >> coor[n + 1].first >> coor[n + 1].second;
    cin >> V1 >> V2;
    dij();
    cout.flags(ios::fixed);
    cout.precision(20);
    cout << dis[n + 1];

    return 0;
}

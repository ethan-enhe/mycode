#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 2505;
const ll INF = 1e18;
ll n, m, k;
vector<ll> g[MXN];
bool reachable[MXN][MXN];
ll mx[MXN][3];
ll arr[MXN], dis[MXN];
queue<ll> q;
void bfs(ll s) {
    memset(dis, -1, sizeof(dis));
    dis[s] = -1;
    q.push(s);
    while (!q.empty()) {
        ll p = q.front();
        q.pop();
        reachable[s][p] = 1;
        if (dis[p] < k)
            for (auto &nx : g[p]) {
                if (dis[nx] == -1) {
                    dis[nx] = dis[p] + 1;
                    q.push(nx);
                }
            }
    }
    reachable[s][s] = 0;
}
void upd(ll x, ll y) {
    if (arr[y] > arr[mx[x][0]]) {
        mx[x][2] = mx[x][1];
        mx[x][1] = mx[x][0];
        mx[x][0] = y;
    } else if (arr[y] > arr[mx[x][1]]) {
        mx[x][2] = mx[x][1];
        mx[x][1] = y;
    } else if (arr[y] > arr[mx[x][2]])
        mx[x][2] = y;
}
ll ans = -INF;
void updans(ll a, ll b, ll c, ll d) {
    if (!c || !d) return;
    // assert(c && d && a && b);
    // assert(b != c);
    ll tmp = arr[a] + arr[b] + arr[c] + arr[d];
    if (tmp > ans) ans = tmp;
}
int main(int argc, char *argv[]) {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    arr[0] = -INF;
    for (ll i = 2; i <= n; i++) cin >> arr[i];
    while (m--) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (ll i = 1; i <= n; i++) bfs(i);
    for (ll i = 2; i <= n; i++)
        if (reachable[1][i])
            for (ll j = 2; j <= n; j++)
                if (reachable[i][j]) upd(j, i);
    for (ll i = 2; i <= n; i++)
        for (ll j = 2; j <= n; j++)
            if (reachable[i][j]) {
                ll idi = mx[i][0] == j;
                ll idj = mx[j][0] == i;
                if (mx[i][idi] == mx[j][idj]) {
                    updans(i, j, mx[i][idi], mx[j][idj + 1 + (mx[j][idj + 1] == i)]);
                    updans(i, j, mx[i][idi + 1 + (mx[i][idi + 1] == j)], mx[j][idj]);
                } else
                    updans(i, j, mx[i][idi], mx[j][idj]);
            }
    cout << ans << endl;

    return 0;
}

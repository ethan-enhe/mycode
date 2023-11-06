#include <bits/stdc++.h>

#include <iomanip>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
const ll MXN = 5005;
const ll INF = 1e9;

ll n, m, k, arr[MXN];
ll s1, t1, s2, t2;
ll dis[MXN][MXN];
queue<ll> q;
vector<ll> g[MXN];
ll mnnotcommon[MXN];
void bfs(ll s, ll *dis) {
    for (ll i = 1; i <= n; i++) dis[i] = INF;
    q.push(s);
    dis[s] = 0;
    while (!q.empty()) {
        ll p = q.front();
        q.pop();
        for (ll nx : g[p]) {
            if (dis[nx] == INF) {
                dis[nx] = dis[p] + 1;
                q.push(nx);
            }
        }
    }
}
double gettime(ll x, ll y) {
    if (!x) return 0;
    ll div = 1 + y / x, rem = y % x;
    return (double)rem / (div + 1) + (double)(x - rem) / div;
}
double mn(ll x, ll y) {
    if (x > INF || y > INF) return INF;
    ll l = 0, r = k;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (gettime(x, mid) + gettime(y, k - mid) * 2 < gettime(x, mid + 1) + gettime(y, k - mid - 1) * 2)
            r = mid;
        else
            l = mid + 1;
    }
    return gettime(x, l) + gettime(y, k - l) * 2;
}
int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for (ll i = 1; i <= m; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> s1 >> t1 >> s2 >> t2;
    for (ll i = 1; i <= n; i++) bfs(i, dis[i]);
    memset(mnnotcommon, 0x3f, sizeof(mnnotcommon));
    mnnotcommon[0] = dis[s1][t1] + dis[s2][t2];

    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (dis[i][j] < INF){
                mnnotcommon[dis[i][j]] = min(mnnotcommon[dis[i][j]], dis[s1][i] + dis[s2][i] + dis[t1][j] + dis[t2][j]);
                mnnotcommon[dis[i][j]] = min(mnnotcommon[dis[i][j]], dis[s1][i] + dis[t2][i] + dis[t1][j] + dis[s2][j]);
            }
        }
    }
    double ans = 1e18;
    // cerr<<gettime(6, 0);
    for (ll i = 0; i <= m; i++) {
        // if (i == 1) cerr << mnnotcommon[i] << endl;
        ans = min(ans, mn(mnnotcommon[i], i));
    }
    cout << setprecision(11) << ans;

    return 0;
}

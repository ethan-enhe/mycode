#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<ll, ll>;
const ll INF = 1e18, MXN = 2505;

ll n, m, s, baseans, deg[MXN];
struct DSU {
    bool must[MXN];
    ll fa[MXN];
    void init(ll n) { iota(fa + 1, fa + 1 + n, 1); }
    ll find(ll x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;
    }
    bool merge(ll x, ll y) {
        x = find(x), y = find(y);
        return x == y ? 0 : (fa[y] = x, must[x] = 1, 1);
    }
} cur, save;

#define dis(x) (x.first - x.second)
bool cmp(const pi &x, const pi &y) { return dis(x) < dis(y); }
pi edge[MXN];
ll solve(ll x) {
    ll ans = 0, edgec = 0;
    cur = save;
    cur.merge(s, x);
    ++deg[s], ++deg[x];
    for (ll i = 1, last = 0; i <= n; i++)
        if (deg[i] & 1) {
            if (last) {
                ans += i - last;
                cur.merge(last, i);
                last = 0;
            } else
                last = i;
        }
    for (ll i = 1, last = -INF; i <= n; i++)
        if (cur.must[cur.find(i)]) {
            edge[++edgec] = {i, last};
            last = i;
        }
    sort(edge + 1, edge + 1 + edgec, cmp);
    for (int i = 1; i < edgec; i++)
        if (cur.merge(edge[i].first, edge[i].second)) ans += dis(edge[i]) << 1;
    --deg[s], --deg[x];
    return baseans + ans;
}

int main() {
    freopen("P6628.in", "r", stdin);
    freopen("P6628.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> s;
    save.init(n);
    while (m--) {
        ll u, v;
        cin >> u >> v;
        baseans += abs(v - u);
        save.merge(u, v);
        ++deg[u], ++deg[v];
    }
    for (int i = 1; i <= n; i++) cout << solve(i) << ' ';
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 1e5 + 5;
const ll MXK = 25;
const ll MXQ = 5e5 + 5;

ll sum[MXN];
void mdf(ll x, ll y) {
    for (; x <= n; x += x & (-x)) sum[x] += y;
}
ll pre(ll x) {
    ll r = 0;
    for (; x; x -= x & (-x)) r += sum[x];
    return r;
}
void mdf(ll l, ll r, ll y) {
    mdf(l, y);
    mdf(r + 1, -y);
}

struct stk {
    stack<pi> s;
    void insert(ll d, ll id) {
        pi ins = {d, id};
        while (!s.empty() && s.top() < ins) {
            s.pop();
        }
        s.push(ins);
    }
} contrib[MXN];

ll n, k, q;
vector<ll> g[MXN];
ll fa[MXN];
ll sz[MXN][MXK];
void dfs(ll p) {
    for (ll i = 0; i <= k; i++) {
        sz[p][i] = 1;
    }
    for (ll nx : g[p])
        if (nx != fa[p]) {
            fa[nx] = p;
            dfs(nx);
            for (ll i = 0; i <= k; i++) sz[p][i] += sz[nx][i - 1];
        }
}
int main() {
    ll t;
    while (t--) {
        cin >> n >> k >> q;
        for (ll i = 1; i <= n; i++) g[i].clear();
        for (ll i = 1; i < n; i++) {
            ll u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1);
    }

    return 0;
}

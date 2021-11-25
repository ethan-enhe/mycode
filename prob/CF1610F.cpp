#include <bits/stdc++.h>
using namespace std;

//{{{ Def
#define fi first
#define se second
#define pb push_back
#define log(fmt...) fprintf(stderr, fmt)

typedef long long ll;
typedef pair<ll, ll> pi;
//}}}
const ll MXN = 1e6 + 5;
ll n, m;
ll e[MXN][3], cure[MXN], ans[MXN];
bool cnt[MXN][3], has[MXN][3];
ll trans(ll x, ll y) {
    if (cnt[x][1]) {
        if (cnt[x][y] && !has[x][y]) {
            has[x][y] = 1;
            return x;
        }
        return x + n * y;
    }
    return x;
}
vector<pi> g[MXN];
void ae(ll x, ll y, ll z) {
    log("%lld %lld\n", x, y);
    g[x].pb({y, z});
}
void build(ll x, ll y, ll w, ll id) {
    log("%lld %lld %lld:\n", x, y, w);
    x = trans(x, w), y = trans(y, w);
    ae(x, y, id);
    ae(y, x, -id);
}
void dfs(ll p) {
    for (ll &i = cure[p]; i < g[p].size();) {
        pi &nx = g[p][i++];
        if (ans[abs(nx.se)]) continue;
        if(p==2 || nx.fi==2)log("%lld %lld %lld\n",p,nx.fi,nx.se);
        ans[abs(nx.se)] = 1 + (nx.se < 0);
        dfs(nx.fi);
    }
}
int deg[MXN];
void mod(int x, int y, int w, int tp) {
    if (tp == 2) swap(x, y);
    deg[x] += w, deg[y] -= w;
}
#define cure e[i][0], e[i][1], e[i][2]

int main() {
    freopen("test.in", "r", stdin);
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < 3; j++) scanf("%lld", &e[i][j]);
        cnt[e[i][0]][e[i][2]] ^= 1;
        cnt[e[i][1]][e[i][2]] ^= 1;
    }
    for (int i = 1; i <= m; i++) build(cure, i);
    ll last = 0;
    for (int i = 1; i <= n * 3; i++)
        if (g[i].size() & 1) {
            if (last) {
                ae(last, i, 0);
                ae(i, last, 0);
                last = 0;
            } else
                last = i;
        }
    for (int i = 1; i <= n * 3; i++) dfs(i);
    ll res = 0;
    for (int i = 1; i <= n; i++) res += cnt[i][1];
    printf("%lld\n", res);
    for (int i = 1; i <= m; i++) {
        putchar('0' + ans[i]);
        mod(cure, ans[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (cnt[i][1] && abs(deg[i]) != 1) {
            cerr << endl << i;
            return 1;
        }
    }

    return 0;
}
/*
5 6
2 4 2
5 2 2
2 4 2
5 2 1
5 4 2
3 1 2

*/

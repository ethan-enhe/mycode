#include <bits/stdc++.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());
ll ri(const ll &l, const ll &r) { return uniform_int_distribution<ll>(l, r)(mr); }

const char nl = '\n';
const ll MXN = 1e5 + 5, INF = 1e18;
struct rng {
    ll l, r;
} arr[MXN];

ll n, m, sq;
ll w(const rng &x, const rng &y) { return min(abs(x.l - y.l) + abs(x.r - y.r), x.r - x.l + 1 + y.r - y.l + 1); }

vector<ll> g[MXN];

void add_edge(ll u, ll v) {
    /* cerr << u << " " << v << endl; */
    g[u].push_back(v);
    g[v].push_back(u);
}

void mst() {
    static ll dis[MXN], pre[MXN];
    fill(dis, dis + 1 + m, INF);
    for (ll i = 0, cur = 0; i <= m; i++) {
        if (cur) add_edge(pre[cur], cur);
        dis[cur] = -1;
        ll nx, mn = INF;
        for (ll j = 1; j <= m; j++)
            if (dis[j] != -1) {
                ll _d = w(arr[cur], arr[j]);
                if (_d < dis[j]) {
                    dis[j] = _d;
                    pre[j] = cur;
                }
                if (dis[j] < mn) {
                    mn = dis[j];
                    nx = j;
                }
            }
        cur = nx;
    }
}

ll ord[MXN], ind;
void dfs(ll p, ll fa) {
    ord[ind++] = p;
    for (ll nx : g[p])
        if (nx != fa) dfs(nx, p);
}

bool MO_cmp(ll a, ll b) {
    rng &x = arr[a], &y = arr[b];
    ll xb = x.l / sq, yb = y.l / sq;
    if (xb == yb)
        return (xb & 1) ? x.r > y.r : x.r < y.r;
    else
        return xb < yb;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    sq = sqrt(m * 2);
    for (ll i = 1; i <= m; i++) {
        /* cin >> arr[i].l >> arr[i].r; */
        arr[i] = {ri(1, n), ri(1, n)};
        if (arr[i].l > arr[i].r) swap(arr[i].l, arr[i].r);
    }
    mst();
    dfs(0, -1);
    ll ans1 = 0, ans2 = 0, ans3 = INF;

    for (ll i = 1; i <= m; i++) ans1 += w(arr[ord[i]], arr[ord[i - 1]]);
    sort(ord + 1, ord + 1 + m, MO_cmp);
    for (ll i = 1; i <= m; i++) ans2 += w(arr[ord[i]], arr[ord[i - 1]]);

    for (ll i = 1; i <= 1; i++) {
        ll tmp = 0;
        iota(ord + 1, ord + 1 + m, 1);
        shuffle(ord + 1, ord + 1 + m, mr);
        for (ll j = 1; j <= m; j++) tmp += w(arr[ord[j]], arr[ord[j - 1]]);
        ans3 = min(ans3, tmp);
    }

    cout << ans1 << nl << ans2 << nl << ans3 << nl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e5 + 5;
ll n, m, s, B, R;

const ll LIM = 400;
const ll MX_BIG = 400;
vector<ll> g[MXN], inv[MXN];
ll mrk[MXN];
ll e_cnt[MX_BIG][MX_BIG];
ll id[MXN], idc;
ll cnt() {
    ll res = 0;
    ll small3 = 0;
    ll big3 = 0;
    for (ll u = 1; u <= n; u++) {
        for (ll v : inv[u]) mrk[v]++;
        if (g[u].size() <= LIM) {
            for (ll v : g[u]) {
                if (v == u) continue;
                if (g[v].size() > LIM) continue;
                // cerr << u << " " << v << endl;
                for (ll w : g[v]) small3 += (g[w].size() <= LIM && w != v && w != u) ? mrk[w] : 0;
            }
        } else {
            id[u] = ++idc;
            for (ll v : g[u]) {
                if (v == u) continue;
                if (g[v].size() > LIM) continue;
                for (ll w : g[v]) {
                    res += (w != v && w != u) ? mrk[w] : 0;
                }
            }
        }
        for (ll v : inv[u]) mrk[v] = 0;
    }
    for (ll u = 1; u <= n; u++)
        if (g[u].size() > LIM) {
            for (ll v : g[u])
                if (v != u && g[v].size() > LIM) ++e_cnt[id[u]][id[v]];
        }

    for (ll i = 1; i <= idc; i++)
        for (ll j = 1; j <= idc; j++)
            for (ll k = 1; k <= idc; k++) big3 += e_cnt[i][j] * e_cnt[j][k] * e_cnt[k][i];
    return res + small3 / 3 + big3 / 3;
}
ll self_loop = 0;
ll undi_edge = 0;
map<ll, ll> multi_edge[MXN];
void ae(ll u, ll v) {
    if (u == v)
        ++self_loop;
    else {
        ++multi_edge[u][v];
        undi_edge += multi_edge[v][u];
    }
    g[u].push_back(v);
    inv[v].push_back(u);
}
ll b[MXN], r[MXN];
ll db[MXN], dr[MXN];
const ll INF = 1e9;
ll getdis(ll p, ll targ, ll *x, ll *y) {
    if (p == targ) return y[p] = 0;
    if (y[p] >= 0) return y[p];
    if (y[p] == -2) return INF;
    y[p] = -2;
    return y[p] = getdis(x[p], targ, x, y) + 1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> B >> R;
    for (ll i = 1; i <= n; i++) {
        cin >> b[i];
        db[i] = dr[i] = -1;
    }
    for (ll i = 1; i <= n; i++) cin >> r[i];
    for (ll i = 1; i <= n; i++) {
        ll x = getdis(i, B, b, db);
        ll y = getdis(i, R, r, dr);
        if (x >= INF || y >= INF) continue;
        ae(x + 1, y + 1);
    }
    ll res = cnt();
    cout << res + undi_edge * self_loop + self_loop * (self_loop - 1) * (self_loop - 2) / 6;
    return 0;
}

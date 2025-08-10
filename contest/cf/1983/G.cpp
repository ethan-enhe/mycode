#include <bits/stdc++.h>

#include <cstdio>
#include <vector>
using ll = long long;
using namespace std;
const ll MXN = 5e5 + 5, LG = 19;
ll n, m, arr[MXN];
vector<ll> g[MXN];
ll anc[MXN][LG + 1], dpth[MXN];
void dfs(ll p, int f) {
    anc[p][0] = f, dpth[p] = dpth[f] + 1;
    for (ll i = 0; anc[p][i]; i++) anc[p][i + 1] = anc[anc[p][i]][i];
    for (ll nx : g[p])
        if (nx ^ f) dfs(nx, p);
}
inline ll lca(int x, int y) {
    if (dpth[x] < dpth[y]) swap(x, y);
    ll tmp = dpth[x] - dpth[y];
    for (ll i = LG; ~i; i--)
        if ((tmp >> i) & 1) x = anc[x][i];
    if (x == y) return x;
    for (ll i = LG; ~i; i--)
        if (anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}

vector<pair<ll, ll>> ask[MXN];
ll stk[MXN], stksum[LG + 1][MXN], stkxor[LG + 1][MXN];

inline ll getv(ll *s, ll i) { return i >= 0 ? s[i] : 0; }
inline ll getsum(ll *s, ll l, ll r) { return getv(s, r) - getv(s, l - 1); }
ll ans=0;
void dfs(ll p, ll f) {
    ll d = dpth[p];
    stk[d] = p;
    for (ll i = 0; i <= LG; i++) {
        stksum[i][d] = stksum[i][d - 1] + (arr[i] >> i) & 1;
        stkxor[i][d] = getv(stkxor[i], d - (1 << (i + 1))) + getsum(stksum[i], d + 1 - (1 << i), d) + (1 << (i - 1)) -
                       getsum(stksum[i], d + 1 - (1 << (i + 1)), d - (1 << i));
    }
    for (auto [id, x] : ask[p]) {
        for (ll i = 0; i <= LG; i++) {
            ll v = x;
            ll mask0 = (1 << (i)) - 1;
            ll mask1 = (1 << (i + 1)) - 1;
            if (((v >> i) & 1) == 0) {
                ll go = v & mask0;
                v += go;
            }
        }
    }
    for (auto nx : g[p])
        if (nx != f) dfs(nx, nx);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) {
            cin >> arr[i];
            g[i].clear();
            ask[i].clear();
        }
        for (ll i = 1; i < n; i++) {
            ll x, y;
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        dfs(1, 0);
        cin >> m;
        for (ll i = 1; i <= m; i++) {
            ll x, y;
            cin >> x >> y;
            ll l = lca(x, y);
            ll dis = dpth[x] + dpth[y] - 2 * dpth[l] + 1;
            ask[x].push_back({i, 1});
            ask[y].push_back({i, -dis});
        }
    }
    return 0;
}

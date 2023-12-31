#include <bits/stdc++.h>

#include <algorithm>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 5e5 + 5;
const ll INF = 1e18;
const ll LG = 22;
ll dp[MXN];
ll ans[MXN], sum[MXN];

ll n;
ll arr[MXN];
ll pool[MXN];
vector<ll> g[MXN];

void umx(ll &x, ll y) { x = max(x, y); }
struct node {
    ll tag, ls, rs;
    pi mx; //{v,v+i}
    node() {
        tag = ls = rs = 0;
        mx = {-INF, -INF};
    }
};
pi operator+(const pi &a, const pi &b) { return pi{max(a.first, b.first), max(a.second, b.second)}; }

node t[MXN * LG];
ll nodec;
ll nnode() { return ++nodec; }
void pull(ll p) { t[p].mx = t[t[p].ls].mx + t[t[p].rs].mx; }
void addt(ll &p, ll k) {
    // 需要新建点吗？
    if (!p) return; // p = nnode();
    t[p].tag += k;
    t[p].mx.first += k;
    t[p].mx.second += k;
}
void push(ll p) {
    if (t[p].tag) {
        addt(t[p].ls, t[p].tag);
        addt(t[p].rs, t[p].tag);
        t[p].tag = 0;
    }
}

void touch(ll &p, ll l, ll r, ll qi) {
    if (!p) p = nnode();
    if (l == r) {
        t[p].mx = {0, pool[l]};
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    if (qi <= mid)
        touch(t[p].ls, l, mid, qi);
    else
        touch(t[p].rs, mid + 1, r, qi);
    pull(p);
}
// pi qry(ll p, ll l, ll r, ll ql, ll qr) {
//     if (!p) return t[0].mx;
//     if (r < ql || l > qr) return t[0].mx;
//     if (ql <= l && r <= qr) return t[p].mx;
//     ll mid = (l + r) >> 1;
//     return qry(t[p].ls, l, mid, ql, qr) + qry(t[p].rs, mid + 1, r, ql, qr);
// }
ll mrg(ll l, ll r, ll rx, ll ry, pi prex, pi sufx, ll &upd) {
    // cerr << l << " " << r << endl;
    if (!rx || !ry) {
        umx(upd, prex.second + t[ry].mx.first);
        umx(upd, sufx.first + t[ry].mx.second);
        // dosth
        return rx | ry;
    }
    if (l == r) {
        prex = prex + t[rx].mx;
        umx(upd, prex.second + t[ry].mx.first);
        umx(upd, sufx.first + t[ry].mx.second);
        t[rx].mx = t[rx].mx + t[ry].mx;
        // dosth
        return rx;
    }
    ll mid = (l + r) >> 1;
    push(rx);
    push(ry);
    t[rx].ls = mrg(l, mid, t[rx].ls, t[ry].ls, prex, sufx + t[t[rx].rs].mx, upd);
    t[rx].rs = mrg(mid + 1, r, t[rx].rs, t[ry].rs, prex + t[t[rx].ls].mx, sufx, upd);
    pull(rx);
    return rx;
}

void mrgdp(ll x, ll y) {
    ans[x] += ans[y];
    addt(dp[x], ans[y]);
    addt(dp[y], sum[x]);

    ll tmp = -INF;
    mrg(1, n, dp[x], dp[y], {-INF, -INF}, {-INF, -INF}, tmp);
    umx(ans[x], tmp - ans[y] - sum[x]);

    sum[x] += ans[y];
}

void dfs(ll p, ll fa) {
    touch(dp[p], 1, n, arr[p]);
    ans[p] = 0;
    for (ll nx : g[p])
        if (nx != fa) {
            dfs(nx, p);
            mrgdp(p, nx);
        }
}

int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        pool[i] = arr[i];
    }
    sort(pool + 1, pool + 1 + n);
    for (ll i = 1; i <= n; i++) {
        arr[i] = lower_bound(pool + 1, pool + 1 + n, arr[i]) - pool;
    }
    for (ll i = 1; i < n; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    cout << ans[1];
    return 0;
}

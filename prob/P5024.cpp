#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN = 1e5 + 5, INF = 1e16, BIG = 1e11;
struct mat {
    ll d[2][2];
    inline mat(ll x = INF, ll y = INF, ll z = INF, ll w = INF) {
        d[0][0] = x, d[0][1] = y, d[1][0] = z, d[1][1] = w;
    }
    inline void operator+=(const mat &y) {
        d[0][0] += y.d[0][0];
        d[0][1] += y.d[0][1];
        d[1][0] += y.d[1][0];
        d[1][1] += y.d[1][1];
    }
    inline mat operator*(const mat &y) const {
        return mat(min(d[0][0] + y.d[0][0], d[0][1] + y.d[1][0]),
                   min(d[0][0] + y.d[0][1], d[0][1] + y.d[1][1]),
                   min(d[1][0] + y.d[0][0], d[1][1] + y.d[1][0]),
                   min(d[1][0] + y.d[0][1], d[1][1] + y.d[1][1]));
    }
};
#define ls (p << 1)
#define rs (p << 1 | 1)
mat t[MXN << 2], f[MXN];
void mod(ll p, ll l, ll r, ll mi) {
    if (l == r) {
        t[p] = f[l];
        return;
    }
    ll mid = (l + r) >> 1;
    if (mi <= mid)
        mod(ls, l, mid, mi);
    else
        mod(rs, mid + 1, r, mi);
    t[p] = t[rs] * t[ls];
}
mat que(ll p, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) return t[p];
    ll mid = (l + r) >> 1;
    mat res(0, INF, INF, 0);
    if (qr > mid) res = que(rs, mid + 1, r, ql, qr);
    if (ql <= mid) res = res * que(ls, l, mid, ql, qr);
    return res;
}
ll n, m, arr[MXN];
vector<ll> g[MXN];

ll sz[MXN], top[MXN], tail[MXN], son[MXN], fa[MXN], dfn[MXN], dfnc;
ll dp[MXN][2];
void dfs1(ll p) {
    sz[p] = 1;
    dp[p][1] = arr[p];
    for (ll nx : g[p])
        if (nx != fa[p]) {
            fa[nx] = p;
            dfs1(nx);
            sz[p] += sz[nx];
            dp[p][0] += dp[nx][1];
            dp[p][1] += min(dp[nx][0], dp[nx][1]);
            if (sz[nx] > sz[son[p]]) son[p] = nx;
        }
}
void dfs2(ll p) {
    dfn[p] = ++dfnc;
    if (son[p]) {
        top[son[p]] = top[p];
        dfs2(son[p]);
        ll s1 = 0, s01 = arr[p];
        for (ll nx : g[p])
            if (nx != fa[p] && nx != son[p]) {
                top[nx] = nx;
                s1 += dp[nx][1];
                s01 += min(dp[nx][0], dp[nx][1]);
                dfs2(nx);
            }
        f[dfn[p]] = mat(INF, s01, s1, s01);
    } else {
        tail[top[p]] = p;
        f[dfn[p]] = mat(0, arr[p], INF, INF);
    }
    mod(1, 1, n, dfn[p]);
}
inline void mod(ll x) {
    if (top[x] == 1) {
        mod(1, 1, n, dfn[x]);
        return;
    }
    mat bef = que(1, 1, n, dfn[top[x]], dfn[tail[top[x]]]);
    mod(1, 1, n, dfn[x]);
    mat lat = que(1, 1, n, dfn[top[x]], dfn[tail[top[x]]]);
    ll delt1 = lat.d[0][1] - bef.d[0][1],
       delt01 = min(lat.d[0][0], lat.d[0][1]) - min(bef.d[0][0], bef.d[0][1]);
    f[dfn[fa[top[x]]]] += mat(0, delt01, delt1, delt01);
    mod(fa[top[x]]);
}
int main() {
    char useless[10];
    scanf("%lld%lld%s", &n, &m, useless);
    for (ll i = 1; i <= n; i++) scanf("%lld", arr + i);
    for (ll i = 1, x, y; i < n; i++) {
        scanf("%lld%lld", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    while (m--) {
        ll a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        ll delta = b ? -arr[a] : BIG, deltc = d ? -arr[c] : BIG;
        f[dfn[a]] += mat(0, delta, 0, delta);
        mod(a);
        f[dfn[c]] += mat(0, deltc, 0, deltc);
        mod(c);
        mat res = que(1, 1, n, 1, dfn[tail[1]]);
        ll ans = min(res.d[0][0], res.d[0][1]);
        if (b) ans += arr[a];
        if (d) ans += arr[c];
        printf("%lld\n", ans > BIG ? -1 : ans);

        f[dfn[a]] += mat(0, -delta, 0, -delta);
        mod(a);
        f[dfn[c]] += mat(0, -deltc, 0, -deltc);
        mod(c);
    }
    return 0;
}

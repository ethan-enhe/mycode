#include <bits/stdc++.h>
#define ls (p << 1)
#define rs (p << 1 | 1)
#define wdown(x) (cnt[x] < 0 ? -1 : 1)
#define wup(x) (cnt[x] > 0 ? -1 : 1)
using namespace std;
using ll = long long;

const ll INF = 1e18, MXN = 1e5 + 5;
// cnt 表示经过次数，正表示向下
ll n, m, cap[MXN], cnt[MXN];
ll dp[MXN], id[MXN];
void upd(ll p) {
    if (cap[p])
        dp[p] = 0, id[p] = p;
    else
        dp[p] = INF;
    if (ls <= n) {
        ll tmp = dp[ls] + wdown(ls);
        if (tmp < dp[p]) dp[p] = tmp, id[p] = id[ls];
    }
    if (rs <= n) {
        ll tmp = dp[rs] + wdown(rs);
        if (tmp < dp[p]) dp[p] = tmp, id[p] = id[rs];
    }
}
ll mod(ll p) {
    ll _p = p, mn = dp[p], q = id[p], lca = p, sumup = 0;
    while (p > 1) {
        sumup += wup(p);
        ll tmp = dp[p ^ 1] + wdown(p ^ 1) + sumup;
        if (tmp < mn) mn = tmp, q = id[p ^ 1], lca = p >> 1;
        p >>= 1;
        if (cap[p] && sumup < mn) mn = sumup, q = p, lca = p;
    }
    p = _p;
    --cap[q];
    bool f = 1;
    while (q) {
        upd(q);
        if (q == lca) break;
        q >>= 1;
    }
    f = 1;
    while (p) {
        upd(p);
        if (p == lca) f = 0;
        cnt[p] -= f, p >>= 1;
    }
    return mn;
}
int main() {
    /* freopen("P6122.in", "r", stdin); */
    /* freopen("P6122.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) cin >> cap[i];
    dp[n + 1] = INF;
    for (ll i = n; i; i--) upd(i);
    ll ans = 0;
    while (m--) {
        ll x;
        cin >> x;
        ans += mod(x);
        cout << ans << " ";
    }
    return 0;
}

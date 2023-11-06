// P3387 【模板】缩点
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN = 1e6 + 5;
vector<ll> e[MXN], d[MXN];
ll n, m, s, q, arr[MXN], dp[MXN];
ll col[MXN], tot[MXN], colc;
ll dfn[MXN], low[MXN], dfsc;
bool instk[MXN];
stack<ll> st;
inline void tj(ll p) {
    dfn[p] = low[p] = ++dfsc;
    st.push(p), instk[p] = 1;
    for (ll nx : e[p]) {
        if (!dfn[nx])
            tj(nx), low[p] = min(low[p], low[nx]);
        else if (instk[nx])
            low[p] = min(low[p], dfn[nx]);
    }

    if (dfn[p] == low[p]) {
        ll x;
        ++colc;
        do {
            x = st.top();
            st.pop();
            col[x] = colc, instk[x] = 0;
            tot[colc] += arr[x];
        } while (x != p);
    }
}
inline ll dfs(ll p) {
    if (~dp[p]) return dp[p];
    if (p == col[s]) return dp[p] = tot[p];
    dp[p] = tot[p];
    for (ll nx : d[p]) dp[p] = max(dp[p], dfs(nx) + tot[p]);
    return dp[p];
}

int main() {
    scanf("%lld%lld", &n, &m);
    for (ll i = 1, ts, tt; i <= m; i++) {
        scanf("%lld%lld", &ts, &tt);
        e[ts].push_back(tt);
    }
    for (ll i = 1; i <= n; i++) scanf("%lld", arr + i);
    for (ll i = 1; i <= n; i++)
        if (!dfn[i]) tj(i);
    for (ll i = 1; i <= n; i++)
        for (ll nx : e[i])
            if (col[nx] != col[i]) d[col[nx]].push_back(col[i]);
    memset(dp, -1, sizeof(dp));
    scanf("%lld%lld", &s, &q);
    ll ans = 0;
    while (q--) {
        ll x;
        scanf("%lld", &x);
        ans = max(ans, dfs(col[x]));
    }
    printf("%lld", ans);
    return 0;
}

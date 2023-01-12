#include <bits/stdc++.h>
#define ae(x, y) (e[x].push_back(y), deg[y]++)
using namespace std;
typedef long long ll;
const ll MXN = 1e6 + 5;
const ll INF = 1e18;

vector<ll> e[MXN];
ll n, arr[MXN], deg[MXN];
ll dp[MXN][2];
inline void topo() {
    queue<ll> q;
    for (ll i = 1; i <= n; i++) {
        if (deg[i] == 1) q.push(i);
        dp[i][1] = arr[i];
    }
    while (!q.empty()) {
        ll p = q.front();
        q.pop();
        for (ll nx : e[p])
            if (--deg[nx]) {
                dp[nx][1] += dp[p][0];
                dp[nx][0] += max(dp[p][1], dp[p][0]);
                if (deg[nx] == 1) q.push(nx);
            }
    }
}
inline ll fnx(ll p, ll last) {
    for (ll nx : e[p])
        if (deg[nx] == 2 && nx != last) return nx;
    return last;
}
inline ll cal(ll s) {
    ll p = fnx(s, -1), last = s, tmp, tdp[2][2] = {{dp[s][0], -INF}, {-INF, dp[s][1]}};
    while (p != s) {
        deg[p] = 0;
        for (ll i = 0; i < 2; i++) {
            tdp[i][0] = max(tdp[i][1], tmp = tdp[i][0]) + dp[p][0];
            tdp[i][1] = tmp + dp[p][1];
        }
        tmp = p, p = fnx(p, last), last = tmp;
    }
    return max(tdp[1][0], max(tdp[0][0], tdp[0][1]));
}

int main() {
    scanf("%lld", &n);
    for (ll i = 1, tt; i <= n; i++) {
        scanf("%lld%lld", arr + i, &tt);
        ae(i, tt);
        ae(tt, i);
    }
    topo();
    ll ans = 0;
    for (ll i = 1; i <= n; i++)
        if (deg[i] == 2) ans += cal(i);
    printf("%lld", ans);
    return 0;
}

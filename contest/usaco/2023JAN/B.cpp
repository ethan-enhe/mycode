#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
using ld = long double;

const ld EPS = 1e-8;
const ll N = 18, NR = 5e5;
const ll INF = 5e18;
const ll MXS = (ll)1e9 + 7;
ll n, m;
ll gen[NR];
ll dp[NR][N];

ll dis[N][N];

pi line[N][NR];

void floyd() {
    for (ll k = 0; k < n; k++)
        for (ll i = 0; i < n; i++)
            for (ll j = 0; j < n; j++) dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
}

pi tmp[NR];
ld itsc(pi x, pi y) { return ld(y.se - x.se) / (x.fi - y.fi); }
void convex_hull(pi *arr) {
    ll top = 0;
    for (ll i = 0; i < (1 << n); i++) {
        while (top && tmp[top].fi == arr[i].fi) --top;
        while (top >= 2 && itsc(tmp[top], arr[i]) <= itsc(tmp[top], tmp[top - 1]) + EPS) --top;
        tmp[++top] = arr[i];
    }
    arr[0].fi = top;
    do arr[top] = tmp[top];
    while (--top);
}
ll getmn(pi *arr, ll x) {
    ll l = 1, r = arr[0].fi;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (mid != arr[0].fi && itsc(arr[mid], arr[mid + 1]) <= x)
            l = mid + 1;
        else
            r = mid;
    }
    return arr[l].fi * x + arr[l].se;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    memset(dis, 0x3f, sizeof(dis));
    cin >> n >> m;
    for (ll i = 0; i < n; i++) {
        cin >> gen[1 << i];
        dis[i][i] = 0;
    }

    while (m--) {
        ll u, v, w;
        cin >> u >> v >> w;
        dis[u - 1][v - 1] = w;
    }
    floyd();

    for (ll i = 1; i < (1 << n); i++) {
        ll lbt = i & (-i);
        gen[i] = gen[i ^ lbt] + gen[lbt];
    }
    memset(dp, 0x3f, sizeof(dp));
    memset(dp[0], 0, sizeof(dp[0]));
    for (ll i = 0; i < (1 << n); i++)
        for (ll j = 0; j < n; j++)
            if (dp[i][j] < INF) {
                for (ll k = 0; k < n; k++)
                    if (!((i >> k) & 1) && dis[j][k] < MXS) {
                        ll nxd = dp[i][j] + gen[i] * dis[j][k];
                        ll nxi = i | (1 << k);
                        dp[nxi][k] = min(dp[nxi][k], nxd);
                    }
                // cerr << j << " " << dp[i][j] << " + " <<  << " x" << '\n';
                line[j][i] = {gen[((1 << n) - 1) ^ i], dp[i][j]};
            }
    for (ll i = 0; i < n; i++) {
        sort(line[i], line[i] + (1 << n), [](auto x, auto y) { return x > y; });
        convex_hull(line[i]);
        // for (ll j = 1; j <= line[i][0].fi; j++) cerr << line[i][j].fi << "," << line[i][j].se << " ";
        // cerr << endl;
    }
    cin >> m;
    while (m--) {
        ll x, y;
        cin >> x >> y;
        ll ans = gen[(1 << n) - 1] * x - getmn(line[y - 1], x);
        cout << ans << '\n';
    }
    return 0;
}

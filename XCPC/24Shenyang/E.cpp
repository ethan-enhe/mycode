#include <bits/stdc++.h>
#include <unistd.h>
#define fi first
#define se second
using namespace std;
using ll = int;
using pi = pair<ll, ll>;

vector<pi> op = {{1, 0}, {2, 0}, {4, 0}, {8, 0}, {3, 0}, {12, 0}, {5, 0}, {10, 0}, {15, 0}};
const ll STAT = 16;
const ll U = 1 << STAT;
const ll INF = 1e9;

ll t, m;
ll a0, a1, a2, a3;

ll dis[STAT][STAT];
ll dp[U][STAT];

ll mncost[U];

ll read_state() {
    ll x = 0;
    string s;
    cin >> s;
    if (s[0] != '1') x ^= 1;
    if (s[1] != '1') x ^= 2;
    cin >> s;
    if (s[0] != '1') x ^= 4;
    if (s[1] != '1') x ^= 8;
    return x;
}
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    cin >> a0 >> a1 >> a2 >> a3;
    op[0].se = op[1].se = op[2].se = op[3].se = a0;
    op[4].se = op[5].se = a1;
    op[6].se = op[7].se = a2;
    op[8].se = a3;

    memset(dis, 0x3f, sizeof(dis));
    for (ll i = 0; i < STAT; i++) {
        dis[i][i] = INF;
        for (auto [x, y] : op) dis[i][i ^ x] = min(dis[i][i ^ x], y);
    }

    for (ll k = 0; k < STAT; k++)
        for (ll i = 0; i < STAT; i++)
            for (ll j = 0; j < STAT; j++) dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (ll i = 0; i < U; i++) {
        mncost[i] = INF;
        for (ll j = 0; j < STAT; j++) {
            if (dp[i][j] >= INF) continue;
            mncost[i] = min(mncost[i], dp[i][j]);
            for (ll k = 0; k < STAT; k++) {
                ll v = 1 << k, nxi = i ^ v;
                if (i & v) continue;
                dp[nxi][k] = min(dp[nxi][k], dp[i][j] + dis[j][k]);
            }
        }
    }
    for (ll i = 0; i < STAT; i++) {
        ll v = 1 << i;
        for (ll i = (U - 1); ~i; i--) {
            if (!(i & v)) mncost[i] = min(mncost[i], mncost[i ^ v]);
        }
    }

    while (t--) {
        ll s = 0;
        cin >> m;
        while (m--) {
            ll x = read_state();
            s |= 1 << x;
        }
        cout << mncost[s] << '\n';
    }
    return 0;
}

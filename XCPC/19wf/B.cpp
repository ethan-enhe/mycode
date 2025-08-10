#include <bits/stdc++.h>

#include <cmath>
#define fi first
#define se second
using namespace std;
using db = long double;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 1e4 + 5;
const ll INF = 1e18;
ll n, h, a, b;
pi coor[MXN];

const ll NR = 1e5 + 5;
ll id[NR];
ll low_bound(db x) {
    ll i = id[max(0ll, min((ll)x, NR - 1))];
    if (coor[i].fi < x) ++i;
    return i;
}
ll up_bound(db x) {
    ll i = id[max(0ll, min((ll)x, NR - 1))];
    if (coor[i].fi <= x) ++i;
    return i;
}
vector<pi> get_l_rng(ll pid, ll rid) {
    pi p = coor[pid];
    db x = p.fi, y = p.se, r = coor[rid].fi;
    if (y > h) return {};
    db b = (-r + x - h + y) * 2;
    db c = (r * r + x * x - r * x * 2 + h * h + y * y - h * y * 2);
    db delta = b * b - c * 4;
    if (delta < 0) return {};
    delta = sqrt(delta);

    // cout << b << " " << c << endl;
    // cout << (-b - delta) << " " << (-b + delta) << endl;
    pi r1 = {low_bound(r - (-b + delta)), up_bound(r - (-b - delta)) - 1};
    pi r2 = {low_bound(r - (h - y) * 2), n};
    if (r1.fi > r1.se) {
        return vector<pi>{r2};
    } else {
        if (r2.fi <= r1.se) {
            return {pi{min(r1.fi, r2.fi), r2.se}};
        } else
            return {r1, r2};
    }
}
ll dp[MXN];
ll delt[MXN];
void mdf(ll x, ll v, ll i, ll &s) {
    delt[x] += v;
    if (x > i) s += v;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> h >> a >> b;
    for (ll i = 1; i <= n; i++) {
        cin >> coor[i].fi >> coor[i].se;
    }
    coor[n + 1].fi = NR;
    for (ll i = 1; i <= n; i++) {
        for (ll j = coor[i].fi; j < coor[i + 1].fi; j++) id[j] = i;
    }
    coor[n + 1].fi = INF;
    coor[0].fi = -INF;

    memset(dp, 0x3f, sizeof(dp));
    dp[1] = a * (h - coor[1].se);
    for (ll i = 2; i <= n; i++) {
        for (int i = 0; i <= n + 1; i++) delt[i] = 0;
        ll sum = 0;
        // cout << i << endl;
        for (ll j = i; j; j--) {
            // cout << "j" << j << ": ";
            auto res = get_l_rng(j, i);
            for (auto [l, r] : res) {
                // cout << "(" << l << "," << r << ") ";
                mdf(r, +1, j, sum);
                mdf(l - 1, -1, j, sum);
            }
            sum += delt[j];
            if (sum == i - j + 1) {
                // cout << "ok";
                dp[i] = min(dp[i],
                            dp[j] + b * (coor[i].fi - coor[j].fi) * (coor[i].fi - coor[j].fi) + a * (h - coor[i].se));
            }
            // cout << endl;
        }
        // cout << dp[i] << " dp\n";
    }
    if (dp[n] >= INF)
        cout << "impossible";
    else
        cout << dp[n];
    return 0;
}

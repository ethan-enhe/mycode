
#include <bits/stdc++.h>

#include <cmath>
#define fi first
#define se second
using namespace std;
using db = long double;
using ll = long long;
using pi = pair<db, db>;
const ll MXN = 1e4 + 5;
const ll INF = 1e18;
ll n, h, a, b;
pi coor[MXN];
db dp[MXN];
pi operator-(const pi &x, const pi &y) { return {x.fi - y.fi, x.se - y.se}; }
pi operator+(const pi &x, const pi &y) { return {x.fi + y.fi, x.se + y.se}; }
pi operator*(const pi &x, const db &y) { return {x.fi * y, x.se * y}; }
db len(pi x) { return sqrt(x.fi * x.fi + x.se * x.se); }
bool chk(ll i, ll j) {
    db r = (coor[j].fi - coor[i].fi) / 2;
    pi center = {coor[j].fi - r, h - r};
    for (int k = i; k <= j; k++) {
        if (coor[k].se > center.se && len(center - coor[k]) > r) {
            return 0;
        }
    }
    return 1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> h >> a >> b;
    for (ll i = 1; i <= n; i++) {
        cin >> coor[i].fi >> coor[i].se;
    }
    dp[1] = a * (h - coor[1].se);
    for (ll i = 1; i <= n; i++) {
        if (i != 1) dp[i] = 2e18;
        for (ll j = i; j; j--) {
            // cout << j << endl;
            if (chk(j, i))
                dp[i] = min(dp[i],
                            dp[j] + b * (coor[i].fi - coor[j].fi) * (coor[i].fi - coor[j].fi) + a * (h - coor[i].se));
        }
    }
    if (dp[n] >= 1e18)
        cout << "impossible";
    else
        cout << (ll)round(dp[n]);
    return 0;
}

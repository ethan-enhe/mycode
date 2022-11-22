#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct p {
    ll x, y, tp;
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        ll h, n, m;
        vector<p> arr;
        cin >> h >> n;
        for (ll i = 1, x, y; i <= n; i++) {
            cin >> x >> y;
            arr.emplace_back(p{x, y, 0});
        }
        cin >> m;
        for (ll i = 1, x, y; i <= m; i++) {
            cin >> x >> y;
            arr.emplace_back(p{x, y, 1});
        }
        sort(arr.begin(), arr.end(), [](const p &x, const p &y) { return x.x > y.x; });
        // x+y=K,x-y=K;
        map<ll, ll> dp;
        for (auto &i : arr) {
            ll m1 = (i.x + i.y) % (h * 2), m2 = (i.x - i.y + h * 2) % (h * 2);
            if (i.tp == 1)
                ++dp[m1], ++dp[m2];
            else
                dp[m1] = dp[m2] = max(dp[m1], dp[m2]);
        }
        cout << dp[0] << '\n';
    }
    return 0;
}

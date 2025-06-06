#include <bits/stdc++.h>

#include <vector>
using namespace std;
using ll = long long;
const ll MXN = 1e5 + 5;
const char nl = '\n';
ll n, k;
ll c[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        ll c2 = -1;
        vector<ll> c1;
        for (ll i = 1; i <= k; i++) {
            cin >> c[i];
            if (c[i] >= 2) {
                c2 = i;
            } else if (c[i] == 1) {
                c1.push_back(i);
            }
        }
        if (c2 != -1) {
            cout << n - 1 << nl;
            for (ll i = 2; i <= n; i++) cout << 1 << " " << i << " " << c2 << nl;
            continue;
        } else {
            ll sc1 = c1.size();
            vector<tuple<ll, ll, ll>> ans;
            for (ll i = 0; i < min((ll)c1.size(), n - 1); i++) {
                ans.push_back({1, i + 2, c1[i]});
            }
            ll idx = c1.size() + 2;
            while (idx <= n) {
                ll last = 1;
                for (ll i = 1; i < k; i++) {
                    ans.push_back({idx, last, i});
                    last = idx;
                    ++idx;
                    if (idx > n) break;
                }
                ans.push_back({1, last, k});
            }
            cout << ans.size() << nl;
            for (auto [a, b, c] : ans) {
                cout << a << " " << b << " " << c << nl;
            }
        }
        // for (ll i = (ll)c1.size() + 2; i <= n; i++) {
        //     cout << 1 << " " << i << " " << 1 << nl;
        //     cout << 1 << " " << i << " " << 2 << nl;
    }
    return 0;
}

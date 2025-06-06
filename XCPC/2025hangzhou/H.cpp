#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
ll n, k;
ll sz(pi x) { return x.se - x.fi + 1; }
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        vector<ll> parent(n + 1, 0);
        vector<pi> chains(k);
        for (auto &[u, v] : chains) {
            cin >> u >> v;
            for (ll i = v; i > u; i--) parent[i] = i - 1;
        }
        sort(chains.begin(), chains.end(), [](auto x, auto y) { return sz(x) < sz(y); });
        auto maxchain = chains.back();
        ll idx = 0, cursz = 1;
        for (ll i = maxchain.se - 1; i >= maxchain.fi; i--) {
            ll nxsz = cursz + 1;
            while (sz(chains[idx]) <= cursz && idx < k - 1) {
                parent[chains[idx].fi] = i;
                nxsz += sz(chains[idx]);
                ++idx;
            }
            cursz = nxsz;
        }
        if (idx < k - 1) {
            cout << "IMPOSSIBLE\n";
        } else {
            for (ll i = 1; i <= n; i++) cout << parent[i] << " ";
            cout << '\n';
        }
    }
    return 0;
}

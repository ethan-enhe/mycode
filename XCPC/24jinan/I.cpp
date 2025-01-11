#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 3e5 + 5;
vector<ll> g[MXN];
ll n;
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    ll t;
    while (t--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) {
            g[i].clear();
        }
        for (ll i = 1; i < n; i++) {
            ll u, v;
            cin >> u >> v;
        }
    }

    return 0;
}

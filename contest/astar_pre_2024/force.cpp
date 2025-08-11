#include <bits/stdc++.h>

#include <algorithm>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 1e6;
const char nl = '\n';
const ll INF = 1e9;
ll n;
ll arr[MXN], tmp[MXN];
ll getcur() {
    ll mx = -INF, mn = INF;
    for (ll i = 1; i <= n; i++) mx = max(mx, tmp[i]), mn = min(mn, tmp[i]);
    return mx - mn;
}
mt19937_64 rnd(clock());
ll ri(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rnd); }
ll frc() {
    for (ll i = 1; i <= n; i++) {
        tmp[i] = arr[i];
    }
    shuffle(tmp + 1, tmp + 1 + n, rnd);
    ll ans = 0;
    // cerr << "---" << endl;
    for (ll i = 1; i <= n; i++) {
        ll j = ri(1, n);
        while (j == i) j = ri(1, n);
        tmp[i] += tmp[j];
        // cerr << tmp[i] - tmp[j] << "+=" << tmp[j] << endl;
        ans = max(ans, getcur());
    }
    // if (ans == 12) exit(0);
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) {
            cin >> arr[i];
            tmp[i] = arr[i];
        }
        if (n == 1) {
            cout << 0 << nl;
            continue;
        }
        ll ans = getcur();
        for (ll i = 1; i <= 100000; i++) {
            // cout << i << endl;
            ans = max(ans, frc());
        }
        cout << ans << nl;
    }
    return 0;
}

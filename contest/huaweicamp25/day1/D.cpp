#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1.5e5 + 5;
const ll LG = 31;
const ll INF = 1e12;
ll n;
vector<ll> arr;
ll solve(const vector<ll> &v, ll h) {
    if (v.empty()) return -INF;
    if (h == -1) return 0;
    vector<ll> v0, v1;
    for (auto i : v) {
        if ((i >> h) & 1)
            v1.push_back(i);
        else
            v0.push_back(i);
    }
    ll x1 = solve(v1, h - 1), x0 = solve(v0, h - 1);
    // cerr << x1 << endl;
    ll ans = 0;
    if (x1 > x0) {
        ans = max(x0 + (1ll << h), x1);
    } else
        ans = max(x0, x1 + (1ll << h));
    // for (auto i : v) cout << i << " ";
    // cout << ": " << h << ": " << ans << endl;
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        arr.push_back(x);
    }
    cout << solve(arr, LG - 1);
    return 0;
}

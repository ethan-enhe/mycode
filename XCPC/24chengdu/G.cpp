#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 2e6 + 5;
ll n, cnt;
ll arr[MXN];
void solve(ll x, ll y) {
    vector<ll> v = {x & y, x ^ (x & y), y ^ (x & y)};
    for (ll f = 0; f < 2; f++) {
        ll x = f ? v[0] : 0;
        // cout << "!!!" << endl;
        for (ll g = 0; g < 2; g++) {
            ll y = x ^ (g ? v[1] : 0);
            for (ll h = 0; h < 2; h++) {
                ll z = y ^ (h ? v[2] : 0);
                // cout << z << endl;
                arr[++cnt] = z;
            }
        }
    }
}
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n;
    cnt = n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        if (i > 1) {
            solve(arr[i], arr[i - 1]);
        }
    }
    sort(arr + 1, arr + 1 + cnt);
    cnt = unique(arr + 1, arr + 1 + cnt) - arr - 1;
    cout << cnt << endl;
    return 0;
}

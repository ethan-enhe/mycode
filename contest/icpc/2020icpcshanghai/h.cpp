#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e5 + 5;

ll n, m, arr[MXN], brr[MXN];
void umx(ll &x, ll y) { x = max(x, y); }
void umn(ll &x, ll y) { x = min(x, y); }
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (ll i = 0; i < m; i++) cin >> arr[i];
        for (ll i = 0; i < m; i++) cin >> brr[i];
        sort(arr, arr + m);
        sort(brr, brr + m);
        /* for (ll i = 0; i < m; i++) cout << arr[i] << " " << brr[i] << endl; */
        ll ans = 1e18;
        for (ll j = 0; j < m; j++) {
            ll mx = 0, mn = 0;
            for (ll k = 0; k < m; k++) {
                umx(mx, brr[(j + k) % m] + (j + k >= m) * n - arr[k]);
                umn(mn, brr[(j + k) % m] + (j + k >= m) * n - arr[k]);
            }
            cout<<mx<<" "<<mn;
            ans = min({ans, mx * 2 - mn, -mn * 2 + mx});
        }
        cout << ans << '\n';
    }
    return 0;
}

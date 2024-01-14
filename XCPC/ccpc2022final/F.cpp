#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e6 + 5;
char str[MXN];
ll arr[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) {
            ll x;
            cin >> x;
            arr[x] = i;
        }
        bool f = 0;
        for (ll i = 2; i <= n; i++) {
            if (abs(arr[i] - arr[i - 1]) >= 3) f = 1;
        }
        cout << (f ? "No" : "Yes") << '\n';
    }
    return 0;
}

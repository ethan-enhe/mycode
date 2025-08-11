#include <bits/stdc++.h>

#include <algorithm>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 1e6;
const char nl = '\n';
ll n;
ll arr[MXN];
ll gets(ll l, ll r, bool ismx, bool candouble = 1) {
    ll sum = 0;
    for (ll i = l; i <= r; i++) {
        sum += arr[i];
    }
    if (r > l && candouble) {
        if (ismx)
            sum = max(sum, sum + arr[r]);
        else
            sum = min(sum, sum + arr[l]);
    }
    return sum;
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
        }
        if (n == 1) {
            cout << 0 << nl;
            continue;
        }
        sort(arr + 1, arr + 1 + n);
        ll pc = 0, nc = 0, zc = 0;
        for (ll i = 1; i <= n; i++) {
            if (arr[i] > 0) {
                pc++;
            } else if (arr[i] == 0) {
                zc++;
            } else {
                nc++;
            }
        }
        if (pc == 0 || nc == 0) {
            if (n == 2)
                cout << max(abs(arr[2]), abs(arr[1])) << nl;
            else {
                if (arr[1] < 0) {
                    for (ll i = 1; i <= n; i++) arr[i] = -arr[i];
                    reverse(arr + 1, arr + 1 + n);
                }
                ll s = arr[n];
                for (ll i = n; i > 1; i--) s += arr[i];
                cout << (s - arr[1]) << nl;
            }
        } else {
            ll ans = 0;
            for (ll i = min(n - 1, pc + zc + 5); i >= max(1ll, pc + zc - 5); i--) {
                ans = max(ans, gets(i + 1, n, 1) - gets(1, i, 0));
                if (i > 1) ans = max(ans, gets(i, n, 1, 0) - gets(1, i, 0, 1));
                if (i > 1) ans = max(ans, gets(i, n, 1, 1) - gets(1, i, 0, 0));
            }
            cout << ans << endl;
        }
    }
    return 0;
}

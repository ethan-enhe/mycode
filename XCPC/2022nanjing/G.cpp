#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ll MXN = 1e6 + 5;
ll n;
ll arr[MXN];
ll inc[MXN];
ll decr[MXN];
ll greaterthan[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        ld ans = -1;
        ll fz = 0, fm = 0;
        cin >> n;
        bool ok = 1;
        for (ll i = 1; i <= n; i++) {
            cin >> arr[i];
            inc[i] = inc[i - 1];
            decr[i] = decr[i - 1];
            if (arr[i] == 1)
                inc[i]++;
            else if (arr[i] == -1)
                decr[i]++;
            if (i - 2 * decr[i] < 0) {
                ok = 0;
            }
        }
        greaterthan[n + 1] = 1;
        for (ll i = n; i >= 1; i--) {
            if (arr[i] == 1) {
                greaterthan[i] = max(1ll, greaterthan[i + 1] - 1);
            } else {
                greaterthan[i] = greaterthan[i + 1] + 1;
            }
        }
        if (!ok) {
            cout << "-1\n";
            continue;
        }

        for (ll i = 1; i <= n + 1; i++) {
            ll sum = i - 1 - decr[i - 1] + 1;
            ll cnt = i - 1 - 2 * decr[i - 1] + 1;
            // cout << i << " " << sum << " " << cnt << "\n";
            if (cnt >= greaterthan[i]) {
                ll cntinc = inc[n] - inc[i - 1];
                sum += cntinc;
                cnt += cntinc - (n - i + 1 - cntinc);
                if ((ld)sum / cnt > ans) {
                    ans = (ld)sum / cnt;
                    fz = sum, fm = cnt;
                }
            }
        }
        ll g = __gcd(fz, fm);
        cout << fz / g << " " << fm / g << "\n";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';
const ll MXN = 3e5 + 5;
ll n, m, c, arr[MXN], sum[MXN];
ll solve() {
    for (ll i = n; i; i--) sum[i] = sum[i + 1] + arr[i];
    ll ans = 0;
    for (ll i = 1, cur = 0; i <= n; i++) {
        if (cur + arr[i] / c >= sum[i + 1]) {
            /* cerr << i << " " << cur << nl; */
            ll _arr = arr[i];
            if (cur >= sum[i + 1]) {
                ans += cur;
                cur -= sum[i + 1];
                _arr -= cur;
                ans += min(_arr / (c + 1), sum[i + 1]);
            } else {
                _arr -= c * (sum[i + 1] - cur);
                ans += sum[i + 1] + min(_arr / (c + 1), cur);
            }
            return sum[1] - ans;
        }
        ans += min(cur, arr[i] % c);
        cur = cur - min(cur, arr[i] % c) + arr[i] / c;
    }
    return -1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> c;
    for (ll i = 1; i <= n; i++) cin >> arr[i];
    cout << solve() << nl;
    while (m--) {
        ll x, y;
        cin >> x >> y;
        arr[x] = y;
        cout << solve() << nl;
    }
    return 0;
}

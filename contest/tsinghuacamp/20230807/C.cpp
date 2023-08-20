#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const ll MXN = 1e5 + 5;
ll a, b, c, na, nb, nc;
ll n, arr[MXN];
ll sa[MXN], sb[MXN], sc[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> a >> na;
    cin >> b >> nb;
    cin >> c >> nc;
    if (a > b) {
        swap(a, b);
        swap(na, nb);
    }
    if (b > c) {
        swap(b, c);
        swap(nb, nc);
    }
    if (a > b) {
        swap(a, b);
        swap(na, nb);
    }
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    sort(arr + 1, arr + 1 + n);
    for (ll i = 1; i <= n; i++) {
        sa[i] = sa[i - 1] + abs(arr[i] - a);
        sb[i] = sb[i - 1] + abs(arr[i] - b);
        sc[i] = sc[i - 1] + abs(arr[i] - c);
    }
    double half = (double)(b + c) / 2;
    ll ans = 1e18;
    for (ll i = 0; i <= min(na, n); i++) { // i|i+1
        ll r = min(n, i + nb), l = max(i, n - nc);
        if (l > r)
            continue;
        else {
            while (l < r) {
                ll mid = (l + r + 1) >> 1;
                if (arr[mid] <= half) {
                    l = mid;
                } else
                    r = mid - 1;
            }
            ll tmp = sa[i] + sb[l] - sb[i] + sc[n] - sc[l];
            ans = min(ans, tmp);
        }
    }
    cout << ans;
    return 0;
}

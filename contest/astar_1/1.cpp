#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e6 + 5;
ll n;
ll x[MXN], y[MXN], z[MXN];
pair<ll, ll> solve(ll *arr) {
    sort(arr + 1, arr + 1 + n);
    ll mid = arr[(n + 1) / 2], s1 = 0, s2 = 0;
    for (ll i = 1; i <= n; i++) {
        s1 += abs(arr[i] - mid);
        if (i && arr[i] > 1 + arr[i - 1]) {
            ll delt = arr[i] - arr[i - 1] - 1;
            s2 += delt * min(i - 1, n - i + 1);
        }
    }
    return {s1, s2};
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) cin >> x[i] >> y[i] >> z[i];
    pair<ll, ll> a, b, c;
    a = solve(x);
    b = solve(y);
    c = solve(z);
    cout << min({a.first + b.first + c.second, a.first + b.second + c.first, a.second + b.first + c.first});

    return 0;
}

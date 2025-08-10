#include <bits/stdc++.h>

#include <cmath>
#include <cstdlib>
#include <iomanip>
using namespace std;
using ll = long long;
using ld = double;
const ll MXN = 2e5 + 5;
const ld INF = 1e18;
ll n, m;
ll arr[MXN];
pair<ld, ll> dp[MXN];

inline ld w(ll l, ll r) {
    ll i = r, j = l - 1;
    return sqrtl((arr[i] - arr[j]) * (i - j));
}
pair<ld, ll> trans(ll l, ll r, ld x) {
    auto v = dp[l];
    v.first += w(l + 1, r) + x;
    v.second++;
    return v;
}
struct Node {
    ll pos, id;
    Node(ll pos = 0, ll id = 0) : pos(pos), id(id) {}
} q[MXN];

pair<ld, ll> wqs(ld x) {
    ll ql = 1, qr = 0;
    fill(dp, dp + 1 + n, pair<ld, ll>{INF, 0});
    dp[0] = {0, 0};
    q[++qr] = {1, 0};
    for (ll i = 1; i <= n; i++) {
        while (qr > ql && q[ql + 1].pos <= i) ++ql;
        dp[i] = trans(q[ql].id, i, x);
        while (qr > ql && trans(q[qr].id, q[qr].pos, x) > trans(i, q[qr].pos, x)) qr--;
        ll l = max(i + 1, q[qr].pos), r = n, ans = n + 1;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (trans(q[qr].id, mid, x) > trans(i, mid, x)) {
                ans = mid;
                r = mid - 1;
            } else
                l = mid + 1;
        }
        if (ans <= n) q[++qr] = Node(ans, i);
    }
    return dp[n];
}
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    // srand(time(0));
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        // arr[i] = rand() % 100000;
    }
    sort(arr + 1, arr + 1 + n);
    for (ll i = 1; i <= n; i++) arr[i] += arr[i - 1];

    ld l = 0, r = 1e9;
    for (ll i = 1; i <= 80; i++) {
        ld mid = (l + r) / 2;
        auto res = wqs(mid);
        if (res.second <= m)
            r = mid;
        else
            l = mid;
    }
    cout << fixed << setprecision(18) << wqs(l).first - l * m << endl;
    return 0;
}

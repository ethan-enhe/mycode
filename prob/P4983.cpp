#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
using ll = long long;
using ull = unsigned long long;
using pi = pair<ll, ll>;
const ll MXN = 1e5 + 5;
ll n, m, cost, arr[MXN], dp[MXN], cnt[MXN];
inline ll w(ll l, ll r) { return (arr[r] - arr[l] + 1) * (arr[r] - arr[l] + 1) + cost + dp[l]; }
ll ql, qr;
pi q[MXN];
void cal() {
    q[ql = qr = 1] = {0, 1};
    for (ll i = 1; i <= n; i++) {
        while (ql < qr && q[ql + 1].se <= i) ++ql;
        /* cout << i << " " << q[ql].fi << endl; */
        dp[i] = w(q[ql].fi, i);
        cnt[i] = cnt[q[ql].fi] + 1;

        while (ql <= qr && w(i, q[qr].se) < w(q[qr].fi, q[qr].se)) --qr;
        if (ql <= qr) {
            ll l = q[qr].fi, r = n + 1, mid;
            while (l < r) {
                mid = (l + r) >> 1;
                if (w(i, mid) < w(q[qr].fi, mid))
                    r = mid;
                else
                    l = mid + 1;
            }
            if (l != n + 1) q[++qr] = {i, l};
        } else
            q[++qr] = {i, i};
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] += arr[i - 1];
    }
    /* cost = 100; */
    /* cal(); */
    /* cout << dp[n] << " " << cnt[n] << endl; */
    ll l = 0, r = 1e18;
    while (l < r) {
        cost = (l + r) >> 1;
        cal();
        if (cnt[n] <= m)
            r = cost;
        else
            l = cost + 1;
    }
    cost = l;
    cal();
    cout << dp[n] - m * cost;
    return 0;
}

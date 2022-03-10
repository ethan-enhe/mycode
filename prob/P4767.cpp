#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
using ll = long long;
using ull = unsigned long long;
using pi = pair<ll, ll>;
const ll MXN = 3005;
ll n, m, cost, arr[MXN], pre[MXN], dp[MXN], cnt[MXN];
inline ll w(ll l, ll r) {
    ll mid = (l + 1 + r) >> 1;
    return dp[l] + pre[r] + pre[l] - (pre[mid] << 1) + arr[mid] * ((mid << 1) - l - r) + cost;
}
ll ql, qr;
pi q[MXN];
void cal() {
    q[ql = qr = 1] = {0, 1};
    for (ll i = 1; i <= n; i++) {
        while (ql < qr && q[ql + 1].se <= i) ++ql;
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
        pre[i] = pre[i - 1] + arr[i];
    }
    ll l = 0, r = 1e4;
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

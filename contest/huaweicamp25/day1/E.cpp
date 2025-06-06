#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 2e5 + 5;
const ll INF = 1e18;
ll n, loc[MXN];
ll a[MXN], b[MXN], c[MXN];
ll sort_pre[MXN], sort_med[MXN], sort_suf[MXN];
ll mn[MXN];
void upd(ll x, ll y) {
    ++x;
    for (; x <= n + 1; x += x & (-x)) {
        mn[x] = min(mn[x], y);
    }
}
ll pre(ll x) {
    ++x;
    ll ans = INF;
    for (; x; x -= x & (-x)) {
        ans = min(ans, mn[x]);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        ll p;
        cin >> p;
        loc[p] = i;
    }
    ll default_cost = 0;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        b[i] = min(b[i], a[i]);
        c[i] = min(c[i], a[i]);
        sort_pre[i] = sort_pre[i - 1] + (b[i] - a[i]);
        default_cost += a[i];
    }
    for (ll i = n; i; i--) {
        sort_suf[i] = sort_suf[i + 1] + (c[i] - a[i]);
    }
    memset(mn, 0x3f, sizeof(mn));
    ll ans = min(sort_pre[n], sort_suf[1]);
    upd(0, sort_pre[0]);
    for (ll i = 1; i <= n; i++) {
        ll val = pre(loc[i]) - a[i];
        upd(loc[i], val);
        upd(0, sort_pre[i]);
        ans = min({ans, val + sort_suf[i + 1], sort_pre[i] + sort_suf[i + 1]});
    }
    cout << ans + default_cost;
    return 0;
}

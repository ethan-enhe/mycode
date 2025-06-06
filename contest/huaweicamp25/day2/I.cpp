#include <bits/stdc++.h>

#include <vector>

using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 1e5 + 5;
ll n, q, arr[MXN], ans[MXN];
ll last[MXN];
vector<pi> qry[MXN];

ll mx[MXN];
void upd(ll x, ll y) {
    for (; x; x -= x & (-x)) mx[x] = max(mx[x], y);
}
ll suf(ll x) {
    ll r = 0;
    for (; x <= n; x += x & (-x)) r = max(r, mx[x]);
    return r;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    cin >> q;
    for (ll i = 1; i <= q; i++) {
        ll l, r;
        cin >> l >> r;
        qry[r].push_back({l, i});
    }
    for (ll i = 1; i <= n; i++) {
        auto solve = [&](ll d) {
            upd(last[d], d);
            last[d] = i;
        };
        for (ll j = 1; j * j <= arr[i]; j++)
            if (arr[i] % j == 0) {
                solve(j);
                if (j * j != arr[i]) solve(arr[i] / j);
            }
        for (auto [l, j] : qry[i]) {
            ans[j] = suf(l);
        }
    }
    for (ll i = 1; i <= q; i++) cout << ans[i] << "\n";
    return 0;
}

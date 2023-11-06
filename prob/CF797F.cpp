#include <bits/stdc++.h>

#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 5005, INF = 1e18;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, m, ql, qr, sum;
    cin >> n >> m;
    vector<ll> mice(n + 1), cur(n + 1), last(n + 1);
    vector<pi> q(n + 2), hole(m + 1);
    for (ll i = 1; i <= n; i++) cin >> mice[i];
    for (ll i = 1; i <= m; i++) cin >> hole[i].fi >> hole[i].se;
    sort(mice.begin() + 1, mice.end());
    sort(hole.begin() + 1, hole.end());
    fill(last.begin() + 1, last.end(), INF);
    for (ll i = 1; i <= m; i++) {
        q[ql = qr = 1] = {sum = 0, 0};
        for (ll j = 1; j <= n; j++) {
            sum += abs(mice[j] - hole[i].fi);
            last[j] -= sum;
            while (ql <= qr && last[j] <= q[qr].fi) --qr;
            q[++qr] = {last[j], j};
            while (q[ql].se + hole[i].se < j) ++ql;
            cur[j] = q[ql].fi + sum;
        }
        swap(cur, last);
    }
    cout << (last[n] >= INF ? -1 : last[n]);
    return 0;
}

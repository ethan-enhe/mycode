#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 2e6 + 5;
ll t, n, m, q;
ll curstage, curscor;
ll ans[MXN], p[MXN];
set<ll> record;
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> t;
    while (t--) {
        cin >> n >> m >> q;
        for (ll i = 1; i <= m; i++) ans[i] = 0;
        curstage = -1;
        while (q--) {
            ll tp, id, x;
            cin >> tp >> id;
            if (tp == 1) {
                record.clear();
                curstage = id;
                curscor = m;
            } else {
                cin >> x;
                if (x != curstage) continue;
                if (record.count(id)) continue;
                record.insert(id);
                if (tp == 2) ans[id] += curscor--;
            }
        }
        for (ll i = 1; i <= m; i++) p[i] = i;
        sort(p + 1, p + 1 + m, [](ll x, ll y) {
            if (ans[x] == ans[y]) return x < y;
            return ans[x] > ans[y];
        });
        for (ll i = 1; i <= m; i++) {
            cout << p[i] << " " << ans[p[i]] << '\n';
        }
    }
    return 0;
}

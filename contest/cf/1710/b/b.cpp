#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
using ll = long long;
void umx(ll &x, const ll &y) { x = max(x, y); }
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

ll n, m;
map<ll, ll> delt;
ll x[MXN], p[MXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        delt.clear();
        cin >> n >> m;
        for (ll i = 1; i <= n; i++) {
            cin >> x[i] >> p[i];
            delt[x[i] - p[i] + 1]++;
            delt[x[i] + 1] -= 2;
            delt[x[i] + p[i] + 1]++;
            if (!delt.count(x[i])) delt[x[i]] = 0;
        }
        ll b = 0, k = 0, lastx = -INF;
        ll b_1 = -INF, b1 = -INF;
        for (auto it : delt) {
            b += k * (it.fi - lastx);
            k += it.se;

            if (b > m) {
                umx(b1, b - it.fi + 1);
                umx(b_1, b + it.fi - 1);
            }

            lastx = it.fi;
        }
        for (ll i = 1; i <= n; i++) cout << ((p[i] + m - x[i] >= b1) && (p[i] + m + x[i] >= b_1));
        cout << nl;
    }
    return 0;
}

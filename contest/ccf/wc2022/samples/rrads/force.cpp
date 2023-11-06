
#include <bits/stdc++.h>

#include <cstdio>
using namespace std;
typedef long long ll;
const ll MXN = 5e5 + 5;
ll n, m, B, arr[MXN], ans[MXN];
ll tmp[MXN], p[MXN];

int main() {
    freopen("rrads1.in", "r", stdin);
    /* freopen("rrads2.out", "w", stdout); */
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++) scanf("%lld", arr + i);
    for (ll i = 1; i <= m; i++) {
        ll l, r;
        scanf("%lld%lld", &l, &r);
        for (int i = 1; i <= n; i++) {
            tmp[i] = arr[i];
            p[i] = 0;
        }
        sort(tmp + l, tmp + r + 1);
        for (int i = l; i <= r; i++) p[tmp[i]] = i;
        ll ans = 0;
        for (int i = l + 1; i <= r; i++) {
            ans += abs(p[tmp[i]] - p[tmp[i - 1]]);
        }
        cout << ans << endl;
    }
    return 0;
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e6 + 5;
char str[MXN];
ll arr[MXN];
ll s, t, k, n;
ll extendk, lg;
ll solve(ll s, ll t) {
    if (s > t) swap(s, t);
    if (s == t) return 0;
    if (t - s == 1) return 1;
    if ((s ^ t) <= k) return 1;
    if ((s ^ t) <= extendk) return 2;

    ll delta = (t >> lg) - (s >> lg);
    return solve(s, s | extendk) + (delta - 1) * (1 + solve(0, extendk)) + 1 + solve(0, t & extendk);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    while (n--) {
        cin >> s >> t >> k;
        lg = 64 - __builtin_clzl(k);
        extendk = (1ll << lg) - 1;
        // cout << extendk;
        cout << solve(s, t) << '\n';
    }
    return 0;
}

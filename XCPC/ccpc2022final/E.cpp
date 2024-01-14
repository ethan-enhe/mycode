#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e6 + 5;
char str[MXN];
ll lastp[MXN], nxp[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, t;
    cin >> t;
    while (t--) {
        cin >> (str + 1);
        n = strlen(str + 1);
        lastp[0] = 0;
        for (ll i = 1; i <= n; i++) lastp[i] = str[i] == 'p' ? i : lastp[i - 1];
        nxp[n + 1] = n + 1;
        for (ll i = n; i; i--) nxp[i] = str[i] == 'p' ? i : nxp[i + 1];
        ll ans = 0;
        for (ll i = 1; i <= n; i++) {
            if (str[i] != 'c') {
                ll tmp = min((i - 1 - lastp[i - 1]) / 2, (nxp[i + 1] - i - 1));
                ans += tmp;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}

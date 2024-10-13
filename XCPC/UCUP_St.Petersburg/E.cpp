#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ll MXN = 1e6 + 5;
// const ll MXN = 1000000;
ll t, n, k;
ld lnfac[MXN], lnfacc;

ld lnfact(ll x) {
    if (x < MXN) return lnfac[x];
    return x * log(x) - x + log(x) / 2 + lnfacc;
}
ld lnchoose(ll n, ll k) { return lnfact(n) - lnfact(k) - lnfact(n - k); }
ld lnchoose_lessthan(ll n, ll k) { return lnchoose(n, k) + log(2) * k - 5; }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 1; i < MXN; ++i) lnfac[i] = lnfac[i - 1] + log(i);
    lnfacc = lnfac[MXN - 1] - ((MXN - 1) * (log(MXN - 1) - 1) + log(MXN - 1) / 2);

    cin >> t;
    while (t--) {
        cin >> n >> k;
        ld ans = log(3) * n + log(3 * k + 1);
        ans -= lnchoose_lessthan(n, k);
        cout << fixed << setprecision(9) << ans << '\n';
    }

    return 0;
}

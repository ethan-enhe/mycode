#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const char nl = '\n';
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN];
char s[MXN], t[MXN];
ll fail[MXN];
ll next(ll i, char j) {
    if (t[i + 1] == j) return i + 1;
    if (i == 0) return 0;
    return next(fail[i], j);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> (s + 1);
    cin >> (t + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);
    for (ll i = 2; i <= m; i++) {
        fail[i] = next(fail[i - 1], t[i]);
    }
    ll idx = 0;
    for (ll i = 1; i <= n; i++) {
        idx = next(idx, s[i]);
        if (idx == m) cout << i - m + 1 << '\n';
    }
    for (ll i = 1; i <= m; i++) {
        cout << fail[i] << " ";
    }
    return 0;
}

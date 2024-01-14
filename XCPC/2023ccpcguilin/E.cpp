#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const char nl = '\n';
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        ll cnt = 0;
        for (auto &i : s) {
            if (i == '(')
                ++cnt;
            else
                cnt = max(cnt - 1, 0ll);
        }
        if (cnt > 0)
            cout << "impossible" << nl;
        else
            cout << s << nl;
    }
    return 0;
}


#include <bits/stdc++.h>

#include <algorithm>
#include <vector>

using namespace std;
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using pi = pair<ll, ll>;
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;
const ll LG = 60;

ll n, m, arr[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    vector<ll> ans;
    ll cnt = 0;
    for (ll i = 0; i <= LG; i++) {
        if ((n >> i) & 1) {
            ans.push_back(n - i - 1 - (cnt++));
        }
    }
    cout << ans.size() << endl;
    for (auto i = ans.rbegin(); i != ans.rend(); ++i) cout << *i << " ";

    // ll v = 0;
    // for (ll i = 1; i <= n; i++) {
    //     if (find(all(ans), i) != ans.end()) {
    //         v--;
    //     } else
    //         v = (v + i - 2) * 2;
    // }
    // cout << v << nl;
    return 0;
}

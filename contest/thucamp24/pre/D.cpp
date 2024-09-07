#include <bits/stdc++.h>

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

ll n, m, arr[MXN], tot;
ll ans = INF, ansi = 0;

vector<ll> g[MXN];
void dfs(ll p, ll fa) {
    ll mx = 0;
    for (ll nx : g[p]) {
        if (nx == fa) continue;
        dfs(nx, p);
        arr[p] += arr[nx];
        mx = max(mx, arr[nx]);
    }
    if (fa != 0) {
        mx = max(mx, tot - arr[p]);
    }
    if (mx < ans) {
        ans = mx;
        ansi = p;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        tot += arr[i];
    }
    for (ll i = 0; i < n - 1; i++) {
        ll x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1,0);
    cout << ansi << nl;
    return 0;
}

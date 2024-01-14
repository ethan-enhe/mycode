#include <bits/stdc++.h>

using namespace std;
#define all(x) (x).begin(), (x).end()
#define tpl template <typename T>

using ll = long long;
tpl void umx(T &x, const T &y) { x = max(x, y); }
tpl void umn(T &x, const T &y) { x = min(x, y); }
const ll MXN = 1e6 + 5;

ll n, m, cnt[MXN];
ll dpth[MXN];
ll dpthout[MXN];
vector<ll> g[MXN];
void dfs(ll p, ll fa) {
    dpth[p] = 0;
    for (auto &nx : g[p])
        if (nx != fa) {
            dfs(nx, p);
            cnt[p] += cnt[nx];
            umx(dpth[p], dpth[nx] + 1);
        }
}

ll sum = 1;

ll solve(vector<ll> d) {
    sort(all(d));
    ll res = d[d.size() - 1] - 1;
    if (d.size() > 1) {
        umn(res, d[d.size() - 2] + 1);
    } else
        umn(res, 1ll);
    return res;
}
char str[MXN];
void dfs2(ll p, ll fa) {
    ll mx = 0;
    ll mn = 1e18;
    if (str[p-1] == '1') mn = 0;
    if (cnt[p] != cnt[1]) umn(mn, dpthout[p]);
    vector<ll> d = {dpthout[p]};
    for (auto &nx : g[p])
        if (nx != fa) {
            d.push_back(dpth[nx] + 1);
            dpthout[nx] = max(dpthout[p], mx) + 1;
            umx(mx, dpth[nx] + 1);
            if (cnt[nx]) umn(mn, dpth[nx] + 1);
        }
    sum += max(0ll,solve(d) + 1 - mn);
    mx = 0;
    for (ll i = g[p].size() - 1; i >= 0; i--) {
        ll nx = g[p][i];
        if (nx != fa) {
            umx(dpthout[nx], mx + 1);
            umx(mx, dpth[nx] + 1);
        }
    }
    for (auto &nx : g[p])
        if (nx != fa) dfs2(nx, p);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i < n; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> str;
    for (ll i = 1; i <= n; i++)
        if (str[i-1] == '1') cnt[i] = 1;
    dfs(1, 0);
    dfs2(1, 0);
    cout << sum;
    return 0;
}

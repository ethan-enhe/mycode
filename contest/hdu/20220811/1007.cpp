#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;
#define fi first
#define se second
using ll = long long;
using pi = pair<int, int>;
const char nl = '\n';
const ll MXN = 50005;

ll n, m, p[MXN], ip[MXN];
ll w(ll x, ll y) { return abs(x - y) * abs(p[x] - p[y]); }
vector<pi> e[MXN];
ll fa[MXN];
ll find(ll x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main() {
    /* freopen("test.in", "r", stdin); */
    /* freopen("test.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        m = ceil(sqrt(n));
        for (ll i = 1; i <= n; i++) {
            cin >> p[i];
            ip[p[i]] = i;
            e[i].clear();
            fa[i] = i;
        }
        /* ll cnt=0; */
        for (ll i = 1; i <= n; i++)
            for (ll j = i + 1; j <= n && j <= i + m; j++) {
                ll tw = w(i, j);
                if (tw <= n) e[tw].emplace_back(i, j);
                tw = w(ip[i], ip[j]);
                /* ++cnt; */
                if (abs(ip[i] - ip[j]) > m && tw <= n) e[tw].emplace_back(ip[i], ip[j]);
            }
        /* cout<<cnt<<nl; */
        ll ans = 0;
        for (ll i = 1; i <= n; i++)
            for (auto j : e[i])
                if (fa[j.fi] != fa[j.se]) {
                    ll u = find(j.fi), v = find(j.se);
                    if (u != v) {
                        fa[u] = v;
                        ans += i;
                    }
                }
        cout << ans << nl;
    }
    return 0;
}

#include <bits/stdc++.h>

#include <vector>

using namespace std;
using ll = long long;
const ll P = 998244353;
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e5 + 5;

ll n, m, fa[MXN], sz[MXN];
ll dpth[MXN];
ll fac[MXN], ifac[MXN];
vector<ll> dp[MXN];
vector<ll> g[MXN];
ll c(ll x, ll y) {
    if (y > x || y < 0) return 0;
    return fac[x] * ifac[y] % P * ifac[x - y] % P;
}
void dfs(ll p) {
    vector<ll> tmp(dpth[p] + 2);
    tmp[0] = 1;
    ll tot = 0;
    for (ll nx : g[p]) {
        dfs(nx);
        tot += sz[nx];
        for (ll i = dpth[p] + 1; ~i; i--) {
            ll nxti = 0;
            for (ll j = 0; j <= dpth[nx] && j <= i; j++) {
                nxti = (nxti + dp[nx][j] * c(tot + i, sz[nx] + j) % P * tmp[i - j]) % P;
            }
            tmp[i] = nxti;
        }
    }
    // if (p == 1) cerr << tmp[0] << endl;
    for (ll i = dpth[p]; ~i; i--) {
        for (ll j = 0; j <= i + 1; j++) {
            dp[p][i] = (dp[p][i] + tmp[i - j + 1] * c(sz[p] + i, j)) % P;
        }
    }
    // cerr << p << " :";
    // for (ll i = 0; i <= dpth[p]; i++) cerr << dp[p][i] << " ";
    // cerr << endl;
}
ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = ifac[0] = 1;
    for (ll i = 1; i < MXN; i++) {
        fac[i] = fac[i - 1] * i % P;
        ifac[i] = qpow(fac[i], P - 2);
    }
    cin >> n;
    dp[1].resize(1);
    for (ll i = 2; i <= n; i++) {
        cin >> fa[i];
        g[fa[i]].push_back(i);
        dpth[i] = dpth[fa[i]] + 1;
        dp[i].resize(dpth[i] + 1);
    }
    for (ll i = n; i; i--) {
        ++sz[i];
        sz[fa[i]] += sz[i];
    }
    dfs(1);
    cout << dp[1][0];
    return 0;
}

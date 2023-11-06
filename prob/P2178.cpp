#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN = 3e5+5;
char str[MXN];
ll arr[MXN];
ll rk[MXN], sa[MXN], h[MXN], tmp[MXN], cnt[MXN], ork[MXN << 1];
ll n;
bool cmp(ll x, ll y, ll w) { return ork[x] == ork[y] && ork[x + w] == ork[y + w]; }
void ss() {
    ll m = 130;
    for (ll i = 1; i <= n; i++) cnt[rk[i] = str[i]]++;
    for (ll i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (ll i = n; i; i--) sa[cnt[rk[i]]--] = i;
    for (ll w = 1; w <= n; w <<= 1) {
        ll ind = 0;
        for (ll i = n - w + 1; i <= n; i++) tmp[++ind] = i;
        for (ll i = 1; i <= n; i++)
            if (sa[i] > w) tmp[++ind] = sa[i] - w;

        for (ll i = 1; i <= m; i++) cnt[i] = 0;
        for (ll i = 1; i <= n; i++) cnt[rk[i]]++;
        for (ll i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (ll i = n; i; i--) sa[cnt[rk[tmp[i]]]--] = tmp[i], ork[i] = rk[i];
        m = 0;
        for (ll i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? m : ++m;

        if (m == n) break;
    }
    for (ll i = 1, l = 0; i <= n; i++) {
        l -= !!l;
        while (str[i + l] == str[sa[rk[i] - 1] + l]) ++l;
        h[rk[i]] = l;
    }
}
vector<ll> r_siml[MXN];
ll ansc, ansm = -1e18;
ll ans[MXN][2];
ll fa[MXN], mn[MXN], mx[MXN], sz[MXN];
ll find(ll x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(ll x, ll y) {
    x = find(x), y = find(y);
    ansc += sz[x] * sz[y];
    ansm = max(ansm, max(mx[x] * mx[y], mn[x] * mn[y]));
    fa[y] = x;
    sz[x] += sz[y];
    mn[x] = min(mn[x], mn[y]);
    mx[x] = max(mx[x], mx[y]);
}
int main(int argc, char *argv[]) {
    scanf("%lld %s", &n, str + 1);
    for (ll i = 1; i <= n; i++) scanf("%lld", arr + i);
    ss();
    for (ll i = 1; i <= n; i++) {
        fa[i] = i, sz[i] = 1, mx[i] = mn[i] = arr[sa[i]];
        if (i > 1) r_siml[h[i]].push_back(i);
    }
    for (ll i = n - 1; ~i; i--) {
        for (ll j : r_siml[i]) merge(j, j - 1);
        if (ansc) ans[i][0] = ansc, ans[i][1] = ansm;
    }
    for (ll i = 0; i < n; i++) printf("%lld %lld\n", ans[i][0], ans[i][1]);

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN = 1e6 + 5, MNN = 1005;
ll n, m, cur, B, LG, arr[MXN], plc[MXN], ans[MXN];
struct que {
    ll l, r, id;
} ask[MXN];
bool cmp(que &x, que &y) {
    if (n <= MNN) return x.l == y.l ? x.r < y.r : x.l < y.l;

    ll idx = x.l / B, idy = y.l / B;
    if (idx == idy)
        return idx & 1 ? x.r < y.r : x.r > y.r;
    else
        return idx < idy;
}
ll cnt[MXN], totc;
void mod(ll x, ll y) {
    totc += y;
    for (; x <= n; x += x & (-x)) cnt[x] += y;
}
ll qrk(ll x) {
    ll r = 0;
    for (; x; x ^= x & (-x)) r += cnt[x];
    return r;
}
ll qva(ll x) {
    if (!x || x > totc) return 0;
    ll r = 0;
    for (ll i = 1 << LG; i; i >>= 1)
        if (x > cnt[r + i]) x -= cnt[r += i];
    return r + 1;
}

void add(ll x) {
    mod(arr[x], 1);
    ll rk = qrk(arr[x]), pre = qva(rk - 1), suf = qva(rk + 1);
    if (pre) cur += abs(plc[pre] - x);
    if (suf) cur += abs(plc[suf] - x);
    if (suf && pre) cur -= abs(plc[pre] - plc[suf]);
}
void del(ll x) {
    ll rk = qrk(arr[x]), pre = qva(rk - 1), suf = qva(rk + 1);
    if (pre) cur -= abs(plc[pre] - x);
    if (suf) cur -= abs(plc[suf] - x);
    if (suf && pre) cur += abs(plc[pre] - plc[suf]);
    mod(arr[x], -1);
}

int main() {
    freopen("rrads.in", "r", stdin);
    freopen("rrads.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for (ll i = n + 1; i < MXN; i++) cnt[i] = 1e9;
    B = max(2ll, (ll)sqrt(n));
    LG = log2(n);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", arr + i);
        plc[arr[i]] = i;
    }
    for (ll i = 1; i <= m; i++) {
        scanf("%lld%lld", &ask[i].l, &ask[i].r);
        ask[i].id = i;
    }
    sort(ask + 1, ask + 1 + m, cmp);
    ll l = 1, r = 0;
    for (ll i = 1; i <= m; i++) {
        while (r < ask[i].r) add(++r);
        while (l > ask[i].l) add(--l);
        while (r > ask[i].r) del(r--);
        while (l < ask[i].l) del(l++);
        ans[ask[i].id] = cur;
    }
    for (ll i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    return 0;
}

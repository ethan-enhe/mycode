#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';
const ll MXN = 3e5 + 5;
ll n, m, c, tot, sum[MXN];

struct node {
    // /c之和，%c之和，如果在当前区间上模拟，会用掉多少代金券
    ll div, mod, use;
} t[MXN << 2];
node operator+(const node &x, const node &y) {
    return {x.div + y.div, x.mod + y.mod, x.use + y.use + min(y.mod - y.use, x.div - x.use)};
}
#define ls p << 1
#define rs p << 1 | 1
void mdf(ll mi, ll mv, ll p = 1, ll l = 1, ll r = n) {
    if (l == r) {
        tot = tot - (t[p].div * c + t[p].mod) + mv;
        t[p] = {mv / c, mv % c, 0};
        return;
    }
    ll mid = (l + r) >> 1;
    if (mi <= mid)
        mdf(mi, mv, ls, l, mid);
    else
        mdf(mi, mv, rs, mid + 1, r);
    t[p] = t[ls] + t[rs];
}
ll que(ll p = 1, ll l = 1, ll r = n, node lft = {0, 0, 0}, ll rht = 0) {
    if (l == r) {
        ll arr = t[p].div * c + t[p].mod, cur = lft.div - lft.use, ans = lft.use;
        if (cur >= rht) {
            ans += cur, cur -= rht, arr -= cur;
            ans += min(arr / (c + 1), rht);
        } else {
            arr -= c * (rht - cur);
            ans += rht + min(arr / (c + 1), cur);
        }
        return tot - ans;
    }
    ll mid = (l + r) >> 1;
    node _lft = lft + t[ls];
    ll _rht = rht + t[rs].div * c + t[rs].mod;
    if (_lft.div - _lft.use >= _rht)
        return que(ls, l, mid, lft, _rht);
    else
        return que(rs, mid + 1, r, _lft, rht);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> c;
    for (ll i = 1, x; i <= n; i++) {
        cin >> x;
        mdf(i, x);
    }
    cout << que() << nl;
    while (m--) {
        ll x, y;
        cin >> x >> y;
        mdf(x, y);
        cout << que() << nl;
    }
    return 0;
}

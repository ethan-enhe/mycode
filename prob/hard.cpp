#include <bits/stdc++.h>

#include <vector>
#define il inline
using namespace std;
typedef long long ll;

template <class v_type, class t_type, v_type (*merge)(v_type, v_type), void (*addt)(ll, ll, v_type &, t_type &, t_type),
          const v_type DEFAULT_V, const t_type DEFAULT_T, const ll SZ>
struct segt {
#define ls d[p].son[0]
#define rs d[p].son[1]
    struct node {
        v_type v;
        t_type t;
        ll son[2];
        node() {
            son[0] = son[1] = 0;
            v = DEFAULT_V, t = DEFAULT_T;
        }
    } d[SZ];
    ll nodec;
    segt() { nodec = 0; }
    il void pushd(ll p, ll l, ll r) {
        if (!ls) ls = ++nodec;
        if (!rs) rs = ++nodec;
        ll mid = (l + r) >> 1;
        addt(l, mid, d[ls].v, d[ls].t, d[p].t);
        addt(mid + 1, r, d[rs].v, d[rs].t, d[p].t);
        d[p].t = DEFAULT_T;
    }
    il void mod(ll &p, ll l, ll r, ll ml, ll mr, t_type mv) {
        if (!p) p = ++nodec;
        if (ml <= l && r <= mr) {
            addt(l, r, d[p].v, d[p].t, mv);
            return;
        }
        ll mid = (l + r) >> 1;
        pushd(p, l, r);
        if (ml <= mid) mod(ls, l, mid, ml, mr, mv);
        if (mr > mid) mod(rs, mid + 1, r, ml, mr, mv);
        d[p].v = merge(d[ls].v, d[rs].v);
    }
    il v_type que(ll p, ll l, ll r, ll ql, ll qr) {
        if (!p || (ql <= l && r <= qr)) return d[p].v;
        ll mid = (l + r) >> 1;
        v_type res = DEFAULT_V;
        pushd(p, l, r);
        if (ql <= mid) res = merge(res, que(ls, l, mid, ql, qr));
        if (qr > mid) res = merge(res, que(rs, mid + 1, r, ql, qr));
        return res;
    }
};
il ll mrg(ll x, ll y) { return max(x, y); }
il void addt(ll l, ll r, ll &x, ll &y, ll z) {
    x += z;
    y += z;
}
const ll MXN = 3e5 + 5;
segt<ll, ll, mrg, addt, 0, 0, MXN> t;
ll n, m, rt, w;
vector<ll> incr[MXN], decr[MXN];
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    freopen("hard.in", "r", stdin);
    freopen("hard.out", "w", stdout);
    cin >> n >> m >> w;
    for (int i = 1; i <= m; i++) {
        ll l, r, v;
        cin >> l >> r >> v;
        if (v != -1) {
            t.mod(rt, 1, n, l, r, v);
        } else {
            incr[l].push_back(r);
            decr[r].push_back(l);
        }
    }
    for (ll i = 1; i <= n; i++) {
        for (auto x : incr[i]) {
            t.mod(rt, 1, n, i, x, w);
        }
        cout << (t.que(rt, 1, n, i, i) == t.d[rt].v);
        for (auto x : decr[i]) {
            t.mod(rt, 1, n, x, i, -w);
        }
    }
    return 0;
}

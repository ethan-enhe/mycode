#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
#define fi first
#define se second
constexpr ll INF = 2e9, MXN = 4e5 + 5;
ll n, m;
priority_queue<pi> q;
ll arr[MXN], cnt[MXN];
void upd(ll x) {
    if (x == 0 || x == n + 1) return;
    if (++cnt[x] == 2) q.push({-arr[x], -x});
}
struct seg {
    struct node {
        pi mn;
        ll tag;
    } t[MXN];
#define ls p << 1
#define rs p << 1 | 1
    bool type;
    seg(bool _type) : type(_type) {}
    void addt(ll p, ll k) { t[p].mn.fi += k, t[p].tag += k; }
    void pushd(ll p) {
        addt(ls, t[p].tag);
        addt(rs, t[p].tag);
        t[p].tag = 0;
    }
    void pushu(ll p) { t[p].mn = min(t[ls].mn, t[rs].mn); }
    void build(ll p, ll l, ll r, ll *arr) {
        if (l == r) {
            t[p].mn.se = l;
            if (arr) t[p].mn.fi = arr[l];
            return;
        }
        ll mid = (l + r) >> 1;
        build(ls, l, mid, arr);
        build(rs, mid + 1, r, arr);
        pushu(p);
    }
    void mod(ll p, ll l, ll r, ll ml, ll mr, ll mv) {
        if (ml > r || mr < l) return;
        if (ml <= l && r <= mr && (type || t[p].mn.fi + mv > 0)) {
            addt(p, mv);
            return;
        }
        if (l == r) {
            t[p].mn.fi = INF;
            upd(l);
            return;
        }
        ll mid = (l + r) >> 1;
        pushd(p);
        mod(ls, l, mid, ml, mr, mv);
        mod(rs, mid + 1, r, ml, mr, mv);
        pushu(p);
    }
    pi fl(ll p, ll l, ll r, ll qv) {
        if (l == r) return t[p].mn;
        ll mid = (l + r) >> 1;
        pushd(p);
        if (t[ls].mn.fi <= qv) return fl(ls, l, mid, qv);
        return fl(rs, mid + 1, r, qv);
    }
    pi que(ll p, ll l, ll r, ll ql, ll qr) {
        if (ql > r || qr < l) return {INF, INF};
        if (ql <= l && r <= qr) return t[p].mn;
        ll mid = (l + r) >> 1;
        pushd(p);
        return min(que(ls, l, mid, ql, qr), que(rs, mid + 1, r, ql, qr));
    }
} a_mn(0), mx_a(0), mnp(1), mxp(1);
#define op(func, args...) func(1, 0, n + 1, args)

bool imn[MXN], imx[MXN];
ll _mnp[MXN], _mxp[MXN], _a_mn[MXN], _mx_a[MXN];
void init() {
    ll mx = -2 * INF, mn = 2 * INF;
    imn[0] = imn[n + 1] = imx[0] = imx[n + 1] = 1;
    mnp.op(build, NULL);
    mxp.op(build, NULL);
    for (ll i = 0; i <= n + 1; i++) {
        if (i == n + 1) mx = INF, mn = -INF;
        if (!i) arr[i] = INF;
        if (arr[i] < mn) mn = arr[i], imn[i] = 1;
        _mnp[i] = arr[i];

        if (!i) arr[i] = -INF;
        if (arr[i] > mx) mx = arr[i], imx[i] = 1;
        _mxp[i] = -arr[i];
        _a_mn[i] = arr[i] - mn - m;
        _mx_a[i] = mx - arr[i] - m;
        if (_a_mn[i] <= 0) _a_mn[i] = INF, upd(i);
        if (_mx_a[i] <= 0) _mx_a[i] = INF, upd(i);
    }
    mnp.op(build, _mnp);
    mxp.op(build, _mxp);
    a_mn.op(build, _a_mn);
    mx_a.op(build, _mx_a);
}
void del(ll x) {
    mnp.op(mod, x, x, INF);
    mxp.op(mod, x, x, INF);
    if (imn[x]) {
        imn[x] = 0;

        auto cur_ele = mnp.op(que, 0, x);
        while (1) {
            auto nx_ele = mnp.op(fl, cur_ele.fi - 1);
            bool f = imn[nx_ele.se];
            a_mn.op(mod, max(x, cur_ele.se), nx_ele.se - 1, -cur_ele.fi + arr[x]);
            if (f) break;
            imn[nx_ele.se] = 1;
            cur_ele = nx_ele;
        }
    }
    if (imx[x]) {
        imx[x] = 0;

        auto cur_ele = mxp.op(que, 0, x);
        while (1) {
            auto nx_ele = mxp.op(fl, cur_ele.fi - 1);
            bool f = imx[nx_ele.se];
            mx_a.op(mod, max(x, cur_ele.se), nx_ele.se - 1, -cur_ele.fi - arr[x]);
            if (f) break;
            imx[nx_ele.se] = 1;
            cur_ele = nx_ele;
        }
    }
}
int main() {
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++) scanf("%lld", arr + i);
    init();
    for (ll i = 1; i <= n; i++) {
        auto best = q.top();
        q.pop();
        printf("%lld\n", -best.fi);
        del(-best.se);
    }
    return 0;
}

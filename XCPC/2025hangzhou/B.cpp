#include <bits/stdc++.h>

#include <tuple>
#define fi first
#define se second
using namespace std;
using ll = long long;
const ll MXN = 4e6 + 5;
const ll INF = 1e18;
using pi = pair<ll, ll>;
#define ls p << 1
#define rs p << 1 | 1
ll n, q;
struct node {
    pi v;
    ll t;
    node(ll x = -1) {
        v = {x, ~x};
        t = -1;
    }
} t[MXN];
void apply(ll p, ll l, ll r, ll k) {
    t[p].t &= k;
    t[p].v.fi &= k;
    if (l == r)
        t[p].v.se = ~t[p].v.fi;
    else {
        t[p].v.se &= k;
    }
}
void push(ll p, ll l, ll r) {
    ll mid = (l + r) >> 1;
    if (t[p].t != -1) {
        apply(ls, l, mid, t[p].t);
        apply(rs, mid + 1, r, t[p].t);
        t[p].t = -1;
    }
}
pi mrg(pi x, pi y) { return pi(x.fi & y.fi, (y.se & x.fi) | (x.se & y.fi)); }
void pull(ll p) { t[p].v = mrg(t[ls].v, t[rs].v); }

ll arr[MXN];
void bld(ll p, ll l, ll r) {
    if (l == r) {
        t[p] = node(arr[l]);
        return;
    }
    ll mid = (l + r) >> 1;
    bld(ls, l, mid);
    bld(rs, mid + 1, r);
    pull(p);
}
pi qry_and(ll p, ll l, ll r, ll ql, ll qr) {
    if (ql > r || qr < l) return pi{-1, 0};
    if (ql <= l && r <= qr) return t[p].v;
    ll mid = (l + r) >> 1;
    push(p, l, r);
    return mrg(qry_and(ls, l, mid, ql, qr), qry_and(rs, mid + 1, r, ql, qr));
}
void mdf_seg(ll p, ll l, ll r, ll ml, ll mr, ll mv) {
    if (ml > r || mr < l) return;
    if (ml <= l && r <= mr) {
        apply(p, l, r, mv);
        // cerr << l << " " << r << " " << mv << " " << t[p].v.se << endl;
        return;
    }
    ll mid = (l + r) >> 1;
    push(p, l, r);
    mdf_seg(ls, l, mid, ml, mr, mv);
    mdf_seg(rs, mid + 1, r, ml, mr, mv);
    pull(p);
}
void mdf_sin(ll p, ll l, ll r, ll mi, ll mv) {
    if (mi > r || mi < l) return;
    if (l == r) {
        t[p] = node(mv);
        return;
    }
    ll mid = (l + r) >> 1;
    push(p, l, r);
    mdf_sin(ls, l, mid, mi, mv);
    mdf_sin(rs, mid + 1, r, mi, mv);
    pull(p);
}

pair<ll, ll> qry_idx(ll p, ll l, ll r, ll ql, ll qr, ll qi) {
    if (ql > r || qr < l) return {0, 0};
    ll mid = (l + r) >> 1;
    if (ql <= l && r <= qr) {
        if ((t[p].v.first >> qi) & 1) return {0, 0};
        if (l == r) return {l, t[p].v.fi};
        push(p, l, r);

        auto v = qry_idx(ls, l, mid, ql, qr, qi);
        if (v.fi) return v;
        return qry_idx(rs, mid + 1, r, ql, qr, qi);
    }
    push(p, l, r);
    auto v = qry_idx(ls, l, mid, ql, qr, qi);
    if (v.fi) return v;
    return qry_idx(rs, mid + 1, r, ql, qr, qi);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    bld(1, 1, n);
    while (q--) {
        ll op, x, y, z;
        cin >> op >> x >> y;
        if (op == 1) {
            cin >> z;
            mdf_seg(1, 1, n, x, y, z);
        } else if (op == 2) {
            mdf_sin(1, 1, n, x, y);
        } else {
            auto q1 = qry_and(1, 1, n, x, y);
            if (q1.se) {
                ll hbt = 63 - __builtin_clzll(q1.second);
                auto q2 = qry_idx(1, 1, n, x, y, hbt);
                // cerr << q1.fi << " " << q1.se << " " << hbt << " " << q2.fi << " " << q2.se << endl;
                cout << (q1.fi ^ (q1.se & (~q2.se))) << "\n";
            } else {
                cout << q1.fi << "\n";
            }
        }
    }
    return 0;
}

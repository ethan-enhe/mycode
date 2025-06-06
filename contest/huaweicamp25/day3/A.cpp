#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1.3e6 + 5;
const ll INF = 1e18;
ll n, m;
ll arr[MXN];
struct val {
    ll sum, len, chg;
    ll calc(ll x) { return sum + len * x; }
    void prt() { cerr << "(" << sum << "," << len << "," << chg << ")"; }
};
const val zero = {0, 0, INF};
val operator+(val a, val b) {
    a.sum += b.sum;
    a.len += b.len;
    a.chg = min(a.chg, b.chg);
    return a;
}
ll curx;
val mx(val a, val b) {
    ll fa = a.calc(curx), fb = b.calc(curx);
    if (fa < fb) swap(a, b);
    a.chg = min(a.chg, b.chg);
    if (b.len > a.len) {
        a.chg = min(a.chg, (a.sum - b.sum + b.len - a.len) / (b.len - a.len));
    }
    return a;
}

struct node {
    val pre, suf, mxs, fxs;
    ll mnc;
    void prt() {
        cerr << mnc << ":";
        cerr << "\npre:";
        pre.prt();
        cerr << "\nsuf:";
        suf.prt();
        cerr << "\nmxs:";
        mxs.prt();
        cerr << "\nfxs:";
        fxs.prt();
    }
} t[MXN];
const node node_zero = {zero, zero, zero, zero, INF};
const node operator+(const node &ls, const node &rs) {
    node p;
    p.fxs = ls.fxs + rs.fxs;
    p.pre = mx(ls.pre, ls.fxs + rs.pre);
    p.suf = mx(rs.suf, rs.fxs + ls.suf);
    p.mxs = mx(mx(ls.mxs, rs.mxs), ls.suf + rs.pre);
    p.mnc = min({p.pre.chg, p.suf.chg, p.mxs.chg});
    return p;
}

#define ls p << 1
#define rs p << 1 | 1

void build(ll p, ll l, ll r) {
    if (l == r) {
        t[p].fxs = val{arr[l], 1, INF};
        t[p].pre = t[p].suf = t[p].mxs = mx(t[p].fxs, zero);
        t[p].mnc = min({t[p].pre.chg, t[p].suf.chg, t[p].mxs.chg});
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    t[p] = t[ls] + t[rs];
}
void upd(ll p, ll l, ll r) {
    if (curx < t[p].mnc) return;
    // cerr << "upd" << p << endl;
    if (l == r) {
        t[p].pre = t[p].suf = t[p].mxs = mx(t[p].fxs, zero);
        t[p].mnc = min({t[p].pre.chg, t[p].suf.chg, t[p].mxs.chg});
        return;
    }
    ll mid = (l + r) >> 1;
    upd(ls, l, mid);
    upd(rs, mid + 1, r);
    t[p] = t[ls] + t[rs];
}
node qry(ll p, ll l, ll r, ll ql, ll qr) {
    if (l > qr || r < ql) {
        return node_zero;
    }
    if (ql <= l && r <= qr) {
        return t[p];
    }
    ll mid = (l + r) >> 1;
    auto tmp = qry(ls, l, mid, ql, qr) + qry(rs, mid + 1, r, ql, qr);
    // cerr << l << ' ' << r << ' ';
    // tmp.prt();
    // cerr << endl;
    return tmp;
}

struct ask {
    ll l, r, h;
};
vector<ask> q;
vector<ll> p;
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    ll curh = 0;
    while (m--) {
        string s;
        ll l, r;
        cin >> s >> l;
        if (s[0] == 'A') {
            cin >> r;
            p.push_back(q.size());
            q.push_back({l, r, curh});
        } else {
            curh += l;
        }
    }
    sort(p.begin(), p.end(), [](ll x, ll y) { return q[x].h < q[y].h; });
    for (ll i = 1; i <= n; i++) arr[i] += q[p.front()].h;

    curx = 0;
    build(1, 1, n);

    for (auto i : p) {
        auto [l, r, h] = q[i];
        curx = h - q[p.front()].h;
        upd(1, 1, n);
        q[i].r = qry(1, 1, n, l, r).mxs.calc(curx);
    }
    for (auto i : q) {
        cout << i.r << '\n';
    }

    //
    // cout << qry(1, 1, n, 1, 4).mxs.calc(curx) << endl;
    // cout << qry(1, 1, n, 1, 2).mxs.calc(curx) << endl;
    // cout << qry(1, 1, n, 2, 2).mxs.calc(curx) << endl;
    //
    // curx = 2;
    // upd(1, 1, n);
    // for (int i = 1; i <= 7; i++) {
    //     cerr << "\nnode" << i << endl;
    //     t[i].prt();
    // }
    //
    // cout << qry(1, 1, n, 1, 4).mxs.calc(curx) << endl;
    // cout << qry(1, 1, n, 1, 2).mxs.calc(curx) << endl;
    // cout << qry(1, 1, n, 2, 2).mxs.calc(curx) << endl;

    return 0;
}

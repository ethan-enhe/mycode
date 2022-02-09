#include <bits/stdc++.h>
using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector

using ll = long long;
using pi = pair<ll, ll>;
using vi = vec<ll>;
using vpi = vec<pi>;
mt19937_64 myrand(65536);
//}}}
//{{{ Func
istream &operator>>(istream &is, pi &y) { return is >> y.fi >> y.se; }
ostream &operator<<(ostream &os, pi &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
template <typename T>
void read(vec<T> &x) {
    for (T &v : x) cin >> v;
}
//}}}
//{{{ fhq
struct node {
    ll sz, rnd, ls, rs;
    ll va, sum;
    ll tag;
    node() {}
    node(ll x) {
        sz = 1, rnd = myrand();
        ls = rs = 0;
        va = sum = x;
        tag = 0;
    }
};
vec<node> t;
ll nodec;
ll nnode(ll x) { return t[++nodec] = node(x), nodec; }
void apply(ll p, ll delt) {
    t[p].tag += delt;
    t[p].va += delt;
    t[p].sum += t[p].sz * delt;
}
void push(ll p) {
    if (t[p].ls) apply(t[p].ls, t[p].tag);
    if (t[p].rs) apply(t[p].rs, t[p].tag);
    t[p].tag = 0;
}
void pull(ll p) {
    t[p].sz = 1 + t[t[p].ls].sz + t[t[p].rs].sz;
    t[p].sum = t[p].va + t[t[p].ls].sum + t[t[p].rs].sum;
}
ll mrg(ll xp, ll yp) {
    if (!xp || !yp) return xp | yp;
    if (t[xp].rnd < t[yp].rnd) {
        push(xp);
        t[xp].rs = mrg(t[xp].rs, yp);
        pull(xp);
        return xp;
    } else {
        push(yp);
        t[yp].ls = mrg(xp, t[yp].ls);
        pull(yp);
        return yp;
    }
}
void splrk(ll p, ll &xp, ll &yp, ll rk) {
    if (!p)
        xp = yp = 0;
    else {
        push(p);
        ll lsz = t[t[p].ls].sz + 1;
        if (lsz <= rk)
            splrk(t[p].rs, t[xp = p].rs, yp, rk - lsz);
        else
            splrk(t[p].ls, xp, t[yp = p].ls, rk);
        pull(p);
    }
}
void splva(ll p, ll &xp, ll &yp, ll va) {
    if (!p)
        xp = yp = 0;
    else {
        push(p);
        if (t[p].va <= va)
            splva(t[p].rs, t[xp = p].rs, yp, va);
        else
            splva(t[p].ls, xp, t[yp = p].ls, va);
        pull(p);
    }
}
//}}}
ll getrng(ll p, bool f) {
    while (1) {
        push(p);
        ll nx = f ? t[p].ls : t[p].rs;
        if (nx)
            p = nx;
        else
            break;
    }
    return t[p].va;
}
ll n, ans, rt;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    t.resize(1e5 + 5);
    vpi sail(n);
    read(sail);
    sort(sail.begin(), sail.end());
    sail.insert(sail.begin(), {0, 0});
    for (int i = 1; i <= n; i++) {
        for (int j = sail[i - 1].fi; j < sail[i].fi; j++) rt = mrg(nnode(0), rt);
        ll a, b, ar, bl;
        splrk(rt, a, b, sail[i].se);
        ar = getrng(a, 0), bl = getrng(b, 1);
        ans += t[a].sum;
        apply(a, 1);
        if (ar == bl) {
            splva(a, a, ar, ar);
            splva(b, bl, b, bl);
            rt = mrg(a, mrg(bl, mrg(ar, b)));
        } else
            rt = mrg(a, b);
    }
    cout << ans;
    return 0;
}

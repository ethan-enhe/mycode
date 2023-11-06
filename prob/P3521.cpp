#include <bits/stdc++.h>
#define ls first
#define rs second
#define vec vector
#define endl '\n'
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
using vi = vec<ll>;

ll n, tnodec;
vec<pi> son;
vi w;
ll readw() {
    ll p = ++tnodec, x;
    cin >> x;
    if (x)
        w[p] = x;
    else {
        son[p].ls = readw();
        son[p].rs = readw();
    }
    return p;
}

struct node {
    ll va, ls, rs;
};
vec<node> t;
ll segnodec;
void pushu(ll p) { t[p].va = t[t[p].ls].va + t[t[p].rs].va; }
void ins(ll &p, ll l, ll r, ll qi) {
    if (!p) p = ++segnodec;
    if (l == r) {
        t[p].va = 1;
        return;
    }
    ll mid = (l + r) >> 1;
    if (qi <= mid)
        ins(t[p].ls, l, mid, qi);
    else
        ins(t[p].rs, mid + 1, r, qi);
    pushu(p);
}
ll res, resinv;
ll merge(ll xr, ll yr) {
    if (!xr || !yr) return xr | yr;
    res += t[t[xr].rs].va * t[t[yr].ls].va;
    resinv += t[t[xr].ls].va * t[t[yr].rs].va;
    t[xr].ls = merge(t[xr].ls, t[yr].ls);
    t[xr].rs = merge(t[xr].rs, t[yr].rs);
    return pushu(xr), xr;
}

ll ans;
ll dfs(ll p) {
    ll rt = 0;
    if (son[p].ls) {
        ll lr = dfs(son[p].ls), rr = dfs(son[p].rs);
        res = resinv = 0;
        rt = merge(lr, rr);
        ans += min(res, resinv);
    } else
        ins(rt, 1, n, w[p]);
    return rt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    son.resize(n * 2);
    w.resize(n * 2);
    readw();

    t.resize(n * ceil(log2(n) + 3));
    dfs(1);
    cout << ans << endl;

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define vec vector
using ll = long long;
using pi = pair<ll, ll>;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
const char nl = '\n';
const ll MXN = 1e5 + 5;
ll n, m, q, ans[MXN];
pi edge[MXN];
struct que {
    ll t, i, w;
    bool must, maybe, del;
};
vec<que> init;
ll fa[MXN], rnd[MXN];
ll stk[MXN], top;
ll find(ll x) {
    while (fa[x] != x) x = fa[x];
    return x;
}
bool mrg(ll i) {
    ll x = find(edge[i].fi), y = find(edge[i].se);
    if (fa[x] == fa[y]) return 0;
    if (rnd[x] > rnd[y]) swap(x, y);
    fa[y] = x;
    stk[++top] = y;
    return 1;
}
void undo(ll x) {
    while (top > x) {
        fa[stk[top]] = stk[top];
        top--;
    }
}
bool cmpw(const que &x, const que &y) { return x.w < y.w; }
bool vis[MXN];
ll lastt[MXN];
void cdq(vec<que> &cur, ll l, ll r, ll tot) {
    vec<que> nx;
    ll curtop = top;
    for (auto &i : cur) vis[i.i] = lastt[i.i] = 0;
    for (auto &i : cur) {
        if (i.t > l && i.t <= r)
            vis[i.i] = 1;
        else if (i.t <= l)
            lastt[i.i] = max(lastt[i.i], i.t);
        i.must = i.maybe = i.del = 0;
    }
    for (auto &i : cur)
        if (i.t > r || (i.t <= l && i.t != lastt[i.i])) i.del = 1;
    for (auto &i : cur)
        if (!i.del && vis[i.i]) mrg(i.i); //合并所有动态边
    for (auto &i : cur)
        if (!i.del) i.must = mrg(i.i); //是否必须合并
    undo(curtop);
    for (auto &i : cur)
        if (!i.del && i.must) {
            mrg(i.i);
            tot += i.w;
        }

    if (l == r) {
        cout << tot << nl;
        undo(curtop);
        return;
    }

    ll nxtop = top;
    for (auto &i : cur)
        if (!vis[i.i] && !i.del) i.maybe = mrg(i.i);

    undo(nxtop);
    for (auto &i : cur)
        if (!i.del && (vis[i.i] || i.maybe)) nx.push_back(i);

    ll mid = (l + r) >> 1;
    cdq(nx, l, mid, tot);
    cdq(nx, mid + 1, r, tot);
    nx.clear();
    undo(curtop);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    for (ll i = 1; i <= n; i++) rnd[i] = myrand(), fa[i] = i;
    for (ll i = 1, w; i <= m; i++) {
        cin >> edge[i].fi >> edge[i].se >> w;
        init.push_back({0, i, w});
    }
    for (ll i = 1, k, d; i <= q; i++) {
        cin >> k >> d;
        init.push_back({i, k, d});
    }
    sort(init.begin(), init.end(), cmpw);
    cdq(init, 1, q, 0);
    return 0;
}

#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pi;
const int INF = 1e9 + 1e6 + 5;
const int MXN = 1e5 + 5;
const int LG = 80;

#define pmx(x, y) \
    pi { max(x.fi, y.fi), max(x.se, y.se) }
#define upd(x, y) x = pmx(x, y)
struct node {
    pi v, tg;
    int ls, rs;
} t[MXN * LG];
int nodec, rt;
int newnode() {
    ++nodec;
    t[nodec].ls = t[nodec].rs = 0;
    t[nodec].tg = t[nodec].v = {0, 0};
    return nodec;
}
void init() { nodec = rt = 0; }
void addt(int &p, pi tg) {
    // if (tg == pi{0, 0}) return;
    if (!p) p = newnode();
    upd(t[p].v, tg);
    upd(t[p].tg, tg);
}
void push(int p) {
    if (t[p].tg == pi{0, 0}) return;
    addt(t[p].ls, t[p].tg);
    addt(t[p].rs, t[p].tg);
    t[p].tg = pi{0, 0};
}
void pull(int p) { t[p].v = pmx(t[t[p].ls].v, t[t[p].rs].v); }
void mmx(int &p, int l, int r, int ml, int mr, pi tg) {
    if (l > mr || r < ml) return;
    if (!p) p = newnode();
    if (l >= ml && r <= mr) {
        addt(p, tg);
        return;
    }
    push(p);
    int mid = (l + r) >> 1;
    mmx(t[p].ls, l, mid, ml, mr, tg);
    mmx(t[p].rs, mid + 1, r, ml, mr, tg);
    pull(p);
}
pi qmx(int p, int l, int r, int qi) {
    if (l == r) return t[p].v;
    push(p);
    int mid = (l + r) >> 1;
    if (qi <= mid)
        return qmx(t[p].ls, l, mid, qi);
    else
        return qmx(t[p].rs, mid + 1, r, qi);
}

int n, m;
vector<int> e[MXN];

int sz[MXN];
bool vis[MXN];
int s[MXN], ans[MXN];
vector<pi> mdf[MXN];
vector<pi> qry[MXN];
void ins(int p, int dpth) {
    int stat = -1, val = s[p];
    int lastt = 0;
    // cout << "fuck " << p << " " << dpth << endl;
    for (auto nx : mdf[p]) {
        pi tg = {stat == -1 ? val - dpth : 0, stat == 0 ? val : 0};
        mmx(rt, 0, INF, lastt, nx.fi - 1, tg);
        // cerr << lastt << " " << nx.fi - 1 << " " << tg.fi << " " << tg.se << endl;
        if (stat == -1 && nx.se == 0)
            val = max(0, val - nx.fi);
        else if (stat == 0 && nx.se == -1)
            val = val + nx.fi;
        lastt = nx.fi;
        stat = nx.se;
    }
    pi tg = {stat == -1 ? val - dpth : 0, stat == 0 ? val : 0};
    mmx(rt, 0, INF, lastt, INF, tg);
    // cerr << lastt << " " << INF << " " << tg.fi << " " << tg.se << endl;
}
int getans(int p, int t, int dpth) {
    auto res = qmx(rt, 0, INF, t);
    return max(res.fi - t - dpth, res.se);
}
void ansall(int p, int dpth) {
    for (auto [t, id] : qry[p]) {
        ans[id] = max(ans[id], getans(p, t, dpth));
    }
}
inline void dfssz(int p, int fa) {
    sz[p] = 1;
    for (size_t i = 0; i < e[p].size(); i++) {
        int nx = e[p][i];
        if (vis[nx] || nx == fa) continue;
        dfssz(nx, p);
        sz[p] += sz[nx];
    }
}
inline int dfsrt(int p, int fa, int tot) {
    bool f = (sz[p] << 1) >= tot;
    for (size_t i = 0; i < e[p].size(); i++) {
        int nx = e[p][i];
        if (vis[nx] || nx == fa) continue;
        int r = dfsrt(nx, p, tot);
        if (r) return r;
        f &= (sz[nx] << 1) <= tot;
    }
    return f ? p : 0;
}
inline void dfsm(int p, int fa, int dpth) {
    ins(p, dpth);
    for (size_t i = 0; i < e[p].size(); i++) {
        int nx = e[p][i];
        if (vis[nx] || nx == fa) continue;
        dfsm(nx, p, dpth + 1);
    }
}
inline void dfsq(int p, int fa, int dpth) {
    ansall(p, dpth);
    for (size_t i = 0; i < e[p].size(); i++) {
        int nx = e[p][i];
        if (vis[nx] || nx == fa) continue;
        dfsq(nx, p, dpth + 1);
    }
}
inline void dfz(int p) {
    dfssz(p, 0), p = dfsrt(p, 0, sz[p]);
    vis[p] = 1;
    init();
    dfsm(p, 0, 0);
    dfsq(p, 0, 0);
    // return;
    for (size_t i = 0; i < e[p].size(); i++) {
        int nx = e[p][i];
        if (vis[nx]) continue;
        dfz(nx);
    }
}

int main() {
    // init();
    // mmx(rt, 1, 10, 2, 3, {1, 2});
    // mmx(rt, 1, 10, 3, 4, {3, 1});
    // cout << "111" << endl;
    // auto res = qmx(rt, 1, 10, 2);
    // cout << res.fi << " " << res.se << endl;
    // res = qmx(rt, 1, 10, 3);
    // cout << res.fi << " " << res.se << endl;
    // res = qmx(rt, 1, 10, 4);
    // cout << res.fi << " " << res.se << endl;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= m; i++) {
        char tp;
        int x, y;
        cin >> tp >> x >> y;
        ans[i] = -1;
        if (tp == '-') {
            mdf[y].push_back({x, 0});
        } else if (tp == '+')
            mdf[y].push_back({x, -1});
        else {
            qry[y].push_back({x, i});
            ans[i] = 0;
        }
    }
    dfz(1);
    for (int i = 1; i <= m; i++) {
        if (ans[i] != -1) cout << ans[i] << endl;
    }

    return 0;
}

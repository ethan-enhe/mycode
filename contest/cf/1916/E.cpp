#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
#define NDEBUG
#endif
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using db = double;
using ld = long double;
//}}}
const int P = 1e9 + 7;
const char nl = '\n';
const int INF = 1e9;
const int MXN = 2e6 + 5;

struct pi {
    int fi, se;
};
const int DEFAULT_V = 0;
const int DEFAULT_T = 0;
template <typename v_type, typename t_type, v_type (*merge)(v_type, v_type),
          void (*addt)(int, int, v_type &, t_type &, t_type), const int SZ>
struct segt {
#define il inline
#define ls d[p].son[0]
#define rs d[p].son[1]
    struct node {
        v_type v;
        t_type t;
        int son[2];
        node() {
            son[0] = son[1] = 0;
            v = DEFAULT_V, t = DEFAULT_T;
        }
    } d[SZ];
    int nodec;
    segt() { nodec = 0; }
    void clear() {
        while (nodec) d[nodec--] = node();
    }
    il void pushd(int p, int l, int r) {
        if (!ls) ls = ++nodec;
        if (!rs) rs = ++nodec;
        int mid = (l + r) >> 1;
        addt(l, mid, d[ls].v, d[ls].t, d[p].t);
        addt(mid + 1, r, d[rs].v, d[rs].t, d[p].t);
        d[p].t = DEFAULT_T;
    }
    il void mod(int &p, int l, int r, int ml, int mr, t_type mv) {
        if (!p) p = ++nodec;
        if (ml <= l && r <= mr) {
            addt(l, r, d[p].v, d[p].t, mv);
            return;
        }
        int mid = (l + r) >> 1;
        pushd(p, l, r);
        if (ml <= mid) mod(ls, l, mid, ml, mr, mv);
        if (mr > mid) mod(rs, mid + 1, r, ml, mr, mv);
        d[p].v = merge(d[ls].v, d[rs].v);
    }
    il v_type que(int p, int l, int r, int ql, int qr) {
        if (!p || (ql <= l && r <= qr)) return d[p].v;
        int mid = (l + r) >> 1;
        v_type res = DEFAULT_V;
        pushd(p, l, r);
        if (ql <= mid) res = merge(res, que(ls, l, mid, ql, qr));
        if (qr > mid) res = merge(res, que(rs, mid + 1, r, ql, qr));
        return res;
    }
};
il int mrg(int x, int y) { return max(x, y); }
il void addt(int l, int r, int &x, int &y, int z) {
    x += z;
    y += z;
}
segt<int, int, mrg, addt, MXN> t;

ll ans = -1;
int n, m, rt;
int arr[MXN];
vector<int> g[MXN], samecolor[MXN];
int dfn[MXN], sz[MXN], dfnc;
int last[MXN];

void init(int p) {
    int pre = last[arr[p]];
    if (last[arr[p]]) samecolor[pre].push_back(p);
    last[arr[p]] = p;
    dfn[p] = ++dfnc;
    sz[p] = 1;
    for (int nx : g[p]) {
        init(nx);
        sz[p] += sz[nx];
    }
    last[arr[p]] = pre;
}
void dfs(int p) {
    for (int nx : g[p]) dfs(nx);
    for (int nx : samecolor[p]) t.mod(rt, 1, n, dfn[nx], dfn[nx] + sz[nx] - 1, -1);
    t.mod(rt, 1, n, dfn[p], dfn[p] + sz[p] - 1, 1);
    pi tmp{1, 1};
    for (int nx : g[p]) {
        int r = t.que(rt, 1, n, dfn[nx], dfn[nx] + sz[nx] - 1);
        if (r > tmp.fi) {
            tmp.se = tmp.fi;
            tmp.fi = r;
        } else if (r > tmp.se)
            tmp.se = r;
    }
    ans = max(ans, (ll)tmp.fi * tmp.se);
    // cerr << p << " " << tmp.fi << " " << tmp.se << nl;
    // cerr << p << ":";
    // for (int i = 1; i <= n; i++) cerr << t.que(rt, 1, n, dfn[i], dfn[i]).fi << " ";
    // cerr << endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 2; i <= n; i++) {
            int f;
            cin >> f;
            g[f].push_back(i);
        }
        for (int i = 1; i <= n; i++) cin >> arr[i];

        init(1);
        dfs(1);
        cout << ans << nl;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            samecolor[i].clear();
        }
        t.clear();
        dfnc = 0;
        ans = -1;
        rt = 0;
    }
    return 0;
}

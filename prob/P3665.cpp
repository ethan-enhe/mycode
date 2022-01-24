#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> _edge;
typedef pair<int, int> edge;
constexpr int MXN = 5e5, LG = 31 - __builtin_clz(MXN), INF = numeric_limits<int>::max();

int n, m, k, q, col[MXN];
_edge arr[MXN];
vector<edge> g[MXN];

int fa[MXN];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void kruskal() {
    sort(arr + 1, arr + 1 + m);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        tie(w, u, v) = arr[i];
        if (find(u) != find(v)) {
            fa[fa[v]] = fa[u];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
    }
}

struct node {
    int va, id, ls, rs;
    node() { va = INF; }
} t[MXN * LG];
int nodec, idc;
multiset<int> fa_dis_col[MXN], ans_all;
void push_up(int p) { t[p].va = min(t[t[p].ls].va, t[t[p].rs].va); }
#define erase_one(x, y) x.erase(x.find(y))
void mod_seg(int &p, int l, int r, int mi, int mv) {
    if (!p) p = ++nodec;
    if (l == r) {
        int &cid = t[p].id;
        if (!cid) cid = ++idc;
        if (mv > 0)
            fa_dis_col[cid].insert(mv);
        else
            erase_one(fa_dis_col[cid], -mv);
        t[p].va = fa_dis_col[cid].empty() ? INF : *fa_dis_col[cid].begin();
        return;
    }
    int mid = (l + r) >> 1;
    if (mi <= mid)
        mod_seg(t[p].ls, l, mid, mi, mv);
    else
        mod_seg(t[p].rs, mid + 1, r, mi, mv);
    push_up(p);
}
int que_seg(int p, int l, int r, int ql, int qr) {
    if (ql > qr) return INF;
    if (!p || (ql <= l && r <= qr)) return t[p].va;
    int mid = (l + r) >> 1, res = INF;
    if (ql <= mid) res = min(res, que_seg(t[p].ls, l, mid, ql, qr));
    if (qr > mid) res = min(res, que_seg(t[p].rs, mid + 1, r, ql, qr));
    return res;
}

int fa_dis[MXN], ans[MXN];
void dfs(int p) {
    ans_all.insert(ans[p] = INF);
    for (auto &nx : g[p])
        if (nx.first != fa[p]) {
            fa[nx.first] = p;
            fa_dis[nx.first] = nx.second;
            dfs(nx.first);
        }
}
int rt[MXN];
void upd(int x) {
    int tmp = ans[x];
    ans[x] = min(que_seg(rt[x], 1, k, 1, col[x] - 1), que_seg(rt[x], 1, k, col[x] + 1, k));
    if (ans[x] != tmp) {
        erase_one(ans_all, tmp);
        ans_all.insert(ans[x]);
    }
}
void mod(int x, int y) {
    if(col[x]==y)return;
    if (x != 1) {
        if (col[x]) mod_seg(rt[fa[x]], 1, k, col[x], -fa_dis[x]);
        mod_seg(rt[fa[x]], 1, k, y, fa_dis[x]);
        upd(fa[x]);
    }
    col[x] = y;
    upd(x);
}
int main(int argc, char *argv[]) {
    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        arr[i] = {w, u, v};
    }
    kruskal();
    fa[1] = 0;
    dfs(1);
    for (int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);
        mod(i, c);
    }
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        mod(x, y);
        printf("%d\n", *ans_all.begin());
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e6 + 5, INF = 3e7 + 5;
struct mat {
    int d[2][2];
    inline mat(int x = -INF, int y = -INF, int z = -INF, int w = -INF) {
        d[0][0] = x, d[0][1] = y, d[1][0] = z, d[1][1] = w;
    }
    inline void operator+=(const mat &y) {
        d[0][0] += y.d[0][0];
        d[0][1] += y.d[0][1];
        d[1][0] += y.d[1][0];
        d[1][1] += y.d[1][1];
    }
    inline mat operator*(const mat &y) const {
        return mat(max(d[0][0] + y.d[0][0], d[0][1] + y.d[1][0]),
                   max(d[0][0] + y.d[0][1], d[0][1] + y.d[1][1]),
                   max(d[1][0] + y.d[0][0], d[1][1] + y.d[1][0]),
                   max(d[1][0] + y.d[0][1], d[1][1] + y.d[1][1]));
    }
};
#define ls (p << 1)
#define rs (p << 1 | 1)
mat t[MXN << 2], f[MXN];
void mod(int p, int l, int r, int mi) {
    if (l == r) {
        t[p] = f[l];
        return;
    }
    int mid = (l + r) >> 1;
    if (mi <= mid)
        mod(ls, l, mid, mi);
    else
        mod(rs, mid + 1, r, mi);
    t[p] = t[rs] * t[ls];
}
mat que(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return t[p];
    int mid = (l + r) >> 1;
    mat res(0, -INF, -INF, 0);
    if (qr > mid) res = que(rs, mid + 1, r, ql, qr);
    if (ql <= mid) res = res * que(ls, l, mid, ql, qr);
    return res;
}
int n, m, arr[MXN];
vector<int> g[MXN];

int sz[MXN], top[MXN], tail[MXN], son[MXN], fa[MXN], dfn[MXN], dfnc;
int dp[MXN][2];
void dfs1(int p) {
    sz[p] = 1;
    dp[p][1] = arr[p];
    for (int nx : g[p])
        if (nx != fa[p]) {
            fa[nx] = p;
            dfs1(nx);
            sz[p] += sz[nx];
            dp[p][0] += max(dp[nx][0], dp[nx][1]);
            dp[p][1] += dp[nx][0];
            if (sz[nx] > sz[son[p]]) son[p] = nx;
        }
}
void dfs2(int p) {
    dfn[p] = ++dfnc;
    if (son[p]) {
        top[son[p]] = top[p];
        dfs2(son[p]);
    } else
        tail[top[p]] = p;
    int s0 = arr[p], s01 = 0;
    for (int nx : g[p])
        if (nx != fa[p] && nx != son[p]) {
            top[nx] = nx;
            s0 += dp[nx][0];
            s01 += max(dp[nx][0], dp[nx][1]);
            dfs2(nx);
        }
    f[dfn[p]] = mat(s01, s0, s01, -INF);
    mod(1, 1, n, dfn[p]);
}
inline void mod(int x) {
    if (top[x] == 1) {
        mod(1, 1, n, dfn[x]);
        return;
    }
    mat bef = que(1, 1, n, dfn[top[x]], dfn[tail[top[x]]]);
    mod(1, 1, n, dfn[x]);
    mat lat = que(1, 1, n, dfn[top[x]], dfn[tail[top[x]]]);
    int delt0 = lat.d[0][0] - bef.d[0][0],
        delt01 = max(lat.d[0][0], lat.d[0][1]) - max(bef.d[0][0], bef.d[0][1]);
    f[dfn[fa[top[x]]]] += mat(delt01, delt0, delt01, 0);
    mod(fa[top[x]]);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", arr + i);
    for (int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    int last = 0;
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        x ^= last;
        f[dfn[x]].d[0][1] += y - arr[x];
        arr[x] = y;
        mod(x);
        mat res = que(1, 1, n, 1, dfn[tail[1]]);
        printf("%d\n", last = max(res.d[0][0], res.d[0][1]));
    }
    return 0;
}

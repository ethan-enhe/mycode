#include <bits/stdc++.h>

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int MXN = 1000, H = 8;
int n, rt = 1, mxd, sz[MXN];
char prt[MXN][MXN], ans[MXN][MXN];
int l[MXN], r[MXN];
vector<int> g[MXN];
inline void draw(int x1, int y1, int x2, int y2) {
    if (y1 < y2) {
        while (y1 < y2) {
            ans[x1][y1] = '\\';
            x1++, y1++;
        }
        if (x1 <= x2) {
            ans[x1][y1] = '\\';
            x1++;
        }
    } else if (y1 > y2) {
        while (y1 > y2) {
            ans[x1][y1] = '/';
            x1++, y1--;
        }
        if (x1 <= x2) {
            ans[x1][y1] = '/';
            x1++;
        }
    }
    while (x1 <= x2) {
        ans[x1][y1] = '|';
        x1++;
    }
}
inline void init(int p, int fa) {
    r[p] = l[p];
    for (int nx : g[p])
        if (nx != fa) {
            l[nx] = r[p];
            init(nx, p);
            r[p] = r[nx];
        }
    r[p] = max(r[p], l[p] + sz[p]) + 1;
}
inline void dfs(int p, int fa, int dpth) {
    mxd = (max(mxd, dpth));
    int mxh = 1, deg = g[p].size() - (p != rt), tmp = (l[p] + r[p] - deg) >> 1;
    for (int nx : g[p])
        if (nx != fa) mxh = max(mxh, abs(((l[nx] + r[nx] - 1) >> 1) - tmp++));
    for (int nx : g[p])
        if (nx != fa) dfs(nx, p, dpth + mxh + 1);
    tmp = (l[p] + r[p] - sz[p]) >> 1;
    memcpy(ans[dpth] + tmp, prt[p], sizeof(char) * sz[p]);
    tmp = (l[p] + r[p] - deg) >> 1;
    for (int nx : g[p])
        if (nx != fa)
            draw(dpth + 1, tmp++, dpth + mxh, (l[nx] + r[nx] - 1) >> 1);
}

int main() {
    freopen("test.in", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", prt[i]);
        sz[i] = strlen(prt[i]);
    }
    for (int i = 1; i < n; i++) {
        int ts, tt;
        scanf("%d%d", &ts, &tt);
        g[ts].push_back(tt);
        g[tt].push_back(ts);
    }
    memset(ans, ' ', sizeof(ans));
    init(rt, 0);
    dfs(rt, 0, 0);
    for (int i = 0; i <= mxd; i++) {
        for (int j = 0; j <= r[1]; j++) putchar(ans[i][j]);
        putchar('\n');
    }
    return 0;
}

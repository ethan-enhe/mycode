#include <bits/stdc++.h>

#define umn(x, y) x = min(x, y)
using namespace std;
//{{{ Rand
namespace GenHelper {
unsigned z1, z2, z3, z4, b;
unsigned rand_() {
    b = ((z1 << 6) ^ z1) >> 13;
    z1 = ((z1 & 4294967294U) << 18) ^ b;
    b = ((z2 << 2) ^ z2) >> 27;
    z2 = ((z2 & 4294967288U) << 2) ^ b;
    b = ((z3 << 13) ^ z3) >> 21;
    z3 = ((z3 & 4294967280U) << 7) ^ b;
    b = ((z4 << 3) ^ z4) >> 12;
    z4 = ((z4 & 4294967168U) << 13) ^ b;
    return (z1 ^ z2 ^ z3 ^ z4);
}
void srand(unsigned x) {
    z1 = x;
    z2 = (~x) ^ 0x233333333U;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
}
int read() {
    int a = rand_() & 32767;
    int b = rand_() & 32767;
    return a * 32768 + b;
}
} // namespace GenHelper
//}}}
const int MXN = 3e5 + 5, LG = 31 - __builtin_clz(MXN), INF = 1e9;
int n, q, s,cnt;
int fa[MXN], w[MXN];
bool notleaf[MXN];
vector<int> g[MXN];

int dp[MXN], tot[MXN], pre[MXN];
void dfsup(int p) {
    for (int nx : g[p]) {
        dfsup(nx);
        dp[p] += dp[nx];
    }
    umn(dp[p], w[p]);
}
void dfsdown(int p) {
    int tmp = dp[p];
    for (int nx : g[p]) tmp += dp[nx];
    for (int nx : g[p]) {
        umn(dp[nx], tmp - dp[nx]);
        dfsdown(nx);
    }
    for (int nx : g[p]) {
        tot[p] += dp[nx];
        pre[nx] = tot[p];
    }
}
int tmp[2];
struct data {
    int dis[2][2], anc;
	void init(int _anc = 0) {
        anc = _anc;
        dis[0][0] = dis[0][1] = 0;
        dis[1][0] = dis[1][1] = INF;
    }
#define upd(x, y) res.dis[x][y] = min(dis[x][0] + b.dis[0][y], dis[x][1] + b.dis[1][y])
    data operator+(const data &b) {
        data res;
        upd(0, 0), upd(0, 1);
        upd(1, 0), upd(1, 1);
        res.anc = b.anc;
        return res;
    }
#undef upd
#define upd(x) tmp[x] = min(dis[0][0] + b.dis[0][x], dis[0][1] + b.dis[1][x])
    void operator^=(const data &b) {
        upd(0), upd(1);
		dis[0][0]=tmp[0];
		dis[0][1]=tmp[1];
        anc = b.anc;
    }
#undef upd
#undef upd
} jmp[MXN][LG + 1];
int dpth[MXN];
void init_lca(int p) {
    jmp[p][0].anc = fa[p];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            int ldis = pre[p] - (i ? 0 : dp[p]) + (j ? dp[fa[p]] : 0);
            int rdis = tot[fa[p]] - pre[p] + (i ? 0 : dp[p]) + (j ? 0 : dp[fa[p]]);
            jmp[p][0].dis[i][j] = min(ldis, rdis);
        }
    for (int i = 1; (1 << i) <= dpth[p]; i++) jmp[p][i] = jmp[p][i - 1] + jmp[jmp[p][i - 1].anc][i - 1];
    for (int nx : g[p]) {
        dpth[nx] = dpth[p] + 1;
        init_lca(nx);
    }
}
int solve(int x, int y) {
    if (x == y) return 0;
    if (dpth[x] < dpth[y]) swap(x, y);
    data dx,dy;
	dx.init(x),dy.init(y);

    if (dpth[x] != dpth[y]) {
        int tmp = dpth[x] - dpth[y] - 1;
        for (int i = LG; ~i; i--) if ((tmp >> i) & 1) dx ^= jmp[dx.anc][i];
        if (fa[dx.anc] == dy.anc) 
            return min(dx.dis[0][0], dx.dis[0][1]);
        dx ^= jmp[dx.anc][0];
    }
    for (int i = LG; ~i; i--)
        if (jmp[dx.anc][i].anc != jmp[dy.anc][i].anc) {
            dx ^= jmp[dx.anc][i];
            dy ^= jmp[dy.anc][i];
        }
    if (dx.anc > dy.anc) swap(dx, dy);
    x = dx.anc, y = dy.anc;
    int l = fa[x], ans = INF;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            int idis = pre[y] - pre[x] - (j ? 0 : dp[y]) + (i ? 0 : dp[x]);
            int odis = tot[l] + dp[l] - idis;
            umn(ans, min(idis, odis) + dx.dis[0][i] + dy.dis[0][j]);
        }
    return ans;
}

int main() {
	freopen("test.in","r",stdin);
    scanf("%d%d%d", &n, &q, &s);
    GenHelper::srand(s);
    for (int i = 2; i <= n; i++) {
        scanf("%d%d", fa + i, w + i);
        g[fa[i]].push_back(i);
        notleaf[fa[i]] = 1;
    }
    scanf("%d", w + 1);
    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
        if (!notleaf[i]) scanf("%d", dp + i);
    }
    dfsup(1);
    dfsdown(1);
    init_lca(1);
    int last = 0, xsum = 0;
    long long sum = 0;
    while (q--) {
        int u = (GenHelper::read() ^ last) % n + 1, v = (GenHelper::read() ^ last) % n + 1;
        last = solve(u, v);
        xsum ^= last;
        sum += last;
    }
    printf("%d %lld", xsum, sum);
	cerr<<endl<<cnt;

    return 0;
}

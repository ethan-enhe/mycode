#include <bits/stdc++.h>
using namespace std;

//{{{ Def
#define fi first
#define se second

typedef pair<int, int> pi;
//}}}
template <class T>
void umx(T &x, T y) {
    x = max(x, y);
}
const int N = 10, MXN = N + 5, CSZ = 55, MXL = CSZ * 2;
int n, m;
bool id[MXN][MXL];
int plc[MXN][CSZ][2], pre[MXN][MXL][CSZ];
int dp[CSZ][1 << MXN];
pi from[CSZ][1 << MXN];
char str[MXN][MXL];

int char2int(char x) {
    if (x >= 'a' && x <= 'z') return x - 'a';
    if (x >= 'A' && x <= 'Z') return x - 'A' + 26;
    return 52;
}
char int2char(int x) {
    if (x == 52) return '\n';
    if (x >= 0 && x < 26) return 'a' + x;
    return 'A' + x - 26;
}
int dfs(int i, int j) {
    if (~dp[i][j]) return dp[i][j];
    dp[i][j] = 0, from[i][j] = {-1, -1};
    for (int nxi = 0; nxi < CSZ; nxi++) {
        int nxj = 0;
        bool f = 1;
        for (int k = 0; k < n; k++) {
            int nxid = pre[k][plc[k][i][(j >> k) & 1] - 1][nxi];
            if (!nxid) {
                f = 0;
                break;
            }
            nxj |= (int)id[k][nxid] << k;
        }
        if (f) {
            int tmp = dfs(nxi, nxj);
            if (tmp > dp[i][j]) {
                dp[i][j] = tmp;
                from[i][j] = {nxi, nxj};
            }
        }
    }
    return ++dp[i][j];
}
stack<int> ans;
void solve() {
	//freopen("test.in","r",stdin);
    memset(plc, 0x3f, sizeof(plc));
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str[i] + 1);
        int tlen = strlen(str[i] + 1);
        str[i][++tlen] = '*';
        for (int j = 1; j <= tlen; j++) {
            memcpy(pre[i][j], pre[i][j - 1], sizeof(pre[i][j]));
            str[i][j] = char2int(str[i][j]);
            plc[i][str[i][j]][id[i][j] = pre[i][j][str[i][j]]] = j;
            pre[i][j][str[i][j]] = j;
        }
    }
    memset(dp, -1, sizeof(dp));
    printf("%d\n", dfs(52, 0) - 1);
    pi ind = {52, 0};
    while (~ind.fi) {
        ans.push(ind.fi);
        ind = from[ind.fi][ind.se];
    }
    while (!ans.empty()) {
        putchar(int2char(ans.top()));
        ans.pop();
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();

    return 0;
}

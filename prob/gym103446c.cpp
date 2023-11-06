// dp[i][j][s][f][g]
// 表示:
// 搞到第i行第j列
// 每列是否被钦定纵向覆盖，是否已经纵向覆盖
// 当前横向的块是否被钦定横向覆盖，是否已经横向覆盖
// 所需要花费的最少车数量
// %3=
// 0：都没有
// 1：钦定了
// 2：钦定并且放了
#include <bits/stdc++.h>

using namespace std;
const int pw3[] = {1,     3,      9,      27,      81,      243,      729,      2187,      6561,      19683,
                   59049, 177147, 531441, 1594323, 4782969, 14348907, 43046721, 129140163, 387420489, 1162261467};
const int N = 12, MXN = N + 2, MXS = pw3[N], INF = 1e9;

int n, m;
char str[MXN][MXN], tmp[MXN * MXN];
int nx[MXS][3], cur[MXS][3], U, D;
inline void upd(int &x, const int &y) { x = min(x, y); }
inline void scroll() {
    for (int i = 0; i < U; i++) {
        cur[i][0] = nx[i][0];
        cur[i][1] = nx[i][1];
        cur[i][2] = nx[i][2];
        nx[i][0] = INF;
        nx[i][1] = INF;
        nx[i][2] = INF;
    }
}
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    memset(str, '1', sizeof(str));
    if (m > n) {
        for (int i = 1; i <= n; i++) {
            cin >> (tmp + 1);
            for (int j = 1; j <= m; j++) str[j][i] = tmp[j];
        }
        swap(m, n);
    } else
        for (int i = 1; i <= n; i++) cin >> (str[i] + 1);
    U = pw3[m], D = pw3[m - 1];
    memset(nx, 0x3f, sizeof(nx));
    nx[0][0] = 0;
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 1; j <= m; j++) {
            scroll();
            for (int s = 0; s < U; s++) {
                int hi = s / D;
                for (int cf = 0; cf < 3; cf++) {
                    if (cur[s][cf] >= INF) continue;
                    if (str[i][j] == '0' || str[i][j] == '2') {
                        int nxs = (s * 3 + hi) % U;
                        //不放（这行或这列钦定放了）
                        if (cf || hi) upd(nx[nxs][cf], cur[s][cf]);
                        //放（这行和这列都钦定放了）
                        if (cf && hi) upd(nx[nxs + (hi == 1)][cf + (cf == 1)], cur[s][cf] + 1);
                    }
                    if (str[i][j] == '1' || str[i][j] == '2') {
                        //如果钦定有，但是实际没有，则寄了
                        if (hi == 1 || cf == 1) continue;
                        int nxs = s * 3 % U;
                        upd(nx[nxs][0], cur[s][cf]);
                        upd(nx[nxs][1], cur[s][cf]);
                        upd(nx[nxs + 1][0], cur[s][cf]);
                        upd(nx[nxs + 1][1], cur[s][cf]);
                    }
                }
            }
        }
        //处理到下一行
        scroll();
        for (int s = 0; s < U; s++) nx[s][1] = nx[s][0] = min(cur[s][0], cur[s][2]);
    }
    cout << nx[0][0];

    return 0;
}

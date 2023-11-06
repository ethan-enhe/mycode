#include <bits/stdc++.h>
using namespace std;
const int MXN = 55, MXT = 2505;
int n, m, t;
char str[MXN];
int f[MXT], g[MXN][MXT];
void cal() {
    for (int i = 1; i <= m; i++) {
        memcpy(g[i], g[i - 1], sizeof(int) * MXT);
        for (int j = i - 1, cnt = 0, mx; ~j; j--) {
            cnt += str[j + 1] - '0';
            mx = max(cnt, i - j - cnt);
            for (int l = 1; l <= t; l++) g[i][l] = max(g[i][l], g[j][l - 1] + mx);
        }
    }
}
void upd() {
    for (int i = t; i; i--)
        for (int j = 1; j <= i; j++) f[i] = max(f[i], f[i - j] + g[m][j]);
}
int main(int argc, char *argv[]) {
    scanf("%d%d%d", &n, &m, &t);
    while (n--) {
        scanf("%s", str + 1);
        cal();
        /* for (int i = 1; i <= t; i++) cout << g[m][i] << " \n"[i == t]; */
        upd();
    }
    printf("%d", f[t]);

    return 0;
}

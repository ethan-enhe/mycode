#include <bits/stdc++.h>
using namespace std;
const int MXN = 55;
int n, m, a, b;
int arr[MXN], pool[MXN];
int f[MXN][MXN][MXN][MXN], g[MXN][MXN];
void umn(int &x, int y) { x = min(x, y); }
int sq(int x) { return x * x; }
int main(int argc, char *argv[]) {
    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", arr + i);
        pool[i] = arr[i];
    }
    sort(pool + 1, pool + 1 + n);
    m = unique(pool + 1, pool + 1 + n) - pool - 1;
    for (int i = 1; i <= n; i++) arr[i] = lower_bound(pool + 1, pool + 1 + m, arr[i]) - pool;
    for (int l = n; l; l--)
        for (int r = l; r <= n; r++) {
            if (l == r) {
                g[l][l] = a;
                for (int vl = 1; vl <= arr[l]; vl++)
                    for (int vr = arr[l]; vr <= m; vr++) f[l][l][vl][vr] = 0;
            } else {
                for (int vl = 1; vl <= m; vl++)
                    for (int vr = vl; vr <= m; vr++) {
                        for (int mid = l; mid < r; mid++)
                            umn(f[l][r][vl][vr],
                                min(f[l][mid][vl][vr], g[l][mid]) + min(f[mid + 1][r][vl][vr], g[mid + 1][r]));
                        umn(g[l][r], f[l][r][vl][vr] + a + b * sq(pool[vr] - pool[vl]));
                    }
            }
        }
    printf("%d\n", g[1][n]);

    return 0;
}


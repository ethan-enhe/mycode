#include <bits/stdc++.h>

#include <algorithm>
using namespace std;
const int MXN = 2e5 + 100, MXK = 9, ZERO = 40, NR = ZERO * 2, INF = 2e9;
char str[MXN];
int tmp[MXN];
int dp[NR][MXN], last[NR][MXN];
int n, k, lim, di;
void cpy(int *from, int *dest) {
    for (int i = 0; i <= lim; i++) dest[i] = from[i];
}
bool add(int *tmp, int l, int r) {
    if (l >= 0 && r < n && l <= r) {
        for (int i = 0; i <= lim; i++) {
            if (r - i >= l) tmp[i] += str[r - i] - '0';
            if (tmp[i] >= 10) tmp[i] -= 10, tmp[i + 1]++;
        }
        return 1;
    }
    return 0;
}
void updans(int *tmp, int *ans) {
    for (int i = lim; i >= 0; i--) {
        if (tmp[i] > ans[i]) return;
        if (tmp[i] < ans[i]) {
            break;
        }
    }
    for (int i = 0; i <= lim; i++) ans[i] = tmp[i];
}
void setinf(int *tmp) {
    for (int i = 0; i <= lim; i++) tmp[i] = INF;
}
void setzero(int *tmp) {
    for (int i = 0; i <= lim; i++) tmp[i] = 0;
}
int id(int x, int y) { return x * di + y - ZERO; }
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        // 9191919111
        cin >> n >> k;
        cin >> str;
        lim = n + 5;
        di = n / (k + 1);
        for (int i = 0; i < NR; i++) setinf(last[i]);
        setzero(last[ZERO]);
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j < NR; j++) setinf(dp[j]);
            for (int j = 0; j < NR; j++) {
                if (last[j][0] == INF) continue;
                for (int l = 0; l < NR; l++) {
                    if (id(i, j) < 0 && id(i, j) > n) continue;
                    if (id(i + 1, l) < 0 && id(i + 1, l) > n) continue;
                    cpy(last[j], tmp);
                    add(tmp, id(i, j), id(i + 1, l) - 1);
                    updans(tmp, dp[l]);
                }
            }
            for (int j = 0; j < NR; j++) {
                cpy(dp[j], last[j]);
            }
        }
        bool f = 0;
        for (int i = lim; i >= 0; i--) {
            int v = last[ZERO + n % (k + 1)][i];
            if (f || v) {
                f = 1;
                cout << v;
            }
        }
        cout << '\n';
    }
    return 0;
}

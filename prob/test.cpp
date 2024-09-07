#pragma GCC optimize("O3")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

const int MXN = 1e6 + 5;

int k;
bool pat_mat(int i, int j) { return j <= i; }
int act_mat(int i, int j) { return __builtin_popcount(i ^ j) == k; }
bool used_line[MXN], used_col[MXN];
int line[MXN], col[MXN];
bool dfs(int cursz, int tgsz, int n) {
    if (cursz == tgsz) {
        cout << "OK" << endl;
        for (int i = 1; i <= cursz; i++) cout << bitset<10>(line[i]) << " " << bitset<10>(col[i]) << endl;
        return 1;
    }
    bool res = 0;
    for (int i = 0; i < n; i++) {
        if (used_line[i]) continue;
        bool chk_newline = 1;
        for (int j = 1; j <= cursz; j++) chk_newline &= pat_mat(cursz + 1, j) == act_mat(i, col[j]);
        if (!chk_newline) continue;
        used_line[i] = 1;
        line[cursz + 1] = i;

        for (int j = 0; j <n; j++) {
            if (used_col[j]) continue;
            bool chk_newcol = 1;
            for (int k = 1; k <= cursz + 1; k++) chk_newcol &= pat_mat(k, cursz + 1) == act_mat(line[k], j);
            if (!chk_newcol) continue;
            used_col[j] = 1;
            col[cursz + 1] = j;
            res |= dfs(cursz + 1, tgsz, n);
            // if (res) return res;
            used_col[j] = 0;
        }
        used_line[i] = 0;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // for (k = 0; k <= 1; k++) {
    k = 1;
    for (int i = 1; i <= 10; i++) {
        if (dfs(0, k * 2 + 1, 1 << i)) {
            cout << "k=" << k << " i=" << i << endl;
            break;
        }
    }
    // }
    return 0;
}


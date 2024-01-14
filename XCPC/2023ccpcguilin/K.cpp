#include <bits/stdc++.h>

#include <vector>

using namespace std;
using ull = unsigned long long;
const char nl = '\n';
const int MXN = 185;
const int MXP = 4.5e4;

int n, m;
vector<int> arr[MXN];
int tmp[MXN];
void genp(vector<int> &x, vector<int> &y) {
    for (int i = 0; i < n; i++) tmp[i] = x[y[i]];
    for (int i = 0; i < n; i++) x[i] = tmp[i];
}
ull genhash(ull base, vector<int> &x) {
    ull res = 0;
    for (auto i : x) res = res * base + i;
    return res;
}
set<ull> res;
void dfs(int idx, vector<int> v, bool f = 0) {
    if (idx == m + 1) {
        if (f) res.insert(genhash(203, v));
        return;
    }
    dfs(idx + 1, v, f);
    genp(v, arr[idx]);
    dfs(idx + 1, v, 1);
}
int id[1 << 24];
vector<int> per[MXP];
bool dp[MXP], nx[MXP];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        arr[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            --arr[i][j];
        }
    }

    vector<int> p0(n);
    for (int i = 0; i < n; i++) p0[i] = i;
    if (m <= 20) {
        dfs(1, p0);
        cout << res.size() << nl;
    } else {
        int cnt = 0;
        do {
            per[cnt] = p0;
            id[genhash(8, p0)] = cnt++;
        } while (next_permutation(p0.begin(), p0.end()));
        for (int i = 1; i <= m; i++) {
            nx[id[genhash(8, arr[i])]] = 1;
            for (int j = 0; j < cnt; j++) {
                if (dp[j]) {
                    nx[j] = 1;
                    vector<int> tmp = per[j];
                    genp(tmp, arr[i]);
                    nx[id[genhash(8, tmp)]] = 1;
                }
            }
            swap(dp, nx);
        }
        int ans = 0;
        for (int i = 0; i < cnt; i++) ans += dp[i];
        cout << ans;
    }
    return 0;
}

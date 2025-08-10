#include <bits/stdc++.h>
using namespace std;
const int MXN = 300;
int arr[MXN], n;
vector<int> fac[MXN];
int weight[MXN];
int mn = 1e9;
bool vis[MXN];
void dfs(int i, int sum = 0) {
    if (sum > mn) return;
    if (i == n + 1) {
        mn = min(mn, sum);
        return;
    }
    for (int f : fac[i]) {
        if (vis[f]) continue;
        if (i == 1 && f == 1) cout << "!!!" << endl;
        vis[f] = 1;
        dfs(i + 1, sum + weight[f]);
        vis[f] = 0;
    }
}
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    weight[1] = 0;
    for (int i = 2; i < MXN; i++) {
        for (int j = 2; j <= i; j++)
            if (i % j == 0) {
                weight[i] = weight[j] + 1;
                break;
            }
    }

    int tot = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        tot += weight[arr[i]];
        for (int j = 1; j * j <= arr[i]; j++) {
            if (arr[i] % j == 0) fac[i].push_back(j), fac[i].push_back(arr[i] / j);
        }
        sort(fac[i].begin(), fac[i].end(), [&](int a, int b) { return weight[a] < weight[b]; });
        unique(fac[i].begin(), fac[i].end());
    }
    dfs(1, 0);
    cout << tot - mn;
    return 0;
}

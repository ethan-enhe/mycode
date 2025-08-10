#include <bits/stdc++.h>
using namespace std;
const int MXN = 5e4 + 5;
bitset<MXN> lf[MXN], rt[MXN], arr[MXN], tmp, all1;
int n, m, p[MXN], inv[MXN];
int main() {
    all1.set();
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        inv[p[i]] = i;
    }
    tmp.reset();
    for (int i = n; i >= 1; i--) {
        arr[inv[i]] = tmp >> inv[i];
        tmp.set(inv[i]);
    }
    for (int i = m; i <= n; i += m) {
        for (int j = 0; j < m; j++) {
            lf[i - j] = arr[i - j] & (j ? lf[i - j + 1] : all1);
            if (i + j + 1 <= n) rt[i + j + 1] = arr[i + j + 1] & (j ? rt[i + j] : all1);
        }
        // if (lf[995][1] == 1) {
        //     cout << i << endl;
        //     break;
        // }
    }
    // for (int i = 1000; i; i--) {
    //     bool f = 1;
    //     for (int j = 1; j <= 10; j++) cout << lf[i][j];
    //     cout << endl;
    //     for (int j = 1; j <= 10; j++) cout << arr[i][j];
    //     cout << endl;
    //     if (lf[i][1] != 1) {
    //         f = 0;
    //         break;
    //     }
    // }
    long long ans = 0;
    for (int i = 1; i + m - 1 <= n; i++) {
        bitset<MXN> res = ((i - 1) % m == 0) ? lf[i] : (lf[i] & rt[i + m - 1]);
        ans += res.count();
        // if (res.count() != n - m + 1 - i) {
        //     cout << "i: " << i << " " << res.count() << endl;
        //     break;
        // }
    }
    cout << ans;
    return 0;
}

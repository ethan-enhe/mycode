#include <bits/stdc++.h>

using namespace std;
const int MXN = 5e4 + 5;
const int INF = 1e9;
bitset<MXN> lower, ans, mask, tmp;
char a[MXN], b[MXN];
int n, pre[MXN], ord[MXN];

int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    mask.set();
    while (t--) {
        cin >> n >> (a + 1) >> (b + 1);
        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + (a[i] == '1' ? 1 : -1);
            // cerr << pre[i] << " ";
        }
        // cerr << endl;
        iota(ord, ord + 1 + n, 0);
        sort(ord, ord + 1 + n, [](int x, int y) { return pre[x] < pre[y]; });
        pre[n + 1] = INF;
        lower.reset();
        ans.set();
        for (int i = 0, j = 0; i <= n; i++) {
            while (pre[ord[j]] < pre[ord[i]]) lower[n - ord[j++]] = 1;
            if (ord[i]) {
                tmp = lower >> (n - ord[i]);
                if (pre[ord[i]] > 0)
                    tmp |= mask << (1 + ord[i]);
                else
                    tmp &= ~(mask << (1 + ord[i]));
                if (b[ord[i]] == '0') tmp = ~tmp;
                ans &= tmp;
            }
            // cerr << ord[i] << endl;
            // for (int i = 1; i <= n; i++) cout << tmp[i];
            // cout << endl;
            // for (int i = 1; i <= n; i++) cout << ans[i];
            // cout << endl;
        }
        for (int i = 1; i <= n; i++) cout << ans[i];
        cout << '\n';
    }

    return 0;
}

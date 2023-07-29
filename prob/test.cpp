#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
const char nl = '\n';
const int MXN = 10000 + 5;
const int INF = 1e9;

int n, m, k, arr[MXN], brr[MXN];

int dp[MXN];
int nx[MXN];
int mxb[MXN];
int q[MXN];
int ql, qr;

int main() {
    freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
            dp[i] = 0;
        }
        for (int i = 1; i <= m; i++) cin >> brr[i];
        // dp[i]递减
        for (int _k = 1; _k <= k; _k++) {
            int mx = 0;
            ql = 1, qr = 0;
            for (int i = n; i; i--) {
                // 枚举最后一次选的a
                while (ql <= qr && arr[q[qr]] <= arr[i]) --qr;
                q[++qr] = i;
                while (ql <= qr && _k + n + m - q[ql] - dp[i - 1] < k) ++ql;
                if (ql <= qr) mx = max(mx, arr[q[ql]]);
            }
            ql = 1, qr = 0;
            for (int i = 0; i <= n; i++) {
                int up_bound = (i == 0 ? m : min(dp[i - 1], m));
                for (int j = up_bound; j > dp[i]; j--) {
                    while (ql <= qr && brr[q[qr]] <= brr[j]) --qr;
                    q[++qr] = j;
                }
                while (ql <= qr && _k + n + m - q[ql] - i < k) ++ql;
                if (ql <= qr)
                    mx = max(mx, brr[mxb[i] = q[ql]]);
                else
                    mxb[i] = INF;
            }
            int mn = INF;
            nx[0] = INF;
            // cerr << _k << " ";
            for (int i = 0; i <= n; i++) {
                // cerr << dp[i] << " ";
                if (i) mn = min(mn, dp[i - 1]), nx[i] = nx[i - 1];
                if (arr[i] == mx) nx[i] = min(nx[i], mn);
                if (mxb[i] != INF && brr[mxb[i]] == mx) nx[i] = min(nx[i], mxb[i]);
            }
            // cerr << nl;
            for (int i = 0; i <= n; i++) dp[i] = nx[i];
            cout << mx;
        }
        cout << nl;
    }
    return 0;
}


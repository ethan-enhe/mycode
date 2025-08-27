#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e6 + 5;
int n, arr[MXN];
int main() {
    // freopen("./test.in","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i <= n; i++) {
            cin >> arr[i];
        }
        arr[n + 1] = 0;
        while (arr[n] == 0) --n;
        int i = 0;
        string ans;
        while (1) {
            // cerr<<i<<endl;
            if ((i && arr[i - 1] > 1) && (i == n || arr[i] > 1)) {
                ans += 'L';
                --i;
                --arr[i];
            } else if (arr[i + 1] >= 1) {
                ans += 'R';
                ++i;
                --arr[i];
            } else {
                break;
            }
        }
        while (i) {
            ans += 'L';
            --i;
            --arr[i];
        }
        bool f = 0;
        for (int i = 0; i <= n; i++) {
            // cerr<<arr[i]<<" ";
            if (arr[i] != 0) f = 1;
        }
        if (f) {
            cout << "Impossible\n";
        } else {
            cout << ans << '\n';
        }
    }

    return 0;
}

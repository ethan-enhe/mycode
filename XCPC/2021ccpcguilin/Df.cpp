#include <bits/stdc++.h>
#define ll long long
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pb push_back
#define ppb pop_back
using namespace std;
const int maxn = 2100;
int m[2100];
int A[maxn];
int B[maxn];
int f1[maxn];
int f2[maxn];
vector<pair<int, int>> ans;
int main() {
    fast;
    int T;
    cin >> T;
    while (T--) {
        ans.clear();
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> A[i];
            f1[A[i]] = i;
        }
        for (int i = 1; i <= n; i++) {
            cin >> B[i];
            f2[B[i]] = i;
        }
        int flag = 1;
        for (int i = n; i > 1; i--) {
            int L = f1[i], R = f2[i];
            if (L > R) {
                flag = 0;
                break;
            }
            if (L == R) {
                continue;
            }
            int l = 1, r = 0;
            for (int j = L + 1; j <= R; j++) {
                if (A[j] > i) continue;
                while (l <= r && A[j] > m[r]) r--;
                m[++r] = A[j];
            }
            if (l > r) {
                flag = 0;
                break;
            }
            while (L < R) {
                ans.pb(make_pair(L, f1[m[l]]));
                // cout<<L<<' '<<f1[m[l]]<<'\n';
                swap(A[L], A[f1[m[l]]]);
                swap(f1[i], f1[m[l]]);
                L = f1[i];
                l++;
                // for (int j = 1; j <= n; j++)
                // {
                //     cout << A[j] << ' ';
                // }
                // cout << '\n';
                // for (int j = 1; j <= n; j++)
                // {
                //     cout << f1[j] << ' ';
                // }
                // cout << '\n';
                // for (int j = l; j <= r; j++)
                // {
                //     cout << m[j] << ' ';
                // }
                // cout << '\n';
            }
            if (flag == 0) break;
        }
        if (flag) {
            // cout << 1 << '\n';
            cout << ans.size() << '\n';
            for (int i = 0; i < ans.size(); i++)
            {
                cout << ans[i].first << ' ' << ans[i].second << '\n';
            }
        } else
            cout << "-1\n";
    }
}

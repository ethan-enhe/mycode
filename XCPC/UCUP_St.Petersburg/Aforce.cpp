// a force for A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MXN = 5e4 + 5;
int n, m, arr[MXN];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int ans = 0;
    for (int i = 1; i + m - 1 <= n; i++) {
        for (int j = i + 1; j + m - 1 <= n; j++) {
            bool f = 1;
            for (int k = 0; k < m; k++) {
                if (arr[j + k] < arr[i + k]) {
                    f = 0;
                    break;
                }
            }
            ans += f;
        }
    }
    cout << ans;
    return 0;
}

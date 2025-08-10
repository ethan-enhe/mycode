#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using pi = pair<int, int>;
const int MXN = 2505;
const int INF = 1e9;
int arr[MXN], n;
int row, lim;
pi x[MXN], y[MXN];
int idxx, idxy;
int ans = 0, ians = 0;

void ins(int sz) {
    auto getv = [&](int a, pi b) -> int {
        if (abs(b.fi - a) <= 1) return b.se;
        return 0;
    };
    bool wrap = row + 1 + sz > lim;
    if (row && !wrap) {
        ++row;
        while (y[idxy].first < row - 1) ++idxy;
        // if(row==13){
        //     cout<<idxy<<" "<<y[idxy].fi<<endl;
        // }
        x[++idxx] = {row, 1 + max({getv(row, y[idxy + 2]), getv(row, y[idxy]), getv(row, y[idxy + 1])})};
        if (x[idxx].se > ans) {
            ans = x[idxx].se;
            ians = lim;
        }
    }
    if (!wrap) {
        row += sz;
    } else {
        // for (int i = 1; i <= idxx; i++) { cout << x[i].fi << " " << x[i].se << ",";
        // }
        // cout << endl;
        x[++idxx] = {INF, 0};
        x[++idxx] = {INF, 0};
        x[++idxx] = {INF, 0};
        idxx = idxy = 0;
        swap(x, y);
        row = sz;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int mx = 0, sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string x;
        cin >> x;
        arr[i] = x.size();
        mx = max(mx, arr[i]);
        sum += arr[i];
    }
    for (int len = mx; len <= sum + n; len++) {
        // int len = 21;
        idxx = idxy = 0;
        row = 0;
        y[3] = y[1] = y[2] = {INF, 0};
        lim = len;
        for (int j = 1; j <= n; j++) ins(arr[j]);
    }
    cout << ians << " " << ans;
    return 0;
}

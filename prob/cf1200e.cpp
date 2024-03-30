/*CN*/
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5;
int n, nxt[N];
string a, ans;
void kmp(string a) {
    int len = a.size(), j = 0;
    a = ' ' + a;
    nxt[0] = nxt[1] = 0;
    for (int i = 2; i <= len; i++) {
        while (j > 0 && a[i] != a[j + 1]) {
            j = nxt[j];
        }
        if (a[i] == a[j + 1]) {
            j++;
        }
        nxt[i] = j;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> ans;
    for (int i = 2; i <= n; i++) {
        cin >> a;
        int l = min(a.size(), ans.size());
        string xt = a + ans.substr(ans.size() - l, l);
        kmp(xt);
        int j = nxt[xt.size()];
        while (j > l) j = nxt[j];
        for (; j < a.size(); j++) {
            ans += a[j];
        }
    }
    cout << ans;
    return 0;
}

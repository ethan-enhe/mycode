#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e5 + 5;
int n;
bool f[MXN], g[MXN], cnt[MXN];
char str[MXN];
int pre(int x) { return x == 1 ? n : x - 1; }
int suf(int x) { return x == n ? 1 : x + 1; }
void mod(int i, bool tp = 1) {
    f[i] ^= tp;
    f[pre(i)] ^= tp;
    f[suf(i)] ^= tp;
}
bool chk(bool x, bool y) {
    copy(g + 1, g + 1 + n, f + 1);
    mod(n, cnt[n] = x);
    mod(1, cnt[1] = y);
    for (int i = 2; i < n; i++) mod(i, cnt[i] = (f[i - 1] ^ 1));
    return (f[n] == 1 && f[n - 1] == 1);
}
queue<int> q;
void solve() {
    cin >> n >> (str + 1);
    for (int i = 1; i <= n; i++) g[i] = f[i] = str[i] - '0';
    for (int x = 0; x < 2; x++)
        for (int y = 0; y < 2; y++)
            if (chk(x, y)) {
                vector<int> ans;
                copy(g + 1, g + 1 + n, f + 1);
                for (int i = 1; i <= n; i++) {
                    // cout << cnt[i];
                    if (cnt[i] && !f[i]) q.push(i);
                }
                while (!q.empty()) {
                    int p = q.front();
                    q.pop();
                    if (f[p] || !cnt[p]) continue;
                    // cerr << p << endl;
                    ans.push_back(p);
                    mod(p);
                    cnt[p] = 0;
                    q.push(pre(p));
                    q.push(suf(p));
                }
                for (int i = 1; i <= n; i++)
                    if (cnt[i] && !cnt[pre(i)] && !f[pre(i)]) q.push(i);
                while (!q.empty()) {
                    int p = q.front();
                    q.pop();
                    if (!cnt[p] || cnt[pre(p)] || f[pre(p)]) continue;
                    // cerr << p << endl;
                    ans.push_back(pre(p));
                    ans.push_back(p);
                    ans.push_back(suf(p));
                    ans.push_back(pre(p));
                    mod(pre(p));
                    mod(p);
                    mod(suf(p));
                    mod(pre(p));
                    cnt[p] = cnt[suf(p)] = 0;
                    q.push(pre(pre(pre(p))));
                    q.push(suf(suf(suf(p))));
                }

                cout << ans.size() << '\n';
                for (int i = 0; i < ans.size(); i++) cout << ans[i] << (" \n"[i + 1 == ans.size()]);
                return;
            }
    cout << 0 << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int task;
    cin >> task;
    while (task--) solve();
    return 0;
}

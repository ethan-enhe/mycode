#include <bits/stdc++.h>
using namespace std;
const int MXN = 1000;
map<string, int> g[MXN];
int nodec;
int sz[MXN], sum[MXN], fa[MXN];
void ins(string x, bool f) {
    int p = 0;
    while (!x.empty()) {
        int ind = 0;
        while (ind < x.size() && x[ind] != '/') ++ind;
        string cur = x.substr(0, ind);
        if (!g[p][cur]) {
            g[p][cur] = ++nodec;
            sum[nodec] = 0;
            sz[nodec] = 0;
            fa[nodec] = p;
        }
        p = g[p][cur];
        ++sz[p];
        sum[p] += f;
        if (ind < x.size() && x[ind] == '/') ++ind;
        x = x.substr(ind, x.size() - ind);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        sz[0] = 1e9;
        sum[0] = -1e9;
        int n, m;
        cin >> n >> m;
        while (n--) {
            string tmp;
            cin >> tmp;
            ins(tmp, 1);
        }
        while (m--) {
            string tmp;
            cin >> tmp;
            ins(tmp, 0);
        }
        int ans = 0;
        for (int i = 0; i <= nodec; i++)
            if (sz[i] == sum[i] && sz[fa[i]] != sum[fa[i]]) ++ans;
        cout << ans << '\n';
        for (int i = 0; i <= nodec; i++) g[i].clear();
        nodec = 0;
    }

    return 0;
}

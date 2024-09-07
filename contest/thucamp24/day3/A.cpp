#include <bits/stdc++.h>

#include <iterator>
using namespace std;
const int MXN = 2e5 + 5;
int n, q;
vector<int> g[MXN];
vector<int> idx[MXN];
bool a[MXN];
int t[MXN], d[MXN], c[MXN];

int mnsuf[MXN];

int getpre(int i, int v) {
    auto it = lower_bound(idx[v].begin(), idx[v].end(), i);
    if (it == idx[v].begin()) return 0;
    return *prev(it);
}

int stk[MXN], top;
bool dfschk(int p) {
    bool f = 1;
    stk[++top] = p;
    if (top != 1) {
        int jmp = stk[max(1, top - d[p])];
        mnsuf[p] = getpre(mnsuf[jmp], t[p]);
        if (a[p] && mnsuf[p] == 0) f = 0;
    }
    for (int nx : g[p]) {
        f &= dfschk(nx);
    }
    --top;
    return f;
}

bool chk(int pre) {
    mnsuf[1] = pre + 1;
    return dfschk(1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        g[f].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) {
        cin >> c[i];
        idx[c[i]].push_back(i);
    }
    int l = 1, r = q + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (chk(mid))
            r = mid;
        else
            l = mid + 1;
    }
    if (l == q + 1)
        cout << "-1";
    else
        cout << l;

    return 0;
}

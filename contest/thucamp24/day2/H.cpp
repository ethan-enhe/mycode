#include <bits/stdc++.h>

#include <stack>

using namespace std;
const int MXN = 2005;
const int NR = MXN * 2;
vector<int> g[MXN];
int n, limd;

int mx[NR];
stack<int> hist;
stack<int> tmp;
void upd(int x, int y) {
    x += MXN;
    for (; x < NR; x += x & -x) {
        tmp.push(mx[x]);
        mx[x] = max(mx[x], y);
    }
    while (!tmp.empty()) {
        hist.push(tmp.top());
        tmp.pop();
    }
}
void undo(int x) {
    x += MXN;
    for (; x < NR; x += x & -x) {
        mx[x] = hist.top();
        hist.pop();
    }
}
int premx(int x) {
    x += MXN;
    x = max(x, 0);
    int ret = -1e9;
    for (; x; x -= x & -x) {
        ret = max(ret, mx[x]);
    }
    return ret;
}
int h[MXN], d[MXN];
template <int* v>
struct mx3 {
    int mx[3];
    mx3() { mx[0] = mx[1] = mx[2] = 0; }
    void ins(int x) {
        if (v[x] > v[mx[2]]) {
            mx[2] = x;
            if (v[mx[2]] > v[mx[1]]) {
                swap(mx[2], mx[1]);
                if (v[mx[1]] > v[mx[0]]) swap(mx[1], mx[0]);
            }
        }
    }
    pair<int, int> top2_except(int x) {
        if (mx[0] == x) return {mx[1], mx[2]};
        if (mx[1] == x) return {mx[0], mx[2]};
        return {mx[0], mx[1]};
    }
};

void dfs1(int p, int fa) {
    h[p] = 0;
    d[p] = 0;
    for (auto v : g[p]) {
        if (v == fa) continue;
        dfs1(v, p);
        d[p] = max({d[p], d[v], h[p] + h[v] + 1});
        h[p] = max(h[p], h[v] + 1);
    }
}
int ans, rt;
void dfs2(int p, int fa, int dep, int mxdep) {
    if (dep > mxdep) return;
    if (p >= rt && d[p] <= limd && premx(dep + h[p] - limd - 1) + h[p] <= limd) {
        ++ans;
        // cerr << p << " " << rt << endl;
    }

    // 要计算除了枚举的子树以外，其余子树的最大深度，&内部的最大直径
    mx3<h> mxh;
    mx3<d> mxd;
    for (auto v : g[p]) {
        if (v == fa) continue;
        mxh.ins(v);
        mxd.ins(v);
    }
    for (auto v : g[p]) {
        if (v == fa) continue;
        if (d[mxd.top2_except(v).first] > limd) continue;
        auto t = mxh.top2_except(v);
        if (h[t.first] + h[t.second] + 2 > limd) continue;

        int sideh = h[t.first] + 1; // 旁生子树的最大深度

        int cannnot_reach = dep + sideh - limd - 1;
        int res = premx(cannnot_reach);
        upd(dep - sideh, dep + sideh);
        dfs2(v, p, dep + 1, min(mxdep, limd - res - sideh + dep));
        undo(dep - sideh);
    }
}

void solve(int p) {
    // if (h[0] != -1) cout << "!!!" << endl;
    rt = p;
    dfs1(p, 0);
    dfs2(p, 0, 0, 1e9);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(mx, ~0x3f, sizeof(mx));

    h[0] = -1;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        ++fa;
        g[fa].push_back(i);
        g[i].push_back(fa);
    }
    cin >> limd;
    // solve(3);
    for (int i = 1; i <= n; i++) {
        solve(i);
    }
    cout << ans;
    return 0;
}

#include <bits/stdc++.h>

#include <vector>

using namespace std;
const int MXN = 1e6 + 5;
const char nl = '\n';
const int INF = 1e9;

int n, cur_i;
char str[MXN];
set<int> remain;
vector<int> pos[MXN];

int delta[MXN];
void mdf(int x, int y) {
    for (; x <= n; x += x & (-x)) delta[x] += y;
}
int pre(int x) {
    int r = 0;
    for (; x; x -= x & (-x)) r += delta[x];
    return r;
}

int trnsfrm(int x) { // 原来的位置转化为新的位置
    return x + pre(x);
}

void del(int i, int len) {
    mdf(i, -len);
    int bitmask = (1 << len) - 1;
    auto itl = remain.lower_bound(i);
    auto itr = itl;
    auto itll = itl;

    for (int i = 1; i < len; i++) {
        if (next(itr) != remain.end()) ++itr;
        if (itll != remain.begin()) --itll;
    }
    ++itr;
    // itl-itr-1之间要删

    // 删除原来的
    int va = 0, cnt = 0;
    auto slow = itll;
    auto itrr = itll;
    for (; itrr != remain.end() && slow != itr; ++itrr) {
        ++cnt;
        va = (va << 1 | str[*itrr]) & bitmask;
        if (cnt >= len) {
            if (va <= n && va >= cur_i) pos[va].push_back(-*slow);
            ++slow;
        }
    }
    int lid = *itll, rid = itrr == remain.end() ? INF : *itrr;
    va = 0, cnt = 0;

    remain.erase(itl, itr);
    auto newrr = remain.lower_bound(lid);
    slow = newrr;
    for (; newrr != remain.end() && *newrr < rid; newrr++) {
        ++cnt;
        va = (va << 1 | str[*newrr]) & bitmask;
        if (cnt >= len) {
            if (va <= n && va >= cur_i) pos[va].push_back(*slow);
            ++slow;
        }
    }
}
int _cnt[MXN];

void solve(int len, int l, int r) {
    int bitmask = (1 << len) - 1;
    int va = 0, cnt = 0;
    auto slow = remain.begin();
    for (auto u : remain) {
        ++cnt;
        va = (va << 1 | str[u]) & bitmask;
        if (cnt >= len) {
            if (va <= n && va >= cur_i) pos[va].push_back(*slow);
            ++slow;
        }
    }

    for (; cur_i <= r; cur_i++) {
        for (auto &i : pos[cur_i]) {
            _cnt[(int)abs(i)] += i > 0 ? 1 : -1;
        }
        int ans = INF, sz = 0;
        for (auto &i : pos[cur_i]) {
            if (i < 0) i = -i;
            if (_cnt[i]) {
                ans = min(ans, i);
                ++sz;
            }
            _cnt[i] = 0;
        }
        if (sz) {
            cout << trnsfrm(ans) << " " << sz << nl;
            del(ans, len);
            pos[cur_i].clear();
        } else
            cout << "-1 0" << nl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    cin >> (str + 1);
    for (int i = 1; i <= n; i++) {
        str[i] -= '0';
        remain.insert(i);
    }
    int l = 1;
    cur_i = 1;
    for (int w = 1; l <= n; l <<= 1, w++) {
        solve(w, l, min(l * 2 - 1, n));
    }
    return 0;
}

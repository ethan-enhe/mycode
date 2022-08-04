// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstdlib>
#include <cstring>
#include <vector>
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
#define NDEBUG
#endif
#include <bits/stdc++.h>

using namespace std;
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())

struct vec {
    int x, y, z;
    vec operator+(const vec &b) const { return {x + b.x, y + b.y, z + b.z}; }
    bool operator<(const vec &b) const {
        if (x == b.x) {
            if (y == b.y) return z < b.z;
            return y < b.y;
        }
        return x < b.x;
    }
    bool operator==(const vec &b) const { return x == b.x && y == b.y && z == b.z; }
    void prt() { cout << "{" << x << "," << y << "," << z << "}"; }
};
using b = vector<vec>;
using bs = vector<b>;
vector<vector<b>> arr = {
    {{{0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {1, 1, 0}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}}},
    {{{0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1}, {0, 0, 2}}},
    {{{0, 0, 0}, {0, 1, 0}, {0, 2, 0}, {1, 2, 0}, {0, 0, 1}}},
    {{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0}, {0, 2, 0}, {0, 0, 1}, {0, 1, 1}}},
    {{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 2, 0}, {0, 1, 1}, {0, 1, 2}}},
    {{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 1, 1}}},
    {{{0, 0, 0}, {0, 1, 0}, {0, 0, 1}}},
    {{{0, 0, 0}, {0, 0, 1}}},
    {{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0}, {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1}}},
    {{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0}, {0, 0, 1}, {1, 0, 1}, {0, 1, 1}}},
    {{{0, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 1, 1}, {0, 0, 2}, {0, 1, 2}}},
    {{{0, 0, 0}, {0, 0, 1}, {0, 0, 2}}},
    {{{0, 0, 0}}},
};
/*
 * 123 23
 * 132 12
 * 312 23
 * 321 12
 * 231 23
 * 213 12
 */

void expand(bs &sides) {
    auto add = [&](b curb) {
        b nxb = curb;
        for (int xo = -1; xo <= 1; xo += 2)
            for (int yo = -1; yo <= 1; yo += 2)
                for (int zo = -1; zo <= 1; zo += 2) {
                    for (int i = 0; i < curb.size(); i++) nxb[i] = {curb[i].x * xo, curb[i].y * yo, curb[i].z * zo};
                    sort(all(nxb));
                    sides.push_back(nxb);
                }
    };
    while (1) {
        int lsz = sides.size();
        for (int i = 0; i < lsz; i++) {
            b tmp = sides[i];
            for (int j = 0; j < 3; j++) {
                for (vec &k : tmp) swap(k.y, k.z);
                add(tmp);
                for (vec &k : tmp) swap(k.x, k.y);
                add(tmp);
            }
        }
        sort(all(sides));
        unq(sides);
        if (sides.size() == lsz) break;
    }
}
b all;
char vis[10][10][10];
bool used[20];
bool valid(const vec &x) { return x.x > 0 && x.x <= 4 && x.y > 0 && x.y <= 4 && x.z > 0 && x.z <= 4; }
char &getvis(const vec &x) { return vis[x.x][x.y][x.z]; }
vector<string> ans;
void dfs(int ind, int cnt) {
    if (all.size() - ind < 13 - cnt) return;
    if (ind == all.size()) {
        if (cnt == 13) {
            string cur;
            for (int i = 1; i <= 4; i++)
                for (int j = 1; j <= 4; j++) {
                    for (int k = 1; k <= 4; k++) cur += vis[i][j][k];
                    cur += '\n';
                }
            ans.emplace_back(cur);
        }
        return;
    }
    if (getvis(all[ind]) == '.')
        for (int id = 0; id < arr.size(); id++)
            if (!used[id]) {
                for (auto &side : arr[id]) {
                    bool f = 1;
                    for (auto &delt : side)
                        if (!valid(all[ind] + delt) || getvis(all[ind] + delt) != '.') {
                            f = 0;
                            break;
                        }
                    if (!f) continue;
                    used[id] = 1;
                    for (auto &delt : side) getvis(all[ind] + delt) = 'A' + id;
                    dfs(ind + 1, cnt + 1);
                    used[id] = 0;
                    for (auto &delt : side) getvis(all[ind] + delt) = '.';
                }
            }
    dfs(ind + 1, cnt);
}

int main() {
    //字典序！！！
    //剪枝！！！
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (auto &i : arr) {
        for (auto &j : i) sort(all(j));
        expand(i);
        /* cout << i.size() << endl; */
    }
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            for (int k = 1; k <= 4; k++) all.push_back({i, j, k});
    sort(all(all), [](vec x, vec y) {
        int c1 = 0, c2 = 0;
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                for (int k = -1; k <= 1; k++) {
                    c1 += valid(x + vec{i, j, k});
                    c2 += valid(y + vec{i, j, k});
                }
        return c1 < c2;
    });
    /* for (int i = 0; i < 64; i++) all[i].prt(); */
    int t;
    cin >> t;
    while (t--) {
        int cnt = 0;
        memset(used, 0, sizeof(used));
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++) {
                cin >> (vis[i][j] + 1);
                for (int k = 1; k <= 4; k++)
                    if (vis[i][j][k] != '.' && used[vis[i][j][k] - 'A'] == 0) {
                        ++cnt;
                        used[vis[i][j][k] - 'A'] = 1;
                    }
            }
        dfs(0, cnt);
        sort(all(ans));
        unq(ans);
        cout << ans.size() << '\n';
        for (string &x : ans) cout << x << '\n';
    }

    return 0;
}

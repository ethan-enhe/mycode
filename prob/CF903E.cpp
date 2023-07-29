#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
const char nl = '\n';
const int MXK = 2505;
const int MXN = 5005;
const int SZ = 6250009;
const ull B = 203;

int n, m;
char arr[MXK][MXN];
ull pw[MXN];
unordered_set<ull> app;

struct hash_map { // 哈希表模板

    struct data {
        ull u;
        int v, nex;
    }; // 前向星结构

    data e[SZ << 1]; // SZ 是 const int 表示大小
    int h[SZ], cnt;

    int hash(ull u) { return (u % SZ + SZ) % SZ; }

    // 这里使用 (u % SZ + SZ) % SZ 而非 u % SZ 的原因是
    // C++ 中的 % 运算无法将负数转为正数

    int& operator[](ull u) {
        int hu = hash(u); // 获取头指针
        for (int i = h[hu]; i; i = e[i].nex)
            if (e[i].u == u) return e[i].v;
        return e[++cnt] = (data){u, -1, h[hu]}, h[hu] = cnt, e[cnt].v;
    }

    hash_map() {
        cnt = 0;
        memset(h, 0, sizeof(h));
    }
} cnt;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    if (n == 1) {
        cin >> (arr[1] + 1);
        swap(arr[1][1], arr[1][2]);
        cout << (arr[1] + 1);
        return 0;
    }
    pw[0] = 1;
    for (int i = 1; i <= m; i++) pw[i] = pw[i - 1] * B;
    int last = 0;
    for (int i = 1; i <= n; i++) {
        cin >> (arr[i] + 1);
        ull h = 0;
        for (int j = 1; j <= m; j++) h = h * B + arr[i][j];
        if (app.count(h)) continue;
        app.insert(h);
        for (int j = 1; j <= m; j++) {
            for (int k = j + 1; k <= m; k++) {
                ull th = h + ((ull)arr[i][j] - (ull)arr[i][k]) * (pw[m - k] - pw[m - j]);
                // cerr << th << endl;
                if (i == 1)
                    cnt[th] = 1;
                else {
                    auto& v = cnt[th];
                    if (v >= last) v = i;
                }
            }
        }
        last = i;
    }
    ull h = 0;
    for (int j = 1; j <= m; j++) h = h * B + arr[1][j];
    for (int j = 1; j <= m; j++) {
        for (int k = j + 1; k <= m; k++) {
            ull th = h + ((ull)arr[1][j] - (ull)arr[1][k]) * (pw[m - k] - pw[m - j]);
            if (cnt[th] >= last) {
                swap(arr[1][j], arr[1][k]);
                cout << (arr[1] + 1);
                return 0;
            }
        }
    }
    cout << "-1";
    return 0;
}

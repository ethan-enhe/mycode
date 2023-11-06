
#include <bits/stdc++.h>

using namespace std;
#define vec vector
#define endl '\n'
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

struct mll;
typedef vec<int> vi;
typedef vec<vi> vvi;
const int P(1e9 + 9);
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + (x >> 31 & P); }
inline void add(int &x, const int &y) { x = redu(x + y); }
inline void del(int &x, const int &y) { x = incr(x - y); }
inline void fwt(vi &x, int n) {
    for (int w = 1; w < n; w <<= 1) {
        add(x[w], x[0]);
        for (int mask = (n - 1) ^ w, i = mask; i; i = (i - 1) & mask) add(x[i ^ w], x[i]);
    }
}
inline void ifwt(vi &x, int n) {
    for (int w = 1; w < n; w <<= 1) {
        del(x[w], x[0]);
        for (int mask = (n - 1) ^ w, i = mask; i; i = (i - 1) & mask) del(x[i ^ w], x[i]);
    }
}
// 多项式复合 res_i=\sum f_j \sum _{k_1到k_j并集为i，两两交为空，且 k_i<k_{i+1}}\prod_{l\in[1,j]}a_{k_l}
vi subset_conv(const vi &a, const vi &b) {
    int n = max(a.size(), b.size()), h = log2(n);
    vvi a_group(h + 1, vi(n)), b_group(h + 1, vi(n));
    vi tmp(n), c(n);
    for (int i = 0; i <= h; i++)
        for (int j = 0; j < n; j++) a_group[i][j] = b_group[i][j] = 0;
    for (int i = 0; i < a.size(); i++) a_group[popc(i)][i] = a[i];
    for (int i = 0; i < b.size(); i++) b_group[popc(i)][i] = b[i];
    for (int i = 0; i <= h; i++) fwt(a_group[i], n), fwt(b_group[i], n);
    for (int sz = 0; sz <= h; sz++) {       // 最终集合大小
        for (int asz = 0; asz <= sz; asz++) // a 对应集合大小
            for (int k = 0; k < n; k++) tmp[k] = (1ll * a_group[asz][k] * b_group[sz - asz][k] + tmp[k]) % P;
        ifwt(tmp, n);
        for (int i = 0; i < n; i++) {
            if (popc(i) == sz) c[i] = tmp[i];
            tmp[i] = 0;
        }
    }
    return c;
}
vi add(vi a, vi b) {
    if (a.size() < b.size()) swap(a, b);
    vi c(a);
    for (int i = 0; i < b.size(); i++) add(c[i], b[i]);
    return c;
}
vi magic(vi a, vi f) {
    int h = f.size() - 1, n = a.size();
    assert(n == 1 << h);
    vec<vvi> g(h + 1);
    vi a_group;
    g[0].resize(h + 1);
    for (int i = 0; i <= h; i++) g[0][i] = {f[i], 0};
    for (int i = 1, w = 2; i <= h; i++, w <<= 1) {
        g[i].resize(h + 1 - i);
        a_group.resize(w);
        for (int j = 0; j < w; j++) a_group[j] = j >= (w >> 1) ? a[j] : 0;
        for (int j = 0; j <= (h - i); j++) g[i][j] = add(g[i - 1][j], subset_conv(g[i - 1][j + 1], a_group));
        g[i - 1].clear();
    }
    return g[h][0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, m, k;
    cin >> n;
    n = 1 << n;
    vi a(n), b(n), res;
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;
    res = subset_conv(a, b);
    for (int &i : res) cout << i << " ";

    return cout.flush(), 0;
}

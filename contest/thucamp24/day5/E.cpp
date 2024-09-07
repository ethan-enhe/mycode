#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4e5 + 5;
const int LG = 21;
int t, n, len;
char str[MAXN];
int sa[MAXN], sa1[MAXN], rk[MAXN << 1], rk1[MAXN << 1], cnt[MAXN], hgt[MAXN];
int st[LG][MAXN];
int getrk(int w) {
    rk1[sa[1]] = 1;
    for (int i = 2; i <= len; i++)
        rk1[sa[i]] = rk1[sa[i - 1]] + (rk[sa[i]] != rk[sa[i - 1]] || rk[sa[i] + w] != rk[sa[i - 1] + w]);
    memcpy(rk + 1, rk1 + 1, sizeof(int) * len);
    return rk[sa[len]];
}
void getsa() {
    int mxr = 130;
    memset(cnt, 0, sizeof(int) * (mxr + 1));
    memset(rk, 0, sizeof(int) * (2 * len + 2));
    for (int i = 1; i <= len; i++) cnt[rk[i] = str[i]]++;
    for (int i = 1; i <= mxr; i++) cnt[i] += cnt[i - 1];
    for (int i = 1; i <= len; i++) sa[cnt[rk[i]]--] = i;
    getrk(0);
    for (int w = 1; w <= len; w <<= 1) {
        int tmp = 0;
        for (int i = len - w + 1; i <= len; i++) sa1[++tmp] = i;
        for (int i = 1; i <= len; i++)
            if (sa[i] > w) sa1[++tmp] = sa[i] - w;
        memset(cnt, 0, sizeof(int) * (mxr + 1));
        for (int i = 1; i <= len; i++) cnt[rk[sa1[i]]]++;
        for (int i = 1; i <= mxr; i++) cnt[i] += cnt[i - 1];
        for (int i = len; i >= 1; i--) sa[cnt[rk[sa1[i]]]--] = sa1[i];
        if ((mxr = getrk(w)) == len) break;
    }
    int p = 0;
    for (int i = 1; i <= len; i++) {
        p = max(p - 1, 0);
        if (rk[i] == 1) continue;
        int pr = sa[rk[i] - 1];
        while (i + p <= len && pr + p <= len && str[i + p] == str[pr + p]) p++;
        hgt[rk[i]] = p;
    }
    for (int i = 1; i <= len; i++) st[0][i] = hgt[i];
    for (int j = 1; j < LG; j++) {
        for (int i = 1; i + (1 << j) - 1 <= len; i++) {
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
}
#define fi first
#define se second
using pi = pair<int, int>;
int getlcp(int u, int v) {
    if (u == v) return 1e9;
    u = rk[u], v = rk[v];
    if (u > v) swap(u, v);
    int lg = 31 - __builtin_clz(v - u);
    return min(st[lg][u + 1], st[lg][v - (1 << lg) + 1]);
}
int getlcp(pi r1, pi r2) {
    int lcp = getlcp(r1.first, r2.first);
    return min({lcp, r1.second - r1.first + 1, r2.second - r2.first + 1});
}
int cmp(pi r1, pi r2) {
    int lcp = getlcp(r1.first, r2.first);
    if (r1.fi + lcp > r1.se || r2.fi + lcp > r2.se) {
        return r1.se - r1.fi < r2.se - r2.fi;
    } else {
        return str[r1.fi + lcp] < str[r2.fi + lcp];
    }
}

bool tp[MAXN]; // 0 pre,1 reversed pre
int newsa[MAXN], newh[MAXN], top;

pi genr(int i, bool f) {
    if (f)
        return {len - i + 1, len};
    else
        return {1, i};
}
using ll = long long;
const ll P = 998244353;
ll p[MAXN];

// 并查集
ll fa[MAXN];                               // 向右合并，存左侧范围
ll lrng[MAXN], multp[MAXN], lastlen[MAXN]; // 上次合并的长度

ll mxl[MAXN]; // 最大的l,使得包含一对前缀
ll last[MAXN];

vector<ll> pool[MAXN];

ll find(ll x) {
    while (x != fa[x]) x = fa[x] = fa[fa[x]];
    return x;
}
ll ans = 0;
void mrg(ll x, ll y, ll curlen) {
    x = find(x), y = find(y);
    if (x > y) swap(x, y);
    // x 拉到当前长度
    ans = (ans + (1 + P - multp[x]) % P * (lastlen[x] - curlen)) % P;
    // y 拉到当前长度
    ans = (ans + (1 + P - multp[y]) % P * (lastlen[y] - curlen)) % P;
    lrng[y] = lrng[x];
    multp[y] = lrng[y] <= mxl[y] ? 0 : multp[x] * multp[y] % P;
    lastlen[y] = curlen;
    fa[x] = y;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    len = n * 2 + 1;
    cin >> (str + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> p[i];
    }
    str[n + 1] = '#';
    for (int i = n; i; i--) {
        str[n + 2 + (n - i)] = str[i];
    }
    str[len + 1] = 0;
    getsa();
    cerr << (str + 1) << endl;
    for (int i = 1; i <= len; i++) {
        cerr << sa[i] << endl;
    }
    int idx = 1;
    for (int i = 1; i <= len; i++) {
        if (sa[i] > n + 1) {
            while (idx <= n && cmp(genr(idx, 0), {sa[i], len})) {
                ++top;
                tp[top] = 0;
                newsa[top] = idx;
                ++idx;
            }
            ++top;
            tp[top] = 1;
            newsa[top] = len - sa[i] + 1;
        }
    }
    while (idx <= n) {
        ++top;
        tp[top] = 0;
        newsa[top] = idx;
        ++idx;
    }
    for (int i = 1; i <= top; i++) {
        if (i > 1) newh[i] = getlcp(genr(newsa[i - 1], tp[i - 1]), genr(newsa[i], tp[i]));

        mxl[i] = mxl[i - 1];
        if (last[newsa[i]]) mxl[i] = max(mxl[i], last[newsa[i]]);
        last[newsa[i]] = i;

        lastlen[i] = newsa[i];
        multp[i] = tp[i] ? p[newsa[i]] : (1 + P - p[newsa[i]]) % P; // 对吗？
        lrng[i] = i;
        fa[i] = i;

        pool[newh[i]].push_back(i);
        cerr << newsa[i] << " " << tp[i] << " " << newh[i] << " " << mxl[i] << endl;
    }

    for (ll i = n; ~i; i--) {
        for (auto j : pool[i]) {
            mrg(j, j - 1, i);
        }
    }
    cout << (ans + 1) % P << endl;
    return 0;
}

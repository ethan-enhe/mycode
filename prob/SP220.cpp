#include <bits/stdc++.h>
using namespace std;
template <typename T>
void umx(T &x, const T &y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, const T &y) {
    x = min(x, y);
}
const char nl = '\n';
const int S = 1e6 + 5, N = 11;
int cnt[S], _sa[S], sa[S], _rk[S], rk[S], h[S];
void csa(int n, int m, int *arr) {
    copy(arr, arr + 1 + n, rk);
#define rdx(x)                                 \
    fill(cnt, cnt + 1 + m, 0);                 \
    for (int i = 1; i <= n; i++) cnt[rk[i]]++; \
    partial_sum(cnt, cnt + 1 + m, cnt);        \
    for (int i = n; i; i--) sa[cnt[rk[x]]--] = x;
    rdx(i);
    for (int w = 1; w <= n; w <<= 1) {
        int ind = 0;
        for (int i = n - w + 1; i <= n; i++) _sa[++ind] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w) _sa[++ind] = sa[i] - w;
        rdx(_sa[i]);
        copy(rk, rk + 1 + n, _rk);
        auto cmp = [&](int x, int y) {
            return _rk[x] == _rk[y] && ((x + w > n && y + w > n) || _rk[x + w] == _rk[y + w]);
        };
        m = 0;
        for (int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1]) ? m : ++m;
    }
}
void ch(int n, int *arr) {
    arr[n + 1] = -1;
    arr[0] = -2;
    for (int i = 1, lcp = 0; i <= n; i++) {
        lcp -= !!lcp;
        while (arr[i + lcp] == arr[sa[rk[i] - 1] + lcp]) ++lcp;
        h[rk[i]] = lcp;
    }
}
int arr[S], id[S];
char str[S];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int task;
    cin >> task;
    while (task--) {
        int t, n = 0;
        cin >> t;
        for (int i = 1; i <= t; i++) {
            cin >> str;
            for (int j = 0, _ = strlen(str); j < _; ++j) {
                ++n;
                arr[n] = str[j] - 'a';
                id[n] = i;
            }
            ++n;
            arr[n] = 30 + i;
            id[n] = 0;
        }
        csa(n, 100, arr);
        ch(n, arr);
        int mx[N], mn[N], tag[N];
        auto chk = [&](int x) -> bool {
            memset(tag, 0, sizeof(tag));
            int cnt = 0, time = 1;
            for (int l = 1; l <= n; l++) {
                int i = sa[l], si = id[i];
                if (h[l] < x) ++time, cnt = 0;
                if (tag[si] != time)
                    tag[si] = time, mn[si] = mx[si] = i;
                else if (mx[si] - mn[si] < x) {
                    umn(mn[si], i), umx(mx[si], i);
                    if (mx[si] - mn[si] >= x)
                        if (++cnt == t) return 1;
                }
            }
            return 0;
        };
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (chk(mid))
                l = mid;
            else
                r = mid - 1;
        }
        cout << l << nl;
    }
    return 0;
}

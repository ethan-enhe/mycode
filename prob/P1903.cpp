// File:             P1903.cpp
// Author:           ethan
// Created:          01/01/22
// Description:      高维莫队
#include <bits/stdc++.h>
#define inr(x, l, r) ((l) <= (x) && (x) <= (r))
using namespace std;
const int MXN = 1.4e5, MXC = 1e6 + 5, INF = 1e9;
int n, m, q, B, arr[MXN], ans[MXN];
struct que {int i, l, r, t;} qrr[MXN];
struct mod {int i, u, v;} mrr[MXN];
#define rcmp(expr) \
    if (x.expr != y.expr) return x.expr < y.expr
bool cmp(const que &x, const que &y) {
    rcmp(l / B);
    rcmp(r / B);
    return x.t < y.t;
}
int cnt[MXC], tot;
void trans(int x, int y) {
    tot += !(cnt[y]++);
    tot -= !(--cnt[x]);
}
int main() {
    int tm;
    scanf("%d%d", &n, &tm);
    B = ceil(exp(log(n * 2) * 2 / 3));
    for (int i = 1; i <= n; i++) scanf("%d", arr + i);
    while (tm--) {
        char op;
        int x, y;
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'Q') {
            ++q;
            qrr[q] = {q, x, y, m};
        } else {
            mrr[++m] = {x, arr[x], y};
            arr[x] = y;
        }
    }
    for (int i = m; i; i--) arr[mrr[i].i] = mrr[i].u;
    sort(qrr + 1, qrr + 1 + q, cmp);
    cnt[0] = INF;
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= q; i++) {
        while (r < qrr[i].r) trans(0, arr[++r]);
        while (l > qrr[i].l) trans(0, arr[--l]);
        while (r > qrr[i].r) trans(arr[r--], 0);
        while (l < qrr[i].l) trans(arr[l++], 0);
        while (t < qrr[i].t) {
            ++t;
            if (inr(mrr[t].i, l, r)) trans(mrr[t].u, mrr[t].v);
            arr[mrr[t].i] = mrr[t].v;
        }
        while (t > qrr[i].t) {
            if (inr(mrr[t].i, l, r)) trans(mrr[t].v, mrr[t].u);
            arr[mrr[t].i] = mrr[t].u;
            --t;
        }
        ans[qrr[i].i] = tot;
    }
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}

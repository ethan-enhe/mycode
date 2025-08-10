#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<bool, ll>;
const int LG = 8;
const int MXN = 2e5 + 5;
const int NR = 1e6 + 5;
struct node {
    pi sum[LG];
    int mn;
} t[MXN << 2];
#define ls p << 1
#define rs p << 1 | 1
inline pi operator+(const pi &a, const pi &b) {
    return {a.first ^ b.first, a.second + (a.first ? -b.second : b.second)};
}
void pull(int p) {
    t[p].mn = min(t[ls].mn, t[rs].mn);
#define mrg(i) t[p].sum[i] = t[ls].sum[i] + t[rs].sum[i]
    mrg(0);
    mrg(1);
    mrg(2);
    mrg(3);
    mrg(4);
    mrg(5);
    mrg(6);
    mrg(7);
}

int n, m;
int arr[MXN], pcnt[MXN];

int mnp[NR], pri[NR], top;
void seive() {
    mnp[1] = 1;
    for (int i = 2; i < NR; i++) {
        if (!mnp[i]) {
            pri[++top] = i;
            mnp[i] = i;
        }
        for (int j = 1; j <= top && i * pri[j] < NR; j++) {
            mnp[i * pri[j]] = pri[j];
            if (i % pri[j] == 0) break;
        }
    }
}

void mult(int &x, int &y, int t, bool clr = 0) {
    if (clr) x = 1, y = 0;
    while (t > 1) {
        int p = mnp[t];
        if (p == 0) cout << t << endl;
        if (x % p) ++y;
        t /= p;
        x *= p;
    }
}
void mdf(int p, int i, int v, bool clr = 0) {
    mult(arr[i], pcnt[i], v, clr);
    t[p].mn = arr[i];
    for (int j = 0; j < LG; j++) t[p].sum[j] = pcnt[i] <= j ? pi{1, arr[i]} : pi{0, 0};
}

void setv(int p, int l, int r, int mi, int mv) {
    if (l == r) {
        mdf(p, mi, mv, 1);
        return;
    }
    int m = (l + r) >> 1;
    if (mi <= m)
        setv(ls, l, m, mi, mv);
    else
        setv(rs, m + 1, r, mi, mv);
    pull(p);
}

void multv(int p, int l, int r, int ml, int mr, int mv, int mb) {
    if (l > mr || r < ml || t[p].mn > mb) return;
    if (l == r) {
        mdf(p, l, mv);
        return;
    }
    int m = (l + r) >> 1;
    multv(ls, l, m, ml, mr, mv, mb);
    multv(rs, m + 1, r, ml, mr, mv, mb);
    pull(p);
}
pi qry(int p, int l, int r, int ql, int qr, int qk) {
    if (l > qr || r < ql) return pi{0, 0};
    if (l >= ql && r <= qr) return t[p].sum[qk];
    int m = (l + r) >> 1;
    return qry(ls, l, m, ql, qr, qk) + qry(rs, m + 1, r, ql, qr, qk);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    seive();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        setv(1, 1, n, i, x);
    }
    while (m--) {
        int t, a, b, c, d;
        cin >> t >> a >> b;
        if (t == 2) {
            setv(1, 1, n, a, b);
        } else if (t == 1) {
            cin >> c;
            cout << qry(1, 1, n, a, b, min(LG - 1, c)).second << '\n';
        } else {
            cin >> c >> d;
            if (c > 1) multv(1, 1, n, a, b, c, d / c);
        }
    }

    return 0;
}

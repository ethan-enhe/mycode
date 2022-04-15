#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e5 + 5, INF = 1e9;

struct line {
    int b, k;
    double operator*(const line &f) const { return double(b - f.b) / (f.k - k); }
};

struct convex_hull {
    vector<line> q;
    int ql, qr;
    bool ismn;
    convex_hull(int sz, bool _ismn) {
        ismn = _ismn;
        q.resize(sz);
        if (ismn)
            ql = 0, qr = -1;
        else
            qr = sz - 1, ql = sz;
    }
    void ins(line f) {
        if (ismn) {
            while (ql < qr && q[qr - 1] * q[qr] >= q[qr] * f) --qr;
            q[++qr] = f;
        } else {
            while (ql < qr && q[ql + 1] * q[ql] <= q[ql] * f) ++ql;
            q[--ql] = f;
        }
    }
    double operator*(line f) const {
        int l = ql, r = qr;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (q[mid] * q[mid + 1] <= q[mid] * f)
                l = mid + 1;
            else
                r = mid;
        }
        return q[l] * f;
    }
};

int m, n, l[MXN], r[MXN], x[MXN];
int L = INF, R = -INF;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (i > 1) r[i - 1] = x;
        l[i] = x;
    }
    l[n] = m, r[n] = m;

    convex_hull mn(n + 1, 1), mx(n + 1, 0);
    for (int i = 0; i <= n; i++) {
        if (i) {
            R = max(R, (int)ceil(mn * line{l[i], -i}));
            L = min(L, (int)floor(mx * line{r[i], -i}));
        }
        mn.ins({r[i], -i});
        mx.ins({l[i], -i});
    }

    for (int i = 0; i < n; i++) x[i + 1] = max(l[i + 1], x[i] + L);
    for (int i = n; i; i--) x[i - 1] = max(x[i - 1], x[i] - R);
    for (int i = 1; i <= n; i++) cout << x[i - 1] << ' ' << x[i] << '\n';

    return 0;
}

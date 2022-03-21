#include "lib.h"

#include <bits/stdc++.h>

#define Fe(i, l, r) for (int i = l; i <= r; ++i)

static int cnt = 0;

Data operator+(Data x, Data y) {
    Data z;
    z.a = x.a * y.a;
    z.b = x.a * y.b + x.b;
    z.c = x.c + y.c;
    z.d = std::max(x.d, y.d);
    ++cnt;
    return z;
}

int main() {
    const int maxn = 1e5, maxm = 2e5;
    auto read = [](int L, int R) {
        int x;
        assert(scanf("%d", &x) == 1);
        assert(L <= x && x <= R);
        return x;
    };
    auto read_data = [&](Data &d) {
        d.a = read(1, 100);
        d.b = read(1, 100);
        d.c = read(1, 100);
        d.d = read(1, 100);
    };
    auto write_data = [](Data &d) { printf("%d %d %d %d\n", d.a, d.b, d.c, d.d); };
    int n = read(1, maxn);
    int m = read(1, maxm);
    int k = read(2, 9);
    int k1 = read(0, 100000);
    int m1 = 0, m2 = 0;
    init(n, k, Data{1, 0, 0, 0});
    Fe(i, 1, m) {
        int o = read(1, 2);
        cnt = 0;
        if (o == 1) {
            int x = read(1, n);
            Data d;
            read_data(d);
            update(x, d);
            m1 = std::max(m1, cnt);
        } else {
            int l = read(1, n), r = read(l, n);
            Data d = query(l, r);
            write_data(d);
            m2 = std::max(m2, cnt);
        }
    }
    fprintf(stderr, "n=%d cost=(%d %d)\n", n, m1, m2);
    if (m1 > k1 || m2 > k) fprintf(stderr, "too many operations!\n");
    return 0;
}

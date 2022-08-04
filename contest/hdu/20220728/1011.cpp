#include <bits/stdc++.h>

#include <cstdio>
#include <cstring>
using namespace std;
typedef unsigned long long ull;
struct _xor {
    static const int D = 63;
    ull m[D + 1];
    inline void insert(ull x) {
        for (int i = D; ~i; i--)
            if ((x >> i) & 1) {
                if (m[i])
                    x ^= m[i];
                else {
                    for (int j = i - 1; ~j; j--)
                        if ((x >> j) & 1) x ^= m[j];
                    for (int j = i + 1; j <= D; j++)
                        if ((m[j] >> i) & 1) m[j] ^= x;
                    m[i] = x;
                    return;
                }
            }
    }
} base;

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        memset(base.m, 0,sizeof(base.m));
        int n;
        scanf("%d", &n);
        while (n--) {
            ull x;
            scanf("%llu", &x);
            base.insert(x);
        }
        ull res = 0;
        for (int i = _xor::D; ~i; i--) res ^= base.m[i];
        printf("%llu\n", res);
    }

    return 0;
}

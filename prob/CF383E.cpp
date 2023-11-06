#include <bits/stdc++.h>
using namespace std;
const int LG = 24, MXN = 1 << LG;
int n, cnt[MXN];
char str[5];
int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", str);
        int x = 0;
        if (str[0] <= 'x') x |= 1 << (str[0] - 'a');
        if (str[1] <= 'x') x |= 1 << (str[1] - 'a');
        if (str[2] <= 'x') x |= 1 << (str[2] - 'a');
        ++cnt[x];
    }
    for (int i = 1; i < MXN; i <<= 1)
        for (int j = 0; j < MXN; j++)
            if (j & i) cnt[j] += cnt[i ^ j];
    int r = 0;
    for (int j = 0; j < MXN; j++) r ^= (n - cnt[j]) * (n - cnt[j]);
    printf("%d", r);

    return 0;
}

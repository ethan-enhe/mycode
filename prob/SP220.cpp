#include <bits/stdc++.h>

#include <cstdio>
using namespace std;
constexpr int MXN = 150005;
int n, m;
char str[MXN], _str[MXN];

int sa[MXN], rk[MXN], ork[MXN], cnt[MXN];
void init() {
    for (int i = 1; i <= n; i++) cnt[rk[i] = _str[i]]++;
    for (int i = m; i; i--) }

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%s", _str + 1);
            int len = strlen(_str + 1);
            for (int i = 1; i <= len; i++) str[i + n] = _str[i];
            str[n += len + 1] = '#';
        }
    }

    return 0;
}


#include <bits/stdc++.h>

#include <cstdio>

using namespace std;

const int N = 1e6 + 10;

char s[20];
int n, ans, q;
long long a[N];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
        //     scanf("%s", s + 1);
        //     int len = strlen(s + 1);
        //     for (int j = 1; j <= len; ++j)
        //         if (s[j] >= '0' && s[j] <= '9')
        //             a[i] = a[i] * 62LL + s[j] - '0' + 0;
        //         else if ('a' <= s[j] && s[j] <= 'z')
        //             a[i] = a[i] * 62LL + (s[j] - 'a' + 10);
        //         else a[i] = a[i] * 62LL + (s[j] - 'A' + 36);
        // //    printf("%d %d\n", i, a[i]);
    }
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x == -1) {
            ans = 1;
            bool lstflag = false;
            for (int i = 1; i <= n; ++i) {
                if (i <= 2)
                    printf("0");
                else {
                    if (lstflag && a[i] + a[i - 2 * ans] == 2 * a[i - ans])
                        printf("1");
                    else {
                        bool allflag = false;
                        // ans=max(ans,(i-1)/ans);
                        while (1 + 2 * ans <= i) {
                            if (a[i] + a[i - 2 * ans] == 2 * a[i - ans]) {
                                bool flag = true;
                                /*
                                for (int j = i - 1; 1 + 2 * ans <= j; --j)
                                    if (a[j] + a[j - 2 * ans] != 2 * a[j - ans]) {
                                        flag = false;
                                        break;
                                    }
                                */
                                for (int j = i - 1, k = 10; j - 2 * ans >= 1 && k; --j, --k)
                                    if (a[j] + a[j - 2 * ans] != 2 * a[j - ans]) {
                                        flag = false;
                                        break;
                                    }
                                if (flag) {
                                    allflag = true;
                                    break;
                                }
                            }
                            if (allflag) break;
                            ++ans;
                        }
                        lstflag = allflag;
                        if (allflag)
                            printf("1");
                        else
                            printf("0");
                    }
                }
            }
            printf("\n");
        } else
            a[x] = y;
    }

    return 0;
}

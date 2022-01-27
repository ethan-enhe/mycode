/*
 * +++A-B-C-
 *  ++A-B-+C-
 *
 *
 * ++A-+B- C-
 * ++A- B-+C-
 *
 *  +A-++B- C-
 * ++A-  B-+C-
 * +A-+B-+C-
 */
#include <bits/stdc++.h>
using namespace std;
const int MXN = 5e5 + 5;
int id, t, n, k;
char s1[MXN], s2[MXN];
int ind;
void dfs1(int dpth) {
    /* if(dpth%1000==0)cerr<<dpth<<endl; */
    for (;;) {
        if (s1[ind] == '(') {
            ++ind;
            dfs1(dpth + 1);
        } else if (s1[ind] == ')') {
            /* cerr<<"out"<<ind<<endl; */
            if (dpth) printf("%d %d\n", 6, dpth - 1);
            ++ind;
            return;
        }
    }
}
void dfs2(int dpth) {
    for (;;) {
        if (s2[ind] == '(') {
            printf("%d %d\n", 5, ind - 1);
            ++ind;
            dfs2(dpth + 1);
        } else if (s2[ind] == ')') {
            ++ind;
            return;
        }
    }
}
int main() {
    freopen("oper.in", "r", stdin);
    freopen("oper.out", "w", stdout);
    scanf("%d%d", &id, &t);
    while (t--) {
        scanf("%d%d %s %s", &n, &k, s1 + 1, s2 + 1);
        s1[n * 2 + 1] = s2[n * 2 + 1] = ')';
        ind = 1;
        printf("%d\n", n * 2);
        dfs1(0);
        ind = 1;
        dfs2(0);
        /* cerr<<"!!!"; */
    }

    return 0;
}

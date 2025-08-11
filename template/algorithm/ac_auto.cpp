// AC自动机（简单）
#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e6 + 5;
const int SZ = 26;
struct node {
    int mark, vis, fail, son[SZ];
} t[MXN];
int q[MXN], ql = 1, qr, nodec;
inline void insert(char *tstr, int len) {
    int p = 0;
    for (int i = 1; i <= len; i++) {
        if (t[p].son[tstr[i] - 'a'])
            p = t[p].son[tstr[i] - 'a'];
        else
            p = t[p].son[tstr[i] - 'a'] = ++nodec;
    }
    t[p].mark++;
}
inline void build() {
    for (int i = 0; i < SZ; i++)
        if (t[0].son[i]) q[++qr] = t[0].son[i];
    while (ql <= qr) {
        int p = q[ql++];
        for (int i = 0; i < SZ; i++) {
            int &nx = t[p].son[i], fa = t[p].fail;
            if (nx) {
                t[nx].fail = t[fa].son[i];
                q[++qr] = nx;
            } else
                nx = t[fa].son[i];
        }
    }
}
inline void run(char *tstr, int len) {
    int p = 0;
    for (int i = 1; i <= len; i++) {
        p = t[p].son[tstr[i] - 'a'];
        t[p].vis = 1;
    }
}
inline int add() {
    int res = 0;
    for (int i = qr; i; i--) {
        int p = q[i];
        if (t[p].vis) {
            t[t[p].fail].vis = 1;
            res += t[p].mark;
        }
    }
    return res;
}

int n;
char str[MXN];
int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%s", str + 1);
        insert(str, strlen(str + 1));
    }
    build();
    scanf("%s", str + 1);
    run(str, strlen(str + 1));
    printf("%d", add());

    return 0;
}

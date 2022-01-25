#include <bits/stdc++.h>
using namespace std;
const int MXN = 5, MXS = 17, MXC = 26;
int n, l, C;
char str[MXS];
struct node {
    int son[MXC], fail;
    bool mark;
} t[MXS * MXN];
int nodec;
void ins(char *s) {
    int p = 0;
    while (*s) {
        int &nx = t[p].son[*s++ - 'a'];
        if (!nx) nx = ++nodec;
        p = nx;
    }
    t[p].mark = 1;
}
void init() {
    queue<int> q;
    for (int i = 0; i < C; i++)
        if (t[0].son[i]) q.push(t[0].son[i]);
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        int fail = t[p].fail;
        t[p].mark |= t[fail].mark;
        for (int i = 0; i < C; i++) {
            int &nx = t[p].son[i];
            if (nx) {
                t[nx].fail = t[fail].son[i];
                q.push(nx);
            } else
                nx = t[fail].son[i];
        }
    }
}
int main(int argc, char *argv[]) {
    scanf("%d%d%d", &n, &l, &C);
    while (n--) {
        scanf("%s", str + 1);
        ins(str + 1);
    }
    init();
    for (int i = 1; i <= nodec; i++) printf("%d %d %d\n", i, t[i].fail, t[i].mark);

    return 0;
}

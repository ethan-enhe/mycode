#include <bits/stdc++.h>
using namespace std;
const int MXN = 5, MXS = 17, MXDP = MXN * MXS, MXC = 26;
int n, l, C;
char str[MXS];
struct node {
    int son[MXC], fail;
    bool mark;
} t[MXDP];
int nodec;
void insert(char *s) {
    int p = 0;
    while (*s) {
        int &nx = t[p].son[*s++ - 'a'];
        if (!nx) nx = ++nodec;
        p = nx;
    }
    t[p].mark = 1;
}
void build() {
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
struct mat {
    double v[MXDP][MXDP];
    mat(bool f = 0) {
        memset(v, 0, sizeof(v));
        if (f)
            for (int i = 0; i < MXDP; i++) v[i][i] = 1;
    }
    mat operator*(const mat &b) const {
        mat res;
        for (int i = 0; i <= nodec; i++)
            for (int j = 0; j <= nodec; j++)
                for (int k = 0; k <= nodec; k++) res.v[i][j] += v[i][k] * b.v[k][j];
        return res;
    }
} mult;
mat qpow(mat x, int y) {
    mat res(1);
    while (y) {
        if (y & 1) res = res * x;
        x = x * x, y >>= 1;
    }
    return res;
}

int main(int argc, char *argv[]) {
    ;

    scanf("%d%d%d", &n, &l, &C);
    while (n--) {
        scanf("%s", str + 1);
        insert(str + 1);
    }
    build();
    for (int i = 0; i <= nodec; i++) {
        if (t[i].mark) mult.v[i][nodec + 1]++;
        for (int j = 0; j < C; j++) {
            int nx = t[i].mark ? t[0].son[j] : t[i].son[j];
            mult.v[i][nx] += 1. / C;
        }
    }
    ++nodec;
    mult.v[nodec][nodec]++;
    mult = qpow(mult, l + 1);
    printf("%.6f", mult.v[0][nodec]);

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int MXN = 1.1e6 + 5;
struct node {
    int va, sz, rnd, ls, rs;
} t[MXN];
int nodec, rt;
inline int nnode(int x) { return t[++nodec] = {x, 1, rand()}, nodec; }
inline void pushd(int p) {}
inline void pushu(int p) { t[p].sz = t[t[p].ls].sz + 1 + t[t[p].rs].sz; }
inline int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (t[x].rnd > t[y].rnd) {
        pushd(x), t[x].rs = merge(t[x].rs, y);
        return pushu(x), x;
    } else {
        pushd(y), t[y].ls = merge(x, t[y].ls);
        return pushu(y), y;
    }
}
inline void splitrk(int p, int &l, int &r, int rk) {
    if (!p) {
        l = r = 0;
        return;
    }
    pushd(p);
    int tmp = t[t[p].ls].sz + 1;
    if (rk < tmp)
        splitrk(t[r = p].ls, l, t[p].ls, rk);
    else
        splitrk(t[l = p].rs, t[p].rs, r, rk - tmp);
    pushu(p);
}
inline void splitva(int p, int &l, int &r, int va) {
    if (!p) {
        l = r = 0;
        return;
    }
    pushd(p);
    if (va < t[p].va)
        splitva(t[r = p].ls, l, t[p].ls, va);
    else
        splitva(t[l = p].rs, t[p].rs, r, va);
    pushu(p);
}
inline void ins(int x) {
    int a, b;
    splitva(rt, a, b, x);
    rt = merge(a, merge(nnode(x), b));
}
inline void del(int x) {
    int a, b, c;
    splitva(rt, a, b, x - 1);
    splitva(b, b, c, x);
    rt = merge(a, merge(merge(t[b].ls, t[b].rs), c));
}
inline int rk(int x) {
    int a, b, r;
    splitva(rt, a, b, x - 1);
    r = t[a].sz + 1;
    rt = merge(a, b);
    return r;
}
inline int va(int rk) {
    int a, b, c, r;
    splitrk(rt, b, c, rk);
    splitrk(b, a, b, rk - 1);
    r = t[b].va;
    rt = merge(a, merge(b, c));
    return r;
}
int n, m, last, ans;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int tmp;
        scanf("%d", &tmp);
        ins(tmp);
    }
    while (m--) {
        int op, x;
        scanf("%d%d", &op, &x);
        x ^= last;
        if (op == 1)
            ins(x);
        else if (op == 2)
            del(x);
        else if (op == 3)
            ans ^= (last = rk(x));
        else if (op == 4)
            ans ^= (last = va(x));
        else if (op == 5)
            ans ^= (last = va(rk(x) - 1));
        else
            ans ^= (last = va(rk(x + 1)));
    }
    printf("%d\n", ans);
    return 0;
}

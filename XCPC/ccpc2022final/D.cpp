#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
mt19937 mrd(114);
const int MAXN = 500051;
const int P = 998244353;
struct Matrix {
    int a[3][3];
    Matrix() { memset(a, 0, sizeof(a)); }
    bool chkI() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (a[i][j] != (i == j)) return false;
            }
        }
        return true;
    }
    void prt() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) cerr << a[i][j] << ' ';
            cout << '\n';
        }
        cout << '\n';
    }
};
Matrix operator*(const Matrix &u, const Matrix &v) {
    Matrix ans;
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                ans.a[i][j] = (ans.a[i][j] + 1ll * u.a[i][k] * v.a[k][j]) % P;
            }
        }
    }
    return ans;
}

ll pwr(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % P;
        x = x * x % P;
        y >>= 1;
    }
    return ans;
}
Matrix getinv(Matrix x) {
    Matrix res;
    for (int i = 0; i < 3; i++) res.a[i][i] = 1;
    for (int i = 0; i < 3; i++) {
        int mult = pwr(x.a[i][i], P - 2);
        for (int j = 0; j < 3; j++) {
            x.a[i][j] = 1ll * x.a[i][j] * mult % P;
            res.a[i][j] = 1ll * res.a[i][j] * mult % P;
        }
        for (int j = 0; j < 3; j++) {
            if (j == i) continue;
            int mult = x.a[j][i];
            for (int k = 0; k < 3; k++) {
                x.a[j][k] = (x.a[j][k] - 1ll * x.a[i][k] * mult) % P;
                res.a[j][k] = (res.a[j][k] - 1ll * res.a[i][k] * mult) % P;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res.a[i][j] = (res.a[i][j] % P + P) % P;
        }
    }
    return res;
}

int n, q;
char a[MAXN];
Matrix b[3][2];
const int MAXT = MAXN * 4;
int rt, tsz;
Matrix sm[MAXT][3];
int tg[MAXT];
int ls[MAXT], rs[MAXT];
void upd(int nw) {
    for (int i = 0; i < 3; i++) sm[nw][i] = sm[ls[nw]][(i + tg[nw]) % 3] * sm[nw][(i + tg[nw]) % 3];
}
void bld(int &nw, int lft, int rgt) {
    nw = ++tsz;
    if (lft == rgt) {
        for (int i = 0; i < 3; i++) sm[nw][i] = b[(a[lft] - '0' + i) % 3][lft & 1];
        return;
    }
    int mid = (lft + rgt) >> 1;
    bld(ls[nw], lft, mid);
    bld(rs[nw], mid + 1, rgt);
    upd(nw);
}
void mdfy1(int nw, int lft, int rgt, int l, int r) {
    if (lft == l && rgt == r) {
        tg[nw]++;
        Matrix tmp = sm[nw][0];
        sm[nw][0] = sm[nw][1];
        sm[nw][1] = sm[nw][2];
        sm[nw][2] = tmp;
        return;
    }
    int mid = (lft + rgt) >> 1;
    if (l <= mid) mdfy1(ls[nw], lft, mid, l, min(mid, r));
    if (r >= mid + 1) mdfy1(rs[nw], mid + 1, rgt, max(mid + 1, l), r);
    upd(nw);
}
Matrix getsm(int nw, int lft, int rgt, int l, int r, int val) {
    if (lft == l && rgt == r) return sm[nw][val];
    val = (val + tg[nw]) % 3;
    int mid = (lft + rgt) >> 1;
    Matrix ans;
    if (r <= mid)
        ans = getsm(ls[nw], lft, mid, l, r, val);
    else if (l >= mid + 1)
        ans = getsm(rs[nw], mid + 1, rgt, l, r, val);
    else
        ans = getsm(ls[nw], lft, mid, l, mid, val) * getsm(rs[nw], mid + 1, rgt, mid + 1, r, val);
    // ans.prt();
    return ans;
}
int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);
    for (int i = 0; i < 3; i++) {
        for (int u = 0; u < 3; u++) {
            for (int v = 0; v < 3; v++) {
                b[i][0].a[u][v] = mrd() % (P - 1) + 1;
            }
        }
        b[i][1] = getinv(b[i][0]);
        // cout << (b[i][0] * b[i][1]).chkI() << '\n';
        // b[i][0].prt();
        // b[i][1].prt();
    }
    cin >> n >> q;
    cin >> (a + 1);
    bld(rt, 1, n);
    while (q--) {
        int op, u, v;
        cin >> op >> u >> v;
        if (op == 1)
            mdfy1(rt, 1, n, u, v);
        else {
            // getsm(rt, 1, n, u, v, 0).prt();
            if (getsm(rt, 1, n, u, v, 0).chkI())
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }
    return 0;
}

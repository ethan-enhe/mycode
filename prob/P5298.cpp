#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define vec vector
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

struct mll;

typedef long long ll;
typedef pair<int, int> pi;
typedef vec<int> vi;
typedef vec<pi> vpi;
//}}}
const char nl='\n';
const int INF = 1e9 + 5;
const ll P(998244353);
//{{{ Func
template <typename T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
template <typename T>
void read(vec<T> &x) {
    for (T &v : x) cin >> v;
}
template <typename T>
void prt(vec<T> &x, char join = ' ') {
    for (T &v : x) cout << v << join;
}
//}}}
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mll {
    int v;
    mll() : v() {}
    template <typename T>
    mll(const T &_v) : v(_v) {
        if (v >= P || v < 0) v = incr(v % P);
    }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mll operator+(const mll &y) const { return mll{redu(v + y.v)}; }
    mll operator-(const mll &y) const { return mll{incr(v - y.v)}; }
    mll operator*(const mll &y) const { return mll{1ll * v * y.v % P}; }
    mll operator/(const mll &y) const { return mll{1ll * v * (ll)qpow(y, P - 2) % P}; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = incr(v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = 1ll * v * y.v % P, *this; }
    mll &operator/=(const mll &y) { return v = 1ll * v * (ll)qpow(y, P - 2) % P, *this; }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mll &y) {
        ll x;
        is >> x;
        return y = mll(x), is;
    }
    friend ostream &operator<<(ostream &os, const mll &y) { return os << y.v; }
};
//}}}

struct node {
    mll va, tag;
    int ls, rs;
};
vec<node> t;

int nodec;
void pushu(int p) { t[p].va = t[t[p].ls].va + t[t[p].rs].va; }
void addt(int p, mll tv) {
    t[p].va *= tv;
    t[p].tag *= tv;
}
void pushd(int p) {
    if (t[p].tag != 1) {
        if (t[p].ls) addt(t[p].ls, t[p].tag);
        if (t[p].rs) addt(t[p].rs, t[p].tag);
        t[p].tag = 1;
    }
}
void mod(int &p, int l, int r, int qi, mll qv) {
    if (!p) p = ++nodec;
    if (l == r) {
        t[p].va = qv;
        return;
    }
    int mid = (l + r) >> 1;
    if (qi <= mid)
        mod(t[p].ls, l, mid, qi, qv);
    else
        mod(t[p].rs, mid + 1, r, qi, qv);
    pushu(p);
}
mll que(int p, int l, int r, int qi) {
    if (!p || l == r) return t[p].va;
    int mid = (l + r) >> 1;
    pushd(p);
    if (qi <= mid)
        return que(t[p].ls, l, mid, qi);
    else
        return que(t[p].rs, mid + 1, r, qi);
}
vpi son;
vi w;
// C[i]=p[u]*(A[i]*B[<i]+A[<i]*B[i])+(1-p[u])*(A[i]*B[>i]+A[>i]*B[i])
int mrg(int xr, int yr, int l, int r, mll xp, mll xs, mll yp, mll ys, mll p) {
    if (!xr) {
        addt(yr, p * xp + ((mll)1 - p) * xs);
        return yr;
    }
    if (!yr) {
        addt(xr, p * yp + ((mll)1 - p) * ys);
        return xr;
    }
    if (l == r) {
        t[xr].va = p * (t[xr].va * yp + xp * t[yr].va) + ((mll)1 - p) * (t[xr].va * ys + xs * t[yr].va);
        return xr;
    }
    pushd(xr), pushd(yr);
    int mid = (l + r) >> 1;
    mll nxp = xp + t[t[xr].ls].va, nyp = yp + t[t[yr].ls].va;
    t[xr].ls = mrg(t[xr].ls, t[yr].ls, l, mid, xp, xs + t[t[xr].rs].va, yp, ys + t[t[yr].rs].va, p);
    t[xr].rs = mrg(t[xr].rs, t[yr].rs, mid + 1, r, nxp, xs, nyp, ys, p);
    pushu(xr);
    return xr;
}
int dfs(int p) {
    int rt = 0;
    if (son[p].fi) {
        if (son[p].se)
            rt = mrg(dfs(son[p].fi), dfs(son[p].se), 1, INF, 0, 0, 0, 0, (mll)w[p] / 10000);
        else
            rt = dfs(son[p].fi);
    } else
        mod(rt, 1, INF, w[p], 1);
    return rt;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    t = vec<node>(n * log2(INF) * 2, {0, 1, 0, 0});

    son.resize(n + 1);
    w.resize(n);
    for (int i = 1; i <= n; i++) {
        int fa;
        cin >> fa;
        (son[fa].fi ? son[fa].se : son[fa].fi) = i;
    }
    read(w);
    w.insert(w.begin(), 0);
    int res = dfs(1);
    vi poss;
    for (int i = 1; i <= n; i++)
        if (!son[i].fi) poss.push_back(w[i]);
    sort(poss.begin(), poss.end());
    mll ans = 0;
    for (int i = 0; i < poss.size(); i++) {
        mll tmp = que(res, 1, INF, poss[i]);
        ans += (mll)(i + 1) * poss[i] * tmp * tmp;
    }
    cout << ans << nl;

    return 0;
}

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
#define NDEBUG
#endif
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
//{{{ Func
tpl pair<T, T> &operator+=(pair<T, T> &x, const pair<T, T> &y) { return x.fi += y.fi, x.se += y.se, x; }
tpl pair<T, T> operator+(const pair<T, T> &x, const pair<T, T> &y) { return {x.fi + y.fi, x.se + y.se}; }
tpl pair<T, T> &operator-=(pair<T, T> &x, const pair<T, T> &y) { return x.fi -= y.fi, x.se -= y.se, x; }
tpl pair<T, T> operator-(const pair<T, T> &x, const pair<T, T> &y) { return {x.fi - y.fi, x.se - y.se}; }
tpl pair<T, T> &operator*=(pair<T, T> &x, const ll &y) { return x.fi *= y, x.se *= y, x; }
tpl pair<T, T> operator*(const pair<T, T> &x, const ll &y) { return {x.fi * y, x.se * y}; }
tpl istream &operator>>(istream &is, pair<T, T> &y) { return is >> y.fi >> y.se; }
tpl ostream &operator<<(ostream &os, const pair<T, T> &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
tpl T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (!a || !b) return a | b;
    ll U = __builtin_ctzll(a), V = __builtin_ctzll(b);
    a >>= U, b >>= V;
    if (U > V) U = V;
    while (a) {
        if (a < b) swap(a, b);
        a -= b;
        a >>= __builtin_ctzll(a);
    }
    return b << U;
}
tpl void umx(T &x, const T &y) { x = max(x, y); }
tpl void umn(T &x, const T &y) { x = min(x, y); }
bool inrng(const ll &x, const ll &l, const ll &r) { return l <= x && x <= r; }
bool insqr(const pi &x, const pi &lt, const pi &rb) {
    return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se;
}
void setp(const ll &x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
}
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());
ll ri(const ll &l, const ll &r) { return uniform_int_distribution<ll>(l, r)(mr); }
ld rd(const ld &l, const ld &r) { return uniform_real_distribution<ld>(l, r)(mr); }
//}}}
const ll P = 1e9 + 7;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() {}
    tpl mod(const T &_v) : v(_v) { assert(_v >= 0 && _v < P); }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = (ll)v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = (ll)v * qpow(y, P - 2).v % P, *this; }
    mod operator+(const mod &y) const { return mod(*this) += y; }
    mod operator-(const mod &y) const { return mod(*this) -= y; }
    mod operator*(const mod &y) const { return mod(*this) *= y; }
    mod operator/(const mod &y) const { return mod(*this) /= y; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y.v = incr(x % P), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
//}}}
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e5 + 5;

ll n, m, q;
ll arr[MXN];

struct mat {
    mod v[4][4];
    mat(bool f = 0) {
        memset(v, 0, sizeof(v));
        if (f)
            for (int i = 0; i < 4; i++) v[i][i] = 1;
    }
    bool is1() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (v[i][j].v != (i == j)) return 0;
        return 1;
    }
    inline mat operator*(const mat &y) const {
        mat res;
        for (int i = 0; i < 4; i++)
            for (int j = i; j < 4; j++)
                for (int k = j; k < 4; k++) res.v[i][k] += v[i][j] * y.v[j][k];
        return res;
    }
    inline mat operator^(const mat &y) const {
        mat res;
        for (int j = 0; j < 4; j++)
            for (int k = j; k < 4; k++) res.v[0][k] += v[0][j] * y.v[j][k];
        return res;
    }
    mat operator+(const mat &y) const {
        mat res;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) res.v[i][j] = v[i][j] + y.v[i][j];
        return res;
    }
    void prt() {
        for (int i = 0; i < 4; i++, cout << endl)
            for (int j = 0; j < 4; j++) cout << v[i][j] << " ";
    }
};

// sum a,sum a^2,hsum a^2
// +=t:
// suma=suma+t*len
// suma^2=suma^2+t*t*len+2*suma*t
// hsuma^2=hsuma^2+suma^2+t*t*len+2*suma*t
// vec={len,sum a,sum a^2,hsum a^2}
// trans={
// {1,t,t*t,t*t},
// {0,1,2*t,2*t}
// {0,0,1,1}
// {0,0,0,1}
// }
#define ls p << 1
#define rs p << 1 | 1

mat cal(mod k) {
    mat res(1);
    res.v[0][1] = k;
    res.v[0][2] = k * k;
    res.v[0][3] = k * k;
    res.v[1][2] = k * 2;
    res.v[1][3] = k * 2;
    res.v[2][3] = 1;
    return res;
}
struct node {
    mat sum, tag;
} t[MXN << 2];
void pull(ll p) { t[p].sum = t[ls].sum + t[rs].sum; }
void addt(ll p, const mat &k) {
    t[p].sum = t[p].sum ^ k;
    t[p].tag = t[p].tag * k;
}
void push(ll p) {
    if (!t[p].tag.is1()) {
        addt(ls, t[p].tag);
        addt(rs, t[p].tag);
        t[p].tag = mat(1);
    }
}
void build(ll p = 1, ll l = 1, ll r = n) {
    t[p].tag = mat(1);
    if (l == r) {
        t[p].sum.v[0][0] = 1;
        t[p].sum.v[0][1] = arr[l];
        t[p].sum.v[0][2] = t[p].sum.v[0][1] * t[p].sum.v[0][1];
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pull(p);
}
mat sum(ll ql, ll qr, ll p = 1, ll l = 1, ll r = n) {
    if (ql > r || qr < l) return mat();
    if (ql <= l && r <= qr) return t[p].sum;
    ll mid = (l + r) >> 1;
    push(p);
    return sum(ql, qr, ls, l, mid) + sum(ql, qr, rs, mid + 1, r);
}
void add(ll ql, ll qr, const mat &k, ll p = 1, ll l = 1, ll r = n) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        addt(p, k);
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    add(ql, qr, k, ls, l, mid);
    add(ql, qr, k, rs, mid + 1, r);
    pull(p);
}
struct _mdf {
    ll l, r;
    mod delt;
} mdf[MXN];

struct _ask {
    ll l, r, id;
};
vector<_ask> ask[MXN];
mod ans[MXN];

int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] = incr(arr[i] % P);
    }
    for (ll i = 1; i <= m; i++) cin >> mdf[i].l >> mdf[i].r >> mdf[i].delt;
    for (ll i = 1; i <= q; i++) {
        ll l, r, x, y;
        cin >> l >> r >> x >> y;
        ask[x].push_back({l, r, -i});
        ask[y + 1].push_back({l, r, i});
    }
    build();
    mdf[0] = {1, n, 0};
    for (int i = 0; i <= m + 1; i++) {
        for (auto &j : ask[i]) {
            if (j.id > 0)
                ans[j.id] += sum(j.l, j.r).v[0][3];
            else
                ans[-j.id] -= sum(j.l, j.r).v[0][3];
        }
        if (i <= m) {
            if (mdf[i].l != 1) add(1, mdf[i].l - 1, cal(0));
            if (mdf[i].r != n) add(mdf[i].r + 1, n, cal(0));
            add(mdf[i].l, mdf[i].r, cal(mdf[i].delt));
            // cerr << mdf[i].l << " " << mdf[i].r << " " << mdf[i].delt << endl;
        }
        // cout << sum(2, 2).v[0][3] << endl;
    }
    for (ll i = 1; i <= q; i++) cout << ans[i] << nl;
    return 0;
}

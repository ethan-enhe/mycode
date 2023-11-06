// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
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

using ll = int;
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
const ll P = 998244353;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() {}
    tpl mod(const T &_v) : v(_v) { assert(_v >= 0 && _v < P); }
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
const ll MXN = 3e5 + 5;

ll n, m, arr[MXN];

struct node {
    ll tagx, tagy;
    mod sum01, sum10;
    mod sumx0, sumy0;
    mod sum;
    node() {
        tagx = tagy = -1;
        sum01 = sum10 = sumx0 = sumy0 = sum = 0;
    }
    friend node operator+(const node &x, const node &y) {
        node res;
        res.sum01 = x.sum01 + y.sum01;
        res.sum10 = x.sum10 + y.sum10;
        res.sumx0 = x.sumx0 + y.sumx0;
        res.sumy0 = x.sumy0 + y.sumy0;
        res.sum = x.sum + y.sum;
        return res;
    }
} t[MXN << 2];

#define ls p << 1
#define rs p << 1 | 1

void pull(ll p) { t[p] = t[ls] + t[rs]; }
void addt(ll p, ll tx, ll ty) {
    if (tx != -1) {
        t[p].tagx = tx;
        if (tx) {
            t[p].sum01 = 0;
            t[p].sum10 = t[p].sumy0;
            t[p].sumx0 = 0;
        } else {
            t[p].sum01 = t[p].sum - t[p].sumy0;
            t[p].sum10 = 0;
            t[p].sumx0 = t[p].sum;
        }
    }
    if (ty != -1) {
        t[p].tagy = ty;
        if (ty) {
            t[p].sum01 = t[p].sumx0;
            t[p].sum10 = 0;
            t[p].sumy0 = 0;
        } else {
            t[p].sum01 = 0;
            t[p].sum10 = t[p].sum - t[p].sumx0;
            t[p].sumy0 = t[p].sum;
        }
    }
}
void push(ll p) {
    if (t[p].tagx != -1 || t[p].tagy != -1) {
        addt(ls, t[p].tagx, t[p].tagy);
        addt(rs, t[p].tagx, t[p].tagy);
        t[p].tagx = t[p].tagy = -1;
    }
}
void build(ll p = 1, ll l = 1, ll r = n + 1) {
    t[p] = node();
    if (l == r) return;
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
}
mod dp[MXN];
void upd(ll ui, ll p = 1, ll l = 1, ll r = n + 1) {
    if (l == r) {
        t[p].sum = dp[l];
        t[p].sumx0 = t[p].sumy0 = dp[l];
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    if (ui <= mid)
        upd(ui, ls, l, mid);
    else
        upd(ui, rs, mid + 1, r);
    pull(p);
}
void mod(ll tx, ll ty, ll ml, ll mr, ll p = 1, ll l = 1, ll r = n + 1) {
    if (l > mr || r < ml) return;
    if (ml <= l && r <= mr) {
        addt(p, tx, ty);
        return;
    }
    ll mid = (l + r) >> 1;
    push(p);
    mod(tx, ty, ml, mr, ls, l, mid);
    mod(tx, ty, ml, mr, rs, mid + 1, r);
    pull(p);
}

ll mx[MXN], mn[MXN];
ll tmx, tmn;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    /* //test */
    /* n = 5; */
    /* dp[1] = 1; */
    /* dp[2] = 2; */
    /* dp[3] = 4; */
    /* upd(1); */
    /* upd(2); */
    /* upd(3); */
    /* cout << t[1].sum01 << " " << t[1].sum10 << nl; */
    /* mod(1, -1, 1, 3); */
    /* cout << t[1].sum01 << " " << t[1].sum10 << nl; */
    /* mod(0, 1, 2, 3); */
    /* cout << t[1].sum01 << " " << t[1].sum10 << nl; */
    int task;
    cin >> task;
    while (task--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) cin >> arr[i];
        tmx = tmn = 0;
        mx[0] = mn[0] = n + 1;
        build();
        dp[n + 1] = 1;
        upd(n + 1);
        for (ll i = n; i; i--) {
            while (tmx && arr[i] > arr[mx[tmx]]) tmx--;
            mod(i & 1, -1, i + 1, mx[tmx]);
            mx[++tmx] = i;
            while (tmn && arr[i] < arr[mn[tmn]]) tmn--;
            mod(-1, i & 1, i + 1, mn[tmn]);
            mn[++tmn] = i;

            dp[i] = (i & 1) ? t[1].sum10 : t[1].sum01;
            upd(i);
            /* cout << dp[i] << nl; */
        }
        cout << dp[1] << nl;
    }
    return 0;
}

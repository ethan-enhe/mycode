// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <vector>
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
const ll MXN = 1e6 + 5, T = 4, C = 13, MXC = C + 5, M = 7, MXM = 8;

char card[10];
bool ina[T][MXC];
ll type(char x) {
    if (x == 'S')
        return 0;
    else if (x == 'H')
        return 1;
    else if (x == 'C')
        return 2;
    else
        return 3;
}
//涉及到的花色，当前花色，当前左，当前右，下一个走的人，是否全出
ll dp[MXM][MXM][MXM][MXM][MXM][MXM][MXM][MXM];
ll dfs(vector<ll> l, vector<ll> r, ll cur) {
    cur = !cur;
    ll &cdp = dp[l[0]][r[0]][l[1]][r[1]][l[2]][r[2]][l[3]][r[3]];
    if (cdp < -2) {
        cdp = -1;
        bool f = 1;
        //转换
        for (ll nxi = 0; nxi < T; nxi++) {
            if (!r[nxi] && ina[nxi][7] == cur) {
                l[nxi] = r[nxi] = 1;
                umx(cdp, -dfs(l, r, cur));
                l[nxi] = r[nxi] = 0;
            }
            if (r[nxi]) {
                if (r[nxi] != 7 && ina[nxi][7 + r[nxi]] == cur) {
                    ++r[nxi];
                    umx(cdp, -dfs(l, r, cur));
                    --r[nxi];
                }
                if (l[nxi] != 7 && ina[nxi][7 - l[nxi]] == cur) {
                    ++l[nxi];
                    umx(cdp, -dfs(l, r, cur));
                    --l[nxi];
                }
            }
            f &= (l[nxi] == 7 && r[nxi] == 7);
        }
        if (f) umx(cdp, 0ll);
        /* cerr << s << " " << i << " " << l << " " << r << " " << cur << " " << tie << " " << cdp << endl; */
    }
    return cdp;
}
int main() {
    /* cerr << (sizeof(dp) >> 20); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> card) {
        ll len = strlen(card), id;
        if (len == 3)
            id = card[2] - '0' + (card[1] - '0') * 10;
        else
            id = card[1] - '0';
        ina[type(card[0])][id] = 1;
        /* cerr << type(card[0]) << " " << id << nl; */
    }
    memset(dp, ~0x3f, sizeof(dp));
    /* cerr << "!!!" << endl; */
    ll f = dfs({1, 0, 0, 0}, {1, 0, 0, 0}, ina[0][7]);
    if (f == 0)
        cout << "Draw";
    else if (f == 1) {
        if (ina[0][7])
            cout << "Bob";
        else
            cout << "Alice";
    } else {
        if (!ina[0][7])
            cout << "Bob";
        else
            cout << "Alice";
    }
    return 0;
}

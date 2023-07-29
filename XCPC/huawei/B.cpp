// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <numeric>
#include <vector>
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << nl
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
const ll MXN = 105;
const ll NR = MXN * MXN;

ll n, m, f, p;
ll cusno[MXN][MXN];
ll cusfo[MXN][MXN];
ll transno[MXN][MXN], transc;
ll g[MXN][MXN];
ll fa[NR];
ll form[MXN][MXN];
ll I, J;
ll id(ll x, ll y) { return x * n + y; }
pi co(ll x) { return {x / n, x % n}; }
vector<pi> edge;
vector<ll> e[NR];

ll find(ll x) {
    while (x != fa[x]) x = fa[x] = fa[fa[x]];
    return x;
}
void dfs(ll p, ll fa) {
    for (auto it = e[p].begin(); it != e[p].end(); ++it)
        if (*it == fa) {
            e[p].erase(it);
            break;
        }
    pi c = co(p);
    if (!cusno[c.fi][c.se]) {
        transno[c.fi][c.se] = ++transc;
    }
    for (auto &nx : e[p]) {
        dfs(nx, p);
    }
}
void mrg(ll x, ll y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[x] = y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
}

void prt(ll x, ll y) {
    ll i = id(x, y);
    cout << x << " " << y << " " << e[i].size() << " ";
    for (auto &nx : e[i]) {
        auto c = co(nx);
        if (cusno[c.fi][c.se]) {
            cout << "1 " << cusno[c.fi][c.se] << " " << cusfo[c.fi][c.se] << " ";
        } else {
            cout << "0 1 " << transno[c.fi][c.se] << " ";
        }
    }
    cout << nl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> f >> p;
    cin >> I >> J;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> g[i][j];
            fa[id(i, j)] = id(i, j);
        }
    }
    for (ll i = 1; i <= m; i++) {
        ll x, y, z;
        cin >> x >> y >> z;
        cusno[x][y] = i;
        cusfo[x][y] = z;
    }
    cusno[I][J] = -1;
    for (ll i = 1; i <= f; i++) {
        for (ll j = 1; j <= f; j++) {
            cin >> form[i][j];
        }
    }
    iota(fa, fa + NR, 0);
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < n; j++)
            for (ll k = j + 1; k < n; k++) {
                if (!(cusno[i][j] && cusno[i][k])) edge.emplace_back(id(i, j), id(i, k));
                if (!(cusno[j][i] && cusno[k][i])) edge.emplace_back(id(j, i), id(k, i));
                break;
            }
    shuffle(all(edge), mr);
    for (auto &i : edge) {
        mrg(i.fi, i.se);
    }
    dfs(id(I, J), 0);
    cout << transc << nl;
    prt(I, J);
    for (ll i = 1; i <= transc; i++) {
        for (ll j = 0; j < n; j++)
            for (ll k = 0; k < n; k++)
                if (transno[j][k] == i) prt(j, k);
    }

    return 0;
}

#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define vec vector
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

struct mod;

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ Func
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
istream &operator>>(istream &is, pi &y) { return is >> y.fi >> y.se; }
ostream &operator<<(ostream &os, pi &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
template <typename T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, T y) {
    x = min(x, y);
}
ll abs(pi x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
bool insqr(pi x, pi lt, pi rb) { return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se; }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
void setp(ll x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void read(T &x, int l, int r) {
    for (int i = l; i <= r; i++) cin >> x[i];
}
template <typename T>
void prt(T &x, int l, int r, char join = ' ') {
    for (int i = l; i <= r; i++) cout << x[i] << join;
}
//}}}
const ll P = 998244353;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() : v() {}
    template <typename T>
    mod(const T &_v) : v(_v) {
        if (v >= P || v < 0) v = incr(v % P);
    }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod operator+(const mod &y) const { return mod{redu(v + y.v)}; }
    mod operator-(const mod &y) const { return mod{incr(v - y.v)}; }
    mod operator*(const mod &y) const { return mod{1ll * v * y.v % P}; }
    mod operator/(const mod &y) const { return mod{1ll * v * (ll)qpow(y, P - 2) % P}; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = 1ll * v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = 1ll * v * (ll)qpow(y, P - 2) % P, *this; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y = mod(x), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
//}}}
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const char nl = '\n';
const ll MXN = 1e6 + 5;
ll n, m;
char str[MXN];

char opt[MXN];
ll son[MXN][2];
ll nodec, ind = 1;
ll build(ll &ind) {
    ll p = ++nodec;
    if (str[ind] == 'x')
        opt[p] = 'x';
    else {
        son[p][0] = build(++ind);
        opt[p] = str[ind];
        son[p][1] = build(++ind);
    }
    ++ind;
    return p;
}
const mod inv2 = (mod)1 / 2, inv4 = (mod)1 / 4;
mod dp[MXN][2];
bool cal(char type, bool x, bool y) {
    switch (type) {
        case '|': return x | y;
        case '&': return x & y;
        case '^': return x ^ y;
    }
    assert(0);
}
void dfs(ll p) {
    if (opt[p] == 'x') {
        dp[p][0] = dp[p][1] = inv2;
        return;
    }
    dfs(son[p][0]);
    dfs(son[p][1]);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) dp[p][cal(opt[p], i, j)] += dp[son[p][0]][i] * dp[son[p][1]][j];
}
void redfs(ll p, mod chance) {
    if (opt[p] == 'x') {
        cout << chance << nl;
        return;
    } else if (opt[p] == '^') {
        redfs(son[p][0], chance);
        redfs(son[p][1], chance);
    } else if (opt[p] == '|') {
        redfs(son[p][0], chance * dp[son[p][1]][0]);
        redfs(son[p][1], chance * dp[son[p][0]][0]);
    } else if (opt[p] == '&') {
        redfs(son[p][0], chance * dp[son[p][1]][1]);
        redfs(son[p][1], chance * dp[son[p][0]][1]);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n >> (str + 1);
    build(ind);
    dfs(1);
    redfs(1, 1);

    return 0;
}

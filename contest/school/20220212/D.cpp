#include <bits/stdc++.h>

#include <algorithm>
#include <vector>

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
const ll P = 1e9 + 7;
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
const ll INF = 1e9 + 5;

ll n, m, k, r;
char str[MXN];
namespace k0 {
mod solve() {
    if (r) {
        ll last = -1;
        while (r--) {
            ll a, b, c;
            cin >> a >> b >> c;
            if (last == -1)
                last = c;
            else if (c != last)
                return 0;
        }
        return 1;

    } else
        return 2;
}
} // namespace k0

namespace k1 {
map<ll, ll> ind;
vec<pi> g[MXN];
ll vecc;

void ae(ll x, ll y, ll v) {
    if (!ind[x]) ind[x] = ++vecc;
    if (!ind[y]) ind[y] = ++vecc;
    g[ind[x]].push_back({y, v});
    g[ind[y]].push_back({x, v});
}
bool fixed, invalid, cur0;
ll sz;
map<ll, bool> mark;
void dfs(ll p, bool cm) {
    ++sz;
    mark[p] = cm;
    ll id = ind[p];
    if (!id) return;
    for (pi &nx : g[id]) {
        if (nx.fi == 1) {
            fixed = 1;
            continue;
        }
        auto it = mark.find(nx.fi);
        bool nxm = cm ^ nx.se ^ cur0;
        if (it == mark.end())
            dfs(nx.fi, nxm);
        else if (it->se != nxm)
            invalid = 1;
    }
}

mod solve() {
    vec<ll> app;
    for (int i = 1; i <= r; i++) {
        ll x, y, v;
        cin >> x >> y >> v;
        --x, --y;
        if (x & 1 && y & 1) v ^= 1;
        if (y) y += INF;
        app.push_back(x), app.push_back(y);
        ae(x, y, v);
    }
    mod ans = 0;
    for(ll x:app)
        if(x)

    cur0 = 1;
    mark.clear();
    return ans;
}
} // namespace k1

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n >> m >> k >> r;
    mod ans;
    if (!k)
        ans = k0::solve();
    else {
    }
    cout << ans << endl;
    return 0;
}

#include <bits/stdc++.h>

#include <numeric>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

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
const ll INF = 1e18;
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const char nl = '\n';
const ll MXN = 1e5 + 5, NR = MXN * 30;

ll n, m, nodec, fa[NR], mn[NR];
pi arr[6][MXN];
ll find(ll x) {
    while (fa[x] != x) x = fa[x] = fa[fa[x]];
    return x;
}
void merge(ll x, ll y) {
    cout << x << " " << y << endl;
    x = find(x), y = find(y);
    fa[y] = x;
    umn(mn[x], mn[y]);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    iota(fa, fa + NR, 0);
    fill(mn, mn + NR, INF);
    cin >> n >> m;
    for (ll i = 1, w; i <= n; i++) {
        for (int j = 1; j <= m; j++) cin >> arr[j][i].fi, arr[j][i].se = i;
        cin >> w;
        mn[i] = w;
    }
    nodec = n;
    for (int i = 1; i <= m; i++) {
        sort(arr[i] + 1, arr[i] + 1 + n), arr[i][n + 1].fi = -1;
        prt(arr[i], 1, n);
        cout << endl;
    }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++) {
            ll ind = 1;
            ++nodec;
            for (ll l = 1; l <= n; l++) {
                merge(nodec, arr[j][l].se);
                if (arr[j][l + 1].fi != arr[j][l].fi) {
                    while (ind <= n && arr[i][ind].fi <= arr[j][l].fi) {
                        if (arr[i][ind].fi == arr[j][l].fi) {
                            merge(nodec, arr[i][ind].se);
                        }
                        ++ind;
                    }
                    ++nodec;
                }
            }
            cout << i << " " << j << endl;
            for (int i = 1; i <= n; i++) cout << find(i) << " ";
            cout << endl;
        }
    return 0;
}

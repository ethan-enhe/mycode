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

ll n, m, k;
vec<mod> arr;
vec<ll> opt;

namespace fuck2in1 {
bool chk() { return k <= 3000; }
void fuck() {
    for (int i = 1; i <= k; i++)
        for (ll i = 1; i <= m; i++) {
            ll &cur = opt[i];
            arr[cur] = arr[cur - 1] + arr[cur + 1] - arr[cur];
        }
    mod ways = qpow(qpow((mod)2, m), k);
    for (int i = 1; i <= n; i++) arr[i] *= ways;
    prt(arr, 1, n);
}
} // namespace fuck2in1

namespace _fuck2in1 {
const ll MXN = 105;
struct mat {
    mod v[MXN][MXN];
    mat(bool f = 0) {
        if (f)
            for (int i = 0; i < MXN; i++) v[i][i] = 1;
    }
    mat operator*(const mat &b) const {
        mat res;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++) res.v[i][j] += v[i][k] * b.v[k][j];
        return res;
    }
    void flip() {
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++) swap(v[i][j], v[j][i]);
    }
} init, trans;
void jmp(mod *x, mod *l, mod *r) {
    for (int i = 1; i <= n; i++) x[i] = l[i] + r[i] - x[i];
}

void fuck() {
    for (int i = 1; i <= n; i++) {
        init.v[1][i] = arr[i];
        trans.v[i][i] = 1;
    }
    for (ll i = 1; i <= m; i++) {
        ll &cur = opt[i];
        jmp(trans.v[cur], trans.v[cur - 1], trans.v[cur + 1]);
    }
    trans.flip();
    /* for (int i = 1; i <= n; i++) { */
    /*     prt(trans.v[i], 1, n); */
    /*     cout << nl; */
    /* } */
    init = init * qpow(trans, k);
    mod ways = qpow(qpow((mod)2, m), k);
    for (int i = 1; i <= n; i++) init.v[1][i] *= ways;
    prt(init.v[1], 1, n);
}

} // namespace _fuck2in1

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n;
    arr.resize(n + 1);
    read(arr, 1, n);
    cin >> m >> k;
    opt.resize(m + 1);
    read(opt, 1, m);

    if (fuck2in1::chk()) fuck2in1::fuck();
    else _fuck2in1::fuck();
    return 0;
}

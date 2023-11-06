#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

using ll = long long;
using ull = unsigned long long;
using db = long double;
using ld = long double;
/* using ld = long double; */
using pi = pair<ll, ll>;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ Func
template <typename T1, typename T2>
pair<T1, T2> operator+(const pair<T1, T2> &x, const pair<T1, T2> &y) {
    return {x.fi + y.fi, x.se + y.se};
}
template <typename T1, typename T2>
pair<T1, T2> operator-(const pair<T1, T2> &x, const pair<T1, T2> &y) {
    return {x.fi - y.fi, x.se - y.se};
}
template <typename T1, typename T2>
pair<T1, T2> operator*(const pair<T1, T2> &x, const ll &y) {
    return {x.fi * y, x.se * y};
}
template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &y) {
    return is >> y.fi >> y.se;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &y) {
    return os << '(' << y.fi << ',' << y.se << ')';
}
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
void umx(T &x, const T &y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, const T &y) {
    x = min(x, y);
}
ll abs(const pi &x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
bool insqr(const pi &x, const pi &lt, const pi &rb) {
    return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se;
}
ll randint(const ll &l, const ll &r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(const ld &l, const ld &r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
void setp(const ll &x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void read(T &x, const ll &l, const ll &r) {
    for (ll i = l; i <= r; i++) cin >> x[i];
}
template <typename T>
void prt(T &x, const ll &l, const ll &r, const char &join = ' ') {
    for (ll i = l; i <= r; i++) cout << x[i] << join;
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
const ll MXN = 3e3 + 5;

ll n, m;

struct p {
    mutable db x, y;
    p(db x = 0, db y = 0) : x(x), y(y) {}
    inline p operator+(const p &b) const { return p(x + b.x, y + b.y); }
    inline p operator-(const p &b) const { return p(x - b.x, y - b.y); }
    inline db operator*(const p &b) const { return x * b.y - y * b.x; }
    inline p operator*(const db &z) const { return p(x * z, y * z); }
    inline p operator/(const db &z) const { return p(x / z, y / z); }
    inline bool operator<=(const p &b) const { return (*this) * b >= 0; }
    inline db abs() const { return sqrt(x * x + y * y); }
} arr[MXN];

db tot;
//当前点，当前所在边的靠左点
p getnx(p x, int &id, db len) {
    len += (x - arr[id]).abs();
    while (len > (arr[id + 1] - arr[id]).abs()) {
        len -= (arr[id + 1] - arr[id]).abs();
        ++id;
        if (id > n) id -= n;
    }
    return arr[id] + (arr[id + 1] - arr[id]) * len / (arr[id + 1] - arr[id]).abs();
}
db get_s(p x, int id) {
    db s = 0;
    for (int i = 1; i <= m; i++) {
        p tmp = x;
        x = getnx(x, id, tot / m);
        s += x * tmp;
    }
    return abs(s) / 2;
}

int main() {
    /* freopen("F.in", "r", stdin); */
    /* freopen("F.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(10);
    ll st = clock() + CLOCKS_PER_SEC * 7.5;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].x >> arr[i].y;
        arr[i + n] = arr[i];
        arr[i + n * 2] = arr[i];
    }
    arr[0] = arr[n];
    for (int i = 1; i <= n; i++) tot += (arr[i] - arr[i - 1]).abs();
    db ans = INF;
    while (clock() < st) {
        db T = 1e18, rate = 0.99;
        int cind = 1;
        p cp = getnx(arr[1], cind, randdb(0, tot));
        while (T > 1e-9 && clock() < st) {
            normal_distribution<db> dist(0, min(T, 0.24 * tot));
            db tmp = dist(myrand);
            if (tmp > tot)
                tmp = tot;
            else if (tmp < -tot)
                tmp = -tot;
            if (tmp < 0) tmp += tot;
            int nxind = cind;
            p nxp = getnx(cp, nxind, tmp);

            db r = get_s(cp, cind);
            db cur = r - get_s(nxp, nxind);
            if (cur > 0 || randdb(0, 1) <= exp(cur / T)) {
                cp = nxp;
                cind = nxind;
            }

            T *= rate;
            umn(ans, r);
        }
    }
    cout << ans << nl;

    return 0;
}

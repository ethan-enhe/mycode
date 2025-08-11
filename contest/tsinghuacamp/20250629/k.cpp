// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <deque>
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
const char nl = '\n';
const ll MXN = 1e6 + 5;
const ll LG = 63 - __builtin_clzll(MXN);

ll n, m, q, arr[MXN];

set<ll> col[MXN], row[MXN];
ll p[MXN];
ll true_h(ll x) {
    ll s = 0;
    for (; x; x -= (x & (-x))) s += p[x];
    return s;
}
ll virtual_h(ll x) {
    ll idx = 0;
    for (ll i = 1 << LG; i; i >>= 1) {
        if (p[i + idx] < x) {
            x -= p[i + idx];
            idx += i;
        }
    }
    return idx + 1;
}
void add(ll x, ll y) {
    for (; x < MXN; x += (x & (-x))) {
        p[x] += y;
    }
}

struct block {
    ll x, y[3];
};
void ins(ll x, ll vh) {
    // cerr << "ins: " << x << ' ' << vh << nl;
    col[x].insert(vh);
    row[vh].insert(x);
    if ((ll)row[vh].size() >= m) {
        for (auto i : row[vh]) {
            col[i].erase(vh);
        }
        row[vh].clear();
        add(vh, -1);
    }
}
bool drop(const block &b) {
    ll bh = -1;
    // cerr << "drop: " << b.x << ' ' << b.y[0] << ' ' << b.y[1] << ' ' << b.y[2] << nl;
    for (ll i = 0; i < 3; i++) {
        ll xi = b.x + i;
        ll vhi = col[xi].empty() ? 0 : *col[xi].rbegin();
        ll hi = true_h(vhi);
        bh = max(bh, hi + b.y[i]);
    }
    // cerr << "bh: " << bh << nl;
    if (bh > n) {
        return false;
    }
    ll vh[3] = {virtual_h(bh), virtual_h(bh - 1), virtual_h(bh - 2)};
    for (ll i = 0; i < 3; i++) {
        ll xi = b.x + i;
        for (ll j = 0; j < b.y[i]; j++) {
            ins(xi, vh[j]);
            // cerr << "ins: " << xi << ' ' << bh - j << nl;
        }
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (ll i = 1; i < MXN; i++) {
        add(i, 1);
        // col[i].insert(0);
    }
    cin >> n >> m >> q;
    for (ll i = 1; i <= q; i++) {
        block b;
        cin >> b.x >> b.y[0] >> b.y[1] >> b.y[2];
        if (!drop(b)) {
            cout << i << nl;
            return 0;
        }
    }
    cout << -1 << nl;
    return 0;
}

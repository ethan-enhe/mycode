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
const ll MXN = 1e6 + 5;

ll n, L, R, arr[MXN], p[MXN];
ll v[MXN];
void mod(ll x, ll y) {
    for (; x <= n; x += x & (-x)) v[x] += y;
}
ll que(ll x) {
    ll r = 0;
    for (; x; x -= x & (-x)) r += v[x];
    return r;
}

ll delt[MXN];
void prt() {
    prt(delt, 1, n);
    cout << nl;
    partial_sum(delt + 1, delt + 1 + n, delt + 1);
    prt(delt, 1, n);
    cout << nl;
    partial_sum(delt + 1, delt + 1 + n, delt + 1);
    prt(delt, 1, n);
    cout << nl;
    cout << "----\n";
    adjacent_difference(delt + 1, delt + 1 + n, delt + 1);
    adjacent_difference(delt + 1, delt + 1 + n, delt + 1);
}
void modd(ll l, ll r, ll y) {
    delt[l] += y;
    delt[r + 1] -= y;
}
void mod(ll l, ll r, ll b, ll k) {
    if (r < l) return;
    modd(l, l, b + l * k);
    modd(r + 1, r + 1, -(b + r * k));

    modd(l + 1, r, k);
}

bool cmp(ll x, ll y) { return arr[x] > arr[y]; }
void cal() {
    fill(v + 1, v + 1 + n, 0);
    for (int i = 1; i <= n; i++) {
        mod(p[i], 1);
        ll lft = que(p[i]), rht = i - lft;
        /* ans += max(min(lft, x) - max(x - rht, 1ll) + 1, 0ll); */
        if (lft <= rht) {
            mod(1, lft - 1, 0, 1);
            mod(lft, rht, lft, 0);
            mod(rht + 1, lft + rht + 1, lft + rht + 1, -1);
        } else {
            mod(1, rht, 0, 1);
            mod(rht + 1, lft - 1, rht + 1, 0);
            mod(lft, lft + rht + 1, lft + rht + 1, -1);
        }
    }
    /* cout << x << " " << ans << endl; */
}
int main() {
    /* freopen("A.in","r",stdin); */
    /* freopen("A.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    /* n = 10; */
    /* mod(1, 2, 2, -1); */
    cin >> n >> L >> R;
    read(arr, 1, n);
    iota(p + 1, p + 1 + n, 1);
    sort(p + 1, p + 1 + n, cmp);
    cal();
    partial_sum(delt + 1, delt + 1 + n, delt + 1);
    partial_sum(delt + 1, delt + 1 + n, delt + 1);

    ll ans = 0;
    for (int i = L; i <= R; i++) ans ^= delt[i];
    cout << ans << nl;
    return 0;
}

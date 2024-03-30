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
const ll MXN = 1e6 + 5;
const ll MXW = 15;

ll t, n, m;
ll w[MXN];
ll pri[MXN], pcnt;

ll fa[MXN], tot;
ll find(ll x) {
    while (x != fa[x]) x = fa[x] = fa[fa[x]];
    return x;
}
void mrg(ll x, ll y) {
    // cerr << x << " " << y << endl;
    x = find(x), y = find(y);
    if (x != y) {
        --tot;
        fa[x] = y;
    }
}

ll last[MXW];
ll solve(ll l, ll r) {
    for (ll i = l; i <= r; i++) fa[i] = i;
    ll ans = 0;
    ll lasttot = tot = r - l + 1;
    for (ll x = 0; x < MXW; x++) {
        for (ll g = 1; g <= r; g++) {
            memset(last, 0, sizeof(last));
            ll wg = w[g];
            ll st = l % g;
            st = st ? l + (g - st) : l;
            for (ll k = st; k <= r; k += g) last[w[k]] = k;
            for (ll k = st; k <= r; k += g) {
                ll wk = w[k];
                ll opp = x - wk + wg;
                // cerr << k << " " << opp << endl;
                if (opp >= 0 && opp < MXW && last[opp]) {
                    mrg(last[min(opp, wk)], k);
                }
            }
        }
        // cerr << x << " " << tot << /*   */ endl;
        ans += (lasttot - tot) * x;
        lasttot = tot;
        if (tot == 1) break;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll mxw = 0;
    for (ll i = 2; i < MXN; i++) {
        umx(mxw, w[i]);
        if (w[i] == 0) {
            w[i] = 1;
            pri[++pcnt] = i;
        }
        for (ll j = 1; pri[j] * i < MXN; j++) {
            if (i % pri[j] == 0) {
                w[i * pri[j]] = w[i];
                break;
            } else
                w[i * pri[j]] = w[i] + 1;
        }
    }
    ll t;
    cin >> t;
    while (t--) {
        ll l, r;
        cin >> l >> r;
        cout << solve(l, r) << nl;
    }
    return 0;
}

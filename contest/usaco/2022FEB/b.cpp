#include <bits/stdc++.h>

#include <algorithm>

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

ll n, m, arr[MXN];
char str[MXN];

//{{{ rho

inline ll qmul(ll x, ll y, ll mod) {
    ll res = x * y - mod * ll((ld)x / mod * y);
    if (res < 0) return res + mod;
    if (res < mod) return res;
    return res - mod;
}
inline ll qpow(ll x, ll y, ll mod) {
    ll res = 1;
    while (y) {
        if (y & 1) res = qmul(res, x, mod);
        x = qmul(x, x, mod), y >>= 1;
    }
    return res;
}
inline bool ispri(ll x) {
    if (x < 3) return x == 2;
    ll y = x - 1, h = 0;
    while (!(y & 1)) y >>= 1, h++;
    for (ll i = 0; i < 8; i++) {
        ll v = qpow(rand() % (x - 2) + 2, y, x), th = h;
        if (v == 1) continue;
        while (th--) {
            if (v == x - 1) break;
            v = qmul(v, v, x);
        }
        if (th == -1) return 0;
    }
    return 1;
}

inline ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
inline ll f(ll x, ll c, ll mod) {
    ll res = qmul(x, x, mod) + c;
    return res < mod ? res : res - mod;
}
inline ll rho(ll x) {
    ll c = rand() % (x - 1), s = 0;
    for (ll rg = 1;; rg <<= 1) {
        ll t = s, v = 1;
        for (ll j = 1; j <= rg; j++) {
            s = f(s, c, x);
            v = qmul(v, abs(s - t), x);
            if (!v) {
                ll g = gcd(s, x);
                if (g > 1) return g;
                return x;
            }
            if (j % 127 == 0) {
                ll g = gcd(v, x);
                if (g > 1) return g;
            }
        }
        ll g = gcd(s, x);
        if (g > 1) return g;
    }
}
vector<ll> res;
inline void fact(ll x) {
    if (x <= 1) return;
    if (ispri(x)) {
        res.push_back(x);
        return;
    }
    ll p;
    do
        p = rho(x);
    while (p == x);
    do
        x /= p;
    while (x % p == 0);
    fact(x), fact(p);
}
//}}}
map<ll, ll> cnt;
inline void dfs(ll pid, ll v) {
    if (pid == res.size()) {
        cnt[v] = 0;
        return;
    }
    ll lim = (ll)2e18 / res[pid];
    while (1) {
        dfs(pid + 1, v);
        if (v < lim)
            v *= res[pid];
        else
            break;
        if (arr[n] % v) break;
    }
}
ll gva(ll x) {
    auto it = cnt.find(x);
    return it == cnt.end() ? 0 : it->second;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    /* freopen("b.in", "r", stdin); */
    /* freopen("b.out", "w", stdout); */
    cin >> n;
    read(arr, 1, n);
    partial_sum(arr + 1, arr + 1 + n, arr + 1);
    fact(arr[n]);
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    dfs(0, 1);
    for (ll i = 1; i <= n; i++) {
        ++cnt[gcd(arr[i], arr[n])];
    }
    for (ll &p : res) {
        for (auto it = cnt.rbegin(); it != cnt.rend(); it++) {
            it->second += gva(it->first * p);
        }
        // cerr<<p<<" "<<cnt[1166]<<endl;
    }

    cin >> m;
    for (int i = 1; i <= m; i++) {
        ll q;
        cin >> q;
        // if(i==334)cerr<<q<<endl;
        if (arr[n] % q)
            cout << "-1\n";
        else
            cout << n + arr[n] / q - cnt[q] * 2 << '\n';
    }
    return 0;
}

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
using db = double;
using ld = long double;
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
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN], pre[MXN];
bool tp[MXN];

struct segq {
#define ls p << 1
#define rs p << 1 | 1
    struct node {
        ll cnt, sum, tag;
    } t[MXN << 2];
    void build(ll p, ll l, ll r, bool f) {
        if (l == r) {
            t[p].cnt = tp[l - 1] == f;
            return;
        }
        ll mid = (l + r) >> 1;
        build(ls, l, mid, f);
        build(rs, mid + 1, r, f);
        t[p].cnt = t[ls].cnt + t[rs].cnt;
    }
    void apply(ll p, ll d) {
        t[p].sum += t[p].cnt * d;
        t[p].tag += d;
    }
    void push(ll p) {
        if (t[p].tag) {
            apply(ls, t[p].tag);
            apply(rs, t[p].tag);
            t[p].tag = 0;
        }
    }
    void pull(ll p) { t[p].sum = t[ls].sum + t[rs].sum; }
    void mod(ll p, ll l, ll r, ll ql, ll qr, ll qv) {
        if (r < ql || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(p, qv);
            return;
        }
        push(p);
        ll mid = (l + r) >> 1;
        mod(ls, l, mid, ql, qr, qv);
        mod(rs, mid + 1, r, ql, qr, qv);
        pull(p);
    }
    ll que(ll p, ll l, ll r, ll ql, ll qr) {
        if (r < ql || qr < l) return 0;
        if (ql <= l && r <= qr) return t[p].sum;
        push(p);
        ll mid = (l + r) >> 1;
        return que(ls, l, mid, ql, qr) + que(rs, mid + 1, r, ql, qr);
    }
} seg[2];
vec<pi> que[MXN];
ll ans[MXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n >> m;
    read(arr, 1, n);
    for (int i = 1; i <= m; i++) {
        ll l, r;
        cin >> l >> r;
        que[r].push_back({l, i});
    }
    ll last[2] = {0, 0};
    for (int i = 1; i <= n; i++) {
        tp[i] = tp[i - 1] ^ (arr[i] & 1);
        if (arr[i] == 0) last[!tp[i]] = i;
        pre[i] = last[tp[i]];
    }
    seg[0].build(1, 1, n, 0);
    seg[1].build(1, 1, n, 1);
    for (int i = 1; i <= n; i++) {
        seg[tp[i]].mod(1, 1, n, pre[i] + 1, i, 1);
        for (pi &ask : que[i]) ans[ask.se] = seg[0].que(1, 1, n, ask.fi, i) + seg[1].que(1, 1, n, ask.fi, i);
    }
    prt(ans, 1, m, nl);

    return 0;
}

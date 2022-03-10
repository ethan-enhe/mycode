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
const ll MXN = 2e4 + 5, MXQ = 1e5 + 5;

ll n, m, q, arr[MXN], ans[MXQ];

//{{{ segt beats
struct beats {
    //最大，最大数量，次大
    ll f, fc, s;
};
inline beats unite(beats x, beats y) {
    if (y.f > x.f) swap(x, y);
    if (x.f != y.f) return {x.f, x.fc, max(x.s, y.f)};
    return {x.f, x.fc + y.fc, max(x.s, y.s)};
}

struct node {
    beats mx;
    ll tag, sum;
} t[MXN << 2];
inline void apply(ll p, ll delt) {
    t[p].tag += delt;
    t[p].mx.f += delt;
    t[p].sum += t[p].mx.fc * delt;
}
#define ls p << 1
#define rs p << 1 | 1
inline void push(ll p) {
    if (t[p].tag) {
        ll tmp = t[p].mx.f - t[p].tag;
        apply(ls, tmp == t[ls].mx.f ? t[p].tag : 0);
        apply(rs, tmp == t[rs].mx.f ? t[p].tag : 0);
        t[p].tag = 0;
    }
}
inline void pull(ll p) {
    t[p].sum = t[ls].sum + t[rs].sum;
    t[p].mx = unite(t[ls].mx, t[rs].mx);
}
void build(ll p, ll l, ll r) {
    t[p].tag = 0;
    if (l == r) {
        t[p].sum = arr[l];
        t[p].mx = {arr[l], 1, -INF};
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pull(p);
}
void smod(ll p, ll l, ll r, ll ql, ll qr, ll qmn) {
    if (t[p].mx.f <= qmn || r < ql || qr < l) return;
    if (ql <= l && r <= qr && qmn > t[p].mx.s) {
        apply(p, qmn - t[p].mx.f);
        return;
    }
    push(p);
    ll mid = (l + r) >> 1;
    smod(ls, l, mid, ql, qr, qmn);
    smod(rs, mid + 1, r, ql, qr, qmn);
    pull(p);
}
ll sque(ll p, ll l, ll r, ll ql, ll qr) {
    if (r < ql || qr < l) return 0;
    if (ql <= l && r <= qr) return t[p].sum;
    push(p);
    ll mid = (l + r) >> 1;
    return sque(ls, l, mid, ql, qr) + sque(rs, mid + 1, r, ql, qr);
}
//}}}

struct que1 {
    ll l, r, v;
} q1[MXN];
struct que2 {
    ll l1, r1, l2, r2, id;
} q2[MXQ];

bool cmp(const que2 &x, const que2 &y) {
    if (x.r1 == y.r1) return x.l1 > y.l1;
    return x.r1 < y.r1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    ll st = clock();
    /* cerr<<((sizeof(t)+sizeof(q1)+sizeof(q2))>>20); */
    /* freopen("test.in", "r", stdin); */
    /* freopen("B.out","w",stdout); */
    cin >> n >> m >> q;
    read(arr, 1, n);
    for (ll i = 1; i <= m; i++) cin >> q1[i].l >> q1[i].r >> q1[i].v;
    for (ll i = 1; i <= q; i++) {
        q2[i].id = i;
        cin >> q2[i].l1 >> q2[i].r1 >> q2[i].l2 >> q2[i].r2;
    }
    sort(q2 + 1, q2 + 1 + q, cmp);
    ll cnt = 0;
    while (cnt != q) {
        build(1, 1, n);
        ll l = 0, r;
        for (ll i = 1; i <= q; i++)
            if (q2[i].id) {
                if (!l) {
                    l = q2[i].l1;
                    r = q2[i].l1 - 1;
                }
                if (q2[i].l1 <= l && r <= q2[i].r1) {
                    while (r < q2[i].r1) {
                        ++r;
                        smod(1, 1, n, q1[r].l, q1[r].r, q1[r].v);
                    }
                    while (l > q2[i].l1) {
                        --l;
                        smod(1, 1, n, q1[l].l, q1[l].r, q1[l].v);
                    }
                    ans[q2[i].id] = sque(1, 1, n, q2[i].l2, q2[i].r2);
                    q2[i].id = 0;
                    ++cnt;
                }
            }
    }
    prt(ans, 1, q, nl);
    /* cerr << double(clock() - st) / CLOCKS_PER_SEC << endl; */
    return 0;
}

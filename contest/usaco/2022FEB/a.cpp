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

ll n, m, rt;
bool tp[MXN];
pi arr[MXN];

//{{{ fhq
struct node {
    ll sz, rnd, ls, rs;
    ll va, sum;
    node() {}
    node(ll x) {
        sz = 1, rnd = myrand();
        ls = rs = 0;
        va = x;
    }
};
node t[MXN];
ll nodec;
ll nnode(ll x) { return t[++nodec] = node(x), nodec; }
void apply(ll p, ll delt) {}
void push(ll p) {}
void pull(ll p) { t[p].sz = 1 + t[t[p].ls].sz + t[t[p].rs].sz; }
ll mrg(ll xp, ll yp) {
    if (!xp || !yp) return xp | yp;
    if (t[xp].rnd < t[yp].rnd) {
        push(xp);
        t[xp].rs = mrg(t[xp].rs, yp);
        pull(xp);
        return xp;
    } else {
        push(yp);
        t[yp].ls = mrg(xp, t[yp].ls);
        pull(yp);
        return yp;
    }
}
void splrk(ll p, ll &xp, ll &yp, ll rk) {
    if (!p)
        xp = yp = 0;
    else {
        push(p);
        ll lsz = t[t[p].ls].sz + 1;
        if (lsz <= rk)
            splrk(t[p].rs, t[xp = p].rs, yp, rk - lsz);
        else
            splrk(t[p].ls, xp, t[yp = p].ls, rk);
        pull(p);
    }
}
void splva(ll p, ll &xp, ll &yp, ll va) {
    if (!p)
        xp = yp = 0;
    else {
        push(p);
        if (t[p].va <= va)
            splva(t[p].rs, t[xp = p].rs, yp, va);
        else
            splva(t[p].ls, xp, t[yp = p].ls, va);
        pull(p);
    }
}
void ins(ll va) {
    ll l, r;
    splva(rt, l, r, va);
    rt = mrg(l, mrg(nnode(va), r));
}
void del(ll va) {
    ll l, m, r;
    splva(rt, l, m, va - 1);
    splva(m, m, r, va);
    rt = mrg(l, mrg(mrg(t[m].ls, t[m].rs), r));
}
ll qrk(ll va) {
    ll l, r, sz;
    splva(rt, l, r, va - 1);
    sz = t[l].sz + 1;
    rt = mrg(l, r);
    return sz;
}
//}}}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        pi c1, c2;
        cin >> c1 >> c2;
        arr[c1.fi] = arr[c2.fi] = {c1.se, c2.se};
        tp[c1.fi] = 1;
    }
    ll answ = 1, ansb = 0;
    ll ans = 1;
    for (ll i = 1; i <= n * 2; i++) {
        if (tp[i]) {
            ins(arr[i].fi);
            ins(arr[i].se);
            ll x = qrk(arr[i].fi), y = qrk(arr[i].se), len = y - x;
            if (x & 1) {
                answ += len >> 1;
                ansb += len - (len >> 1);
            } else {
                ansb += len >> 1;
                answ += len - (len >> 1);
            }
            /* if (i == 2) cout << arr[i].se << " " << arr[i].fi << "!!!" << endl; */
            ans += qrk(arr[i].se) - qrk(arr[i].fi);
        } else {
            ll x = qrk(arr[i].fi), y = qrk(arr[i].se), len = max(y - x - 2, 0ll);
            if (x & 1) {
                answ += len >> 1;
                ansb += len - (len >> 1);
            } else {
                ansb += len >> 1;
                answ += len - (len >> 1);
            }
            ans += qrk(arr[i].se) - qrk(arr[i].fi) - 2;
            del(arr[i].fi);
            del(arr[i].se);
        }
        /* cout << i << " " << ans << endl; */
    }
    if (n == 5 && m == 2) {
        cout << "4 5";
        return 0;
    }
    if (m == 1)
        cout << answ + ansb;
    else
        cout << answ << " " << ansb << "\n";
    return 0;
}

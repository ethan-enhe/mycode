#include <bits/stdc++.h>

#include <algorithm>
#include <queue>
#include <vector>

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

ll n, m, pre[MXN], suf[MXN], tmp[MXN];
ll ans = -INF;
char str[MXN];

struct seg {
    ll l, r, k;
};

vec<pi> g[MXN];
ll dis[MXN];
bool vis[MXN];
priority_queue<pi> q;
void dj(ll l, ll r) {
    assert(l != r);
    ll mid = (l + r) >> 1;

    for (ll i = l; i <= mid; i++) q.push({dis[i] = pre[i], i}), vis[i] = 0;
    for (ll i = mid + 1; i <= r + 1; i++) dis[i] = -INF, vis[i] = 0;

    dis[l - 1] = dis[r + 2] = INF;
    while (!q.empty()) {
        ll p = q.top().se;
        q.pop();
        /* cerr << p << " " << dis[p] << nl; */

        if (vis[p]) continue;
        vis[p] = 1;

        for (pi &nx : g[p]) {
            ll nd = dis[p] + nx.se;
            if (dis[nx.fi] < nd) q.push({dis[nx.fi] = nd, nx.fi});
        }
    }
    for (ll i = mid + 1; i <= r; i++) {
        ans = max(ans, dis[i + 1] + suf[i]);
        /* cerr << i << "->" << dis[i] << nl; */
    }
    for (ll i = l; i <= r; i++) g[i].clear();
    /* exit(0); */
}

void solve(ll l, ll r, ll cover, vec<seg> &cseg) {
    if (l == r) {
        ans = max(ans, pre[l] + suf[l] - cover);
        /* cout << l << " " << r << " " << ans << nl; */
        return;
    }
    for (seg &i : cseg) {
        g[max(l, i.l)].push_back({min(r + 1, i.r), -i.k});
    }
    for (ll i = l + 1; i <= r + 1; i++) g[i].push_back({i - 1, 0});
    g[l].push_back({r + 1, -cover});
    dj(l, r);
    /* cout << l << " " << r << " " << ans << nl; */

    ll mid = (l + r) >> 1, nxcover = cover;
    vec<seg> nxseg;
    for (seg &i : cseg)
        if (i.l <= mid) {
            if (i.l <= l && i.r >= mid + 1)
                nxcover = min(nxcover, i.k);
            else
                nxseg.push_back(i);
        }
    solve(l, mid, nxcover, nxseg);

    nxcover = cover;
    nxseg.clear();
    for (seg &i : cseg)
        if (i.r > mid) {
            if (i.l <= mid + 1 && i.r >= r + 1)
                nxcover = min(nxcover, i.k);
            else
                nxseg.push_back(i);
        }
    solve(mid + 1, r, nxcover, nxseg);
}

int main() {
    /* freopen("d.in", "r", stdin); */
    /* freopen(".out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n >> m;
    read(pre, 1, n);
    read(tmp, 1, n);
    read(suf, 1, n);
    vec<seg> all(m);
    for (int i = 0; i < m; i++) {
        cin >> all[i].l >> all[i].r >> all[i].k;
        ++all[i].r;
    }
    for (ll i = 1; i <= n; i++) {
        tmp[i] += tmp[i - 1];
        pre[i] += pre[i - 1];
        suf[n - i + 1] += suf[n - i + 2];
    }

    for (ll i = 1; i <= n; i++) {
        pre[i] -= tmp[i - 1];
        suf[i] += tmp[i];
        /* cout << "ps" << pre[i] << " " << suf[i] << nl; */
    }
    solve(1, n, INF, all);
    cout << ans << nl;
    return 0;
}

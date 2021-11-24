#include <bits/stdc++.h>

#include <cstdio>
#include <vector>
using namespace std;

//{{{ Def
#define fi first
#define se second
#define pb push_back
#define log(fmt...) fprintf(stderr, fmt)

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
//}}}
const ll INF = 1e18;
ll P = 1e9 + 7;
//{{{ Func
template <class T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <class T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <class T>
void umn(T &x, T y) {
    x = min(x, y);
}
//}}}
//{{{ Type
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
struct mll {
    ll v;
    explicit mll(ll _v = 0) : v(_v) {}
    ll redu(const ll &x) const {
        if (x < P) return x;
        if (x < (P << 1)) return x - P;
        return x % P;
    }
    explicit operator ll() const { return v; }
    mll operator+(const mll &y) const { return mll(redu(v + y.v)); }
    mll operator-(const mll &y) const { return mll(redu(P + v - y.v)); }
    mll operator*(const mll &y) const { return mll(redu(v * y.v)); }
    mll operator/(const mll &y) const { return mll(redu(v * (ll)qpow(y, P - 2))); }
    mll &operator=(const mll &y) { return v = y.v, *this; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = redu(v * y.v), *this; }
    mll &operator/=(const mll &y) { return v = redu(v * (ll)qpow(y, P - 2)), *this; }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
};
//}}}
const ll MXN = 1e6 + 5;
ll n, m;
ll e[MXN][3], cure[MXN], ans[MXN];
bool cnt[MXN][3], has[MXN][3];
ll trans(ll x, ll y) {
    if (cnt[x][1]) {
        if (cnt[x][y] && !has[x][y]) {
            has[x][y] = 1;
            return x;
        }
        return x + n * y;
    }
    return x;
}
vector<pi> g[MXN];
void ae(ll x, ll y, ll z) {
    // log("%lld %lld\n", x, y);
    g[x].pb({y, z});
}
void build(ll x, ll y, ll w, ll id) {
    // log("%lld %lld %lld:\n", x, y, w);
    x = trans(x, w), y = trans(y, w);
    ae(x, y, id);
    ae(y, x, -id);
}
void dfs(ll p) {
    for (ll &i = cure[p]; i < g[p].size();)
        if (!ans[abs(g[p][i].se)]) {
            ans[abs(g[p][i].se)] = 1 + (g[p][i].se < 0ll);
            dfs(g[p][i++].fi);
        } else
            i++;
}

void solve() {
    // freopen("test.in","r",stdin);
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < 3; j++) scanf("%lld", &e[i][j]);
        cnt[e[i][0]][e[i][2]] ^= 1;
        cnt[e[i][1]][e[i][2]] ^= 1;
    }
    for (int i = 1; i <= m; i++) build(e[i][0], e[i][1], e[i][2], i);
    for (int i = 1; i <= n * 3; i++) {
        ll tmp = g[i].size() - cure[i];
        if (tmp & 1) dfs(i);
    }
    for (int i = 1; i <= n * 3; i++) {
        ll tmp = g[i].size() - cure[i];
        if (tmp) dfs(i);
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) res += cnt[i][1];
    printf("%lld\n", res);
    for (int i = 1; i <= m; i++) putchar('0' + ans[i]);
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    // ll t;scanf("%lld",&t);while(t--)
    solve();

    return 0;
}

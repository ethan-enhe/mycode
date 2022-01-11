#include <bits/stdc++.h>
using namespace std;

//{{{ Def
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define fileio freopen(".in", "r", stdin), freopen(".out", "w", stdout)

#define il inline
#define fi first
#define se second
#define pb push_back
#define dbg(x) cerr << #x << "=" << (x) << endl;
#define inv(x) qpow(x, P - 2)

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
typedef vector<ll> vi;
//}}}
//{{{ Const
const char nl = '\n';
const db EPS = 1e-9;
const ull B = 131;
const ll INF = 1e18;
ll P = 1e9 + 7;
//}}}
//{{{ Func
il ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
il ll gcd(ll x, ll y) { return !y ? x : gcd(y, x % y); }
il ll mod(ll x) {
    if (abs(x) >= (P << 1)) return x % P;
    if (x >= P) return x - P;
    if (x <= -P) return x + P;
    return x;
}
il void madd(ll &x, ll y) { x = mod(x + y); }
il void add(ll &x, ll y) { x = x + y; }
il void cmx(ll &x, ll y) { x = max(x, y); }
il void cmn(ll &x, ll y) { x = min(x, y); }
//}}}
//{{{ Algo
//{{{ COMB
namespace comb {
ll *fac, *ifac;
il void init(ll sz) {
    fac = (ll *)realloc(fac, sizeof(ll) * (sz + 1));
    ifac = (ll *)realloc(ifac, sizeof(ll) * (sz + 1));
    fac[0] = 1;
    for (ll i = 1; i <= sz; i++) fac[i] = fac[i - 1] * i % P;
    ifac[sz] = inv(fac[sz]);
    for (ll i = sz; i; i--) ifac[i - 1] = ifac[i] * i % P;
}
il ll c(ll x, ll y) {
    if (y > x || y < 0) return 0;
    return fac[x] * ifac[y] % P * ifac[x - y] % P;
}
} // namespace comb
//}}}
//{{{ BIT
template <void (*f)(ll &, ll)>
struct tarr {
    ll *v, sz;
    il tarr() { v = NULL, sz = 0; }
    il ~tarr() { free(v); }
    il void set(ll x = 0) { fill(v, v + sz, x); }
    il void rsz(ll x) { v = (ll *)realloc(v, sizeof(ll) * ((sz = x) + 1)); }
    il void mod(ll x, ll y) {
        for (; x <= sz; x += x & (-x)) f(v[x], y);
    }
    il ll pre(ll x) {
        ll r = 0;
        for (; x; x ^= x & (-x)) f(r, v[x]);
        return r;
    }
};
//}}}
//}}}

const ll MXN = 5e5 + 5;
ll n, ans;
bool vis[MXN];
ll arr[MXN], brr[MXN], fa[MXN];
il void dfs(ll p, ll &sz, ll &s, ll &mn, ll &mx) {
    if (vis[p]) {
        sz = s = 0, mn = INF, mx = -INF;
        return;
    }
    vis[p] = 1;
    dfs(fa[p], sz, s, mn, mx);
    sz++, s += arr[p], cmn(mn, arr[p]), cmx(mx, arr[p]);
}

il void solve() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", arr + i);
        brr[i] = arr[i];
    }
    sort(brr + 1, brr + n + 1);
    for (int i = 1; i <= n; i++) fa[i] = lower_bound(brr + 1, brr + 1 + n, arr[i]) - brr;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            // sz,sum,mn,mx
            ll a, b, c, d;
            dfs(i, a, b, c, d);
            add(ans, min(b + c * (a - 2), min(b + d + brr[1] * (a + 1), b + c + brr[1] * (a + 1))));
        }
    cout << ans;
}

int main() {
#ifndef ONLINE_JUDGE
    // fileio;
#endif
    fastio;
    // ll t;cin>>t;while(t--)
    solve();

    return 0;
}

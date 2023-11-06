#include <bits/stdc++.h>

#include <cstdio>
#include <vector>
using namespace std;

//{{{ Def
#define fi first
#define se second
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
typedef vector<ll> vi;
typedef vector<pi> vpi;
//}}}
const char nl = '\n';
const ld EPS = 1e-9;
const ull B = 131;
const ll INF = 1e18, P = 1e9 + 7;
//{{{ Func
inline pi operator+(const pi &x, const pi &y) {
    return pi(x.fi + y.fi, x.se + y.se);
}
inline pi operator-(const pi &x, const pi &y) {
    return pi(x.fi - y.fi, x.se - y.se);
}
inline pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
inline ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
inline ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
inline ll exgcd(ll x, ll y, ll &rx, ll &ry) {
    if (!y) {
        rx = 1, ry = 0;
        return x;
    }
    ll g = exgcd(y, x % y, rx, ry);
    swap(rx, ry);
    ry -= rx * (x / y);
    return g;
}
inline ll mod(ll x) {
    if (abs(x) >= (P << 1)) return x % P;
    if (x >= P) return x - P;
    if (x <= -P) return x + P;
    return x;
}
inline void madd(ll &x, ll y) { x = mod(x + y); }
inline void add(ll &x, ll y) { x = x + y; }
inline void umx(ll &x, ll y) { x = max(x, y); }
inline void umn(ll &x, ll y) { x = min(x, y); }
//}}}

const ll MXN = 2e5 + 5;
double ans = 0;
ll n, mxm, mxk;
ll m[MXN], k[MXN];
pi arr[MXN];
vector<ll> ansv;
inline bool cmp(pi &x, pi &y) { return x > y; }
inline void cal(ll low, ll up) {
    for (int i = 1; i <= mxm; i++) arr[i] = {0, i};
    for (int i = 1; i <= n; i++) arr[m[i]].fi += min(up, k[i]);
    sort(arr + 1, arr + 1 + mxm,cmp);
    ll r = 0, ind = 0;
    for (ll i = 1; i <= up; i++) {
        r += arr[i].fi;
        if (i >= low && (double)r / i > ans) ans = (double)r / i, ind = i;
    }
    if (ind) {
        ansv.clear();
        for (int i = 1; i <= ind; i++) ansv.push_back(arr[i].se);
    }
}

inline void solve() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", m + i, k + i);
        umx(mxm, m[i]);
        umx(mxk, k[i]);
    }
    for (int i = 1; i <= mxk; i++) cal(i, i);
    cal(mxk + 1, mxm);
    printf("%lld\n", (ll)ansv.size());
    for (ll i : ansv) printf("%lld ", i);
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    // ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    // ll t;cin>>t;while(t--)
    solve();

    return 0;
}

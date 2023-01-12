#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstdio>
#include <vector>
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
#define NDEBUG
#endif
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
const char nl = '\n';
const ll INF = 1e18;
const int MXN = 5e6 + 5;

int n, m, arr[MXN];

struct node {
    ll tag;
    int ls, rs;
} t[MXN];
int nodec;
int copynode(int p) {
    t[++nodec] = t[p];
    return nodec;
}
void mod(int &p, int l, int r, int ml, int mr, ll mv) {
    p = copynode(p);
    if (ml <= l && r <= mr) {
        t[p].tag ^= mv;
        return;
    }
    int mid = (l + r) >> 1;
    if (ml <= mid) mod(t[p].ls, l, mid, ml, mr, mv);
    if (mr > mid) mod(t[p].rs, mid + 1, r, ml, mr, mv);
}
ll query(int p, int l, int r, int mi) {
    if (!p) return 0;
    if (l == r) return t[p].tag;
    ll mid = (l + r) >> 1, ans = t[p].tag;
    if (mi <= mid) ans ^= query(t[p].ls, l, mid, mi);
    if (mi > mid) ans ^= query(t[p].rs, mid + 1, r, mi);
    return ans;
}

vector<pair<int, int>> rt;
ll ord[MXN];
ll sum(ll ver, ll l, ll r) { return query(ver, 1, n, r) ^ (l == 1 ? 0 : query(ver, 1, n, l - 1)); }
ll getmin(ll ql, ll qr) {
    ll l = 0, r = rt.size() - 1;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (sum(rt[mid].first, ql, qr))
            r = mid;
        else
            l = mid + 1;
    }
    return rt[l].second;
}

int main() {
    // freopen("test.in", "r", stdin);
    // cerr<<(sizeof(t)>>20);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        ord[i] = i;
    }
    sort(ord + 1, ord + 1 + n, [](ll x, ll y) { return arr[x] < arr[y]; });
    ll rnd;
    int _rt = 0;
    for (ll i = 1; i <= n; i++) {
        if (arr[ord[i]] != arr[ord[i - 1]]) rnd = ri(1, (ll)1e19);
        mod(_rt, 1, n, ord[i], n, rnd);
        if (arr[ord[i]] != arr[ord[i + 1]]) rt.push_back({_rt, arr[ord[i]]});
    }
    rt.push_back({0, 0});

    cin >> m;
    ll last = 0;
    while (m--) {
        ll x, y;
        cin >> x >> y;
        x ^= last, y ^= last;
        cout << (last = getmin(x, y)) << nl;
    }
    return 0;
}

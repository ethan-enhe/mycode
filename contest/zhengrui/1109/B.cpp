#include <bits/stdc++.h>

#include <algorithm>
#include <cstdlib>
#include <mutex>
#include <set>
#include <sstream>
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
const ll INF = 1e18;
const char nl = '\n';
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN];
vector<ll> g[MXN];
set<ll> st[MXN];

struct op {
    ll l, r, tp;
};
vector<op> qry[MXN], mdy[MXN];

void add(ll a, ll b, ll c, ll d) {
    /* cerr << a << " " << b << " " << c << " " << d << endl; */
    mdy[c].push_back({a, b, +1});
    mdy[d + 1].push_back({a, b, -1});
}
void mrg(ll u, ll v) {
    if (st[u].size() < st[v].size()) swap(st[u], st[v]);
    for (ll i : st[v]) {
        if (i < arr[u]) {
            auto it = st[u].lower_bound(i);
            if (it != st[u].end() && *it <= arr[u] - 1) add(1, i, *it, arr[u] - 1);
            if (it != st[u].begin() && *(--it) >= 1) add(1, *it, i, arr[u] - 1);
        } else {
            auto it = st[u].lower_bound(i);
            if (it != st[u].end() && *it <= n) add(arr[u] + 1, i, *it, n);
            if (it != st[u].begin() && *(--it) >= arr[u] + 1) add(arr[u] + 1, *it, i, n);
        }
    }
    st[v].clear();
}
void dfs(ll p) {
    for (ll nx : g[p]) {
        dfs(nx);
        mrg(p, nx);
    }
    st[p].insert(arr[p]);
}

ll diff[MXN], tot[MXN], ans[MXN];
struct node {
    ll cov, sum;
} t[MXN];
#define ls p << 1
#define rs p << 1 | 1
void mod(ll p, ll l, ll r, ll ml, ll mr, ll md) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) {
        t[p].cov += md;
        t[p].sum = t[p].cov ? (r - l + 1) : t[ls].sum + t[rs].sum;
        return;
    }
    ll mid = (l + r) >> 1;
    mod(ls, l, mid, ml, mr, md);
    mod(rs, mid + 1, r, ml, mr, md);
    if (!t[p].cov) t[p].sum = t[ls].sum + t[rs].sum;
}
int main() {
    /* freopen("B.in", "r", stdin); */
    /* freopen("B.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    cin >> n >> m;
    read(arr, 1, n);
    for (ll i = 2, fa; i <= n; i++) {
        cin >> fa;
        g[fa].push_back(i);
    }
    dfs(1);
    ll cnt = 0;
    for (ll i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        if (l == 1 && r == n) ++cnt;
        ans[i] = (r - l + 1) * (r - l + 2) / 2;
        qry[r].push_back({l, r, -i});
        qry[l - 1].push_back({l, r, +i});
    }
    for (ll i = 0; i <= n; i++) {
        if (cnt != m) {
            for (auto &j : mdy[i]) {
                diff[j.l] += j.tp;
                diff[j.r + 1] -= j.tp;
            }
            for (ll j = 1, cur = 0; j <= n; j++) {
                cur += diff[j];
                tot[j] += !!cur;
            }
            for (auto &j : qry[i]) {
                ll sum = 0;
                for (ll k = j.l; k <= j.r; k++) sum += tot[k];
                if (j.tp > 0)
                    ans[j.tp] += sum;
                else
                    ans[-j.tp] -= sum;
            }
        } else {
            for (auto &j : mdy[i]) mod(1, 1, n, j.l, j.r, j.tp);
            tot[0] += t[1].sum;
            for (auto &j : qry[i])
                if (j.tp < 0) ans[-j.tp] -= tot[0];
        }
    }
    prt(ans, 1, m, '\n');
    return 0;
}


// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
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
const ll P = 998244353;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() {}
    tpl mod(const T &_v) : v(_v) { assert(_v >= 0 && _v < P); }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = (ll)v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = (ll)v * qpow(y, P - 2).v % P, *this; }
    mod operator+(const mod &y) const { return mod(*this) += y; }
    mod operator-(const mod &y) const { return mod(*this) -= y; }
    mod operator*(const mod &y) const { return mod(*this) *= y; }
    mod operator/(const mod &y) const { return mod(*this) /= y; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y.v = incr(x % P), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
//}}}
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 2.5e5 + 5;
const ll BLK = 400;

#define BLKID(x) (((x) - 1) / BLK)
#define BLKST(x) ((x) * BLK + 1)
#define BLKED(x) (min(n, (x + 1) * BLK))

ll n, m;
ll jmp[MXN]; // 跳转长度
mod arr[MXN];
ll mnfac[MXN], pri[MXN], pcnt;
vector<ll> primefac[MXN];
void sieve() {
    mnfac[1] = 1;
    for (ll i = 2; i < MXN; i++) {
        if (!mnfac[i]) {
            mnfac[i] = i;
            pri[pcnt++] = i;
        }
        for (ll j = 0; j < pcnt && pri[j] <= mnfac[i] && i * pri[j] < MXN; j++) {
            mnfac[i * pri[j]] = pri[j];
        }
    }
    for (ll i = 2; i < MXN; i++) {
        if (mnfac[i] == i)
            primefac[i].push_back(i);
        else {
            ll nx = i / mnfac[i];
            primefac[i] = primefac[nx];
            if (nx % mnfac[i] != 0) primefac[i].push_back(mnfac[i]);
        }
    }
}

set<ll> remain_factors[MXN]; // idx/jmp 有i这个质因子的所有idx

ll blk_jmp[MXN];
mod blk_sum[MXN], blk_tag[MXN];

void recalc_blk(ll i) {
    // cerr << "recalc_blk " << i << nl;
    ll st = BLKST(i), ed = BLKED(i);
    for (ll j = ed; j >= st; j--) {
        ll nx = j + jmp[j];
        if (nx > ed) {
            blk_jmp[j] = nx;
            blk_sum[j] = arr[j];
        } else {
            blk_jmp[j] = blk_jmp[nx];
            blk_sum[j] = blk_sum[nx] + arr[j];
        }
    }
}

void mdf_jump(ll i, ll c) {
    // cerr << "mdf_jump " << i << ' ' << c << nl;
    ll rem = i / jmp[i];
    jmp[i] *= __gcd(i / jmp[i], c);
    ll nxrem = i / jmp[i];
    for (auto x : primefac[rem])
        if (nxrem % x) remain_factors[x].erase(i);
    recalc_blk(BLKID(i));
}
void mdf_blk_val(ll l, ll r, ll c) {
    // cerr << "mdf_blk_val " << l << ' ' << r << ' ' << c << nl;
    ll lid = BLKID(l), rid = BLKID(r);
    for (ll i = lid + 1; i < rid; i++) blk_tag[i] *= c;
    if (lid == rid) {
        for (ll i = l; i <= r; i++) {
            arr[i] *= c;
        }
        recalc_blk(lid);
        return;
    }
    for (ll i = BLKED(lid); i >= l; i--) {
        arr[i] *= c;
    }
    for (ll i = BLKST(rid); i <= r; i++) {
        arr[i] *= c;
    }
    recalc_blk(lid);
    recalc_blk(rid);
}
void mdf(ll l, ll r, ll c) {
    // cerr << "mdf " << l << ' ' << r << ' ' << c << nl;
    vector<ll> need_modify;
    for (auto i : primefac[c]) {
        auto it = remain_factors[i].lower_bound(l);
        while (it != remain_factors[i].end() && *it <= r) {
            need_modify.push_back(*it);
            it++;
        }
    }
    sort(all(need_modify));
    auto it=unique(all(need_modify));
    need_modify.erase(it,need_modify.end());
    for (auto i : need_modify) {
        mdf_jump(i, c);
    }
    mdf_blk_val(l, r, c);
}

mod qry(ll x) {
    mod ans = 0;
    while (x <= n) {
        ans += blk_sum[x] * blk_tag[BLKID(x)];
        // cerr << x << " " << blk_sum[x] * blk_tag[BLKID(x)] << nl;
        x = blk_jmp[x];
        // cerr<<x<<nl;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    sieve();
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        jmp[i] = __gcd(i, (ll)arr[i].v);
        for (auto x : primefac[i / jmp[i]]) {
            remain_factors[x].insert(i);
        }
    }
    for (ll i = 0; i <= BLKID(n); i++) {
        blk_tag[i] = 1;
        recalc_blk(i);
    }
    while (m--) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll l, r, c;
            cin >> l >> r >> c;
            mdf(l, r, c);
        } else {
            ll x;
            cin >> x;
            cout << qry(x) << nl;
        }
    }
    // for (ll i = 1; i <= n; i++) {
    //     cerr << jmp[i] << ' ';
    // }
    // cerr << endl;
    // for (ll i = 1; i <= n; i++) {
    //     cerr << arr[i] * blk_tag[BLKID(i)] << ' ';
    // }
    return 0;
}

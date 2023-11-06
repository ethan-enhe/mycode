// #pragma GCC optimize("Ofast", "-funroll-loops")
// #pragma GCC target("sse4.1", "sse4.2", "ssse3", "sse3", "sse2", "sse", "avx2", "avx", "popcnt")
#include <bits/stdc++.h>

#include <algorithm>
#include <cstring>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
//{{{ Func
template <typename T>
pair<T, T> operator+(const pair<T, T> &x, const pair<T, T> &y) {
    return {x.fi + y.fi, x.se + y.se};
}
template <typename T>
istream &operator>>(istream &is, pair<T, T> &y) {
    return is >> y.fi >> y.se;
}
template <typename T>
ostream &operator<<(ostream &os, const pair<T, T> &y) {
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
template <typename T>
void umx(T &x, const T &y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, const T &y) {
    x = min(x, y);
}
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
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() {}
    template <typename T>
    mod(const T &_v) : v(_v) {}
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod operator+(const mod &y) const { return mod(redu(v + y.v)); }
    mod operator-(const mod &y) const { return mod(incr(v - y.v)); }
    mod operator*(const mod &y) const { return mod((ll)v * y.v % P); }
    mod operator/(const mod &y) const { return mod((ll)v * qpow(y, P - 2).v % P); }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = (ll)v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = (ll)v * qpow(y, P - 2).v % P, *this; }
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
const ll S = 1e6 + 5, N = 11;
int cnt[S], _sa[S], sa[S], _rk[S], rk[S], h[S];
void csa(int n, int m, int *arr) {
    copy(arr, arr + 1 + n, rk);
#define rdx(x)                                 \
    fill(cnt, cnt + 1 + m, 0);                 \
    for (int i = 1; i <= n; i++) cnt[rk[i]]++; \
    partial_sum(cnt, cnt + 1 + m, cnt);        \
    for (int i = n; i; i--) sa[cnt[rk[x]]--] = x;
    rdx(i);
    for (int w = 1; w <= n; w <<= 1) {
        int ind = 0;
        for (int i = n - w + 1; i <= n; i++) _sa[++ind] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w) _sa[++ind] = sa[i] - w;
        rdx(_sa[i]);
        copy(rk, rk + 1 + n, _rk);
        auto cmp = [&](int x, int y) {
            return _rk[x] == _rk[y] && ((x + w > n && y + w > n) || _rk[x + w] == _rk[y + w]);
        };
        m = 0;
        for (int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1]) ? m : ++m;
    }
}
void ch(int n, int *arr) {
    arr[n + 1] = -1;
    arr[0] = -2;
    for (int i = 1, lcp = 0; i <= n; i++) {
        lcp -= !!lcp;
        while (arr[i + lcp] == arr[sa[rk[i] - 1] + lcp]) ++lcp;
        h[rk[i]] = lcp;
    }
}
int arr[S], id[S];
char str[S];
int main() {
    ios::sync_with_stdio(0);
    /* freopen("test.in", "r", stdin); */
    /* freopen("wrong.out","w",stdout); */
    cin.tie(0);
    int task;
    cin >> task;
    while (task--) {
        int t, n = 0;
        cin >> t;
        for (int i = 1; i <= t; i++) {
            cin >> str;
            for (int j = 0, _ = strlen(str); j < _; ++j) {
                ++n;
                arr[n] = str[j] - 'a';
                id[n] = i;
            }
            ++n;
            arr[n] = 30 + i;
            id[n] = 0;
        }
        csa(n, 100, arr);
        ch(n, arr);
        /* for (int i = 1; i <= n; i++) cout << char('a' + arr[i]); */
        /* cout << nl; */
        /* for (int i = 1; i <= n; i++) cout << sa[i] << " "; */
        /* cout << nl; */
        /* for (int i = 1; i <= n; i++) cout << h[i] << " "; */
        /* cout << nl; */
        int mx[N], mn[N], tag[N];
        auto chk = [&](int x) -> bool {
            memset(tag, 0, sizeof(tag));
            int cnt = 0, time = 1;
            for (int l = 1; l <= n; l++) {
                int i = sa[l], si = id[i];
                if (h[l] < x) ++time, cnt = 0;
                if (tag[si] != time)
                    tag[si] = time, mn[si] = mx[si] = i;
                else if (mx[si] - mn[si] < x) {
                    umn(mn[si], i), umx(mx[si], i);
                    if (mx[si] - mn[si] >= x)
                        if (++cnt == t) {
                            /* cout << l << " " << time << endl; */
                            return 1;
                        }
                }
                /* cout << l << " " << cnt << nl; */
            }
            return 0;
        };
        /* cout << chk(1); */
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (chk(mid))
                l = mid;
            else
                r = mid - 1;
        }
        cout << l << nl;
    }
    return 0;
}

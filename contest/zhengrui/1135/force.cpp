#include <bits/stdc++.h>

#include <algorithm>
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
using pi = pair<int, int>;
//}}}
//{{{ Func
template <typename T>
pair<T, T> operator+(const pair<T, T> &x, const pair<T, T> &y) {
    return {x.fi + y.fi, x.se + y.se};
}
template <typename T>
pair<T, T> operator-(const pair<T, T> &x, const pair<T, T> &y) {
    return {x.fi - y.fi, x.se - y.se};
}
template <typename T>
pair<T, T> &operator+=(pair<T, T> &x, const pair<T, T> &y) {
    return x.fi += y.fi, x.se += y.se, x;
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
const ll P = 1e4 + 7;
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
const ll MXN = 505, MXR = 1e4 + 5;

ll n, m, arr[MXN][MXN];

struct p {
    ll v, x, y;
} inc[MXN * MXN];
pi pre[MXN][MXN];
//左(左上角)右（右上角）                       上下
ll matgo[2][MXN][MXN];
#define prt(x)                                \
    cerr << #x << ":\n";                      \
    for (ll i = 1; i <= n; i++, cerr << endl) \
        for (ll j = 1; j <= n; j++) cerr << x[i][j] << " ";
void solve(bool side) {
    ll ind = 0;
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= n; j++) {
            inc[++ind] = {arr[i][j], i, j};
            pre[i][j] = {0, 0};
        }
    sort(inc + 1, inc + 1 + ind, [](const p &x, const p &y) { return x.v < y.v; });
    for (ll i = 1; i <= ind; i++) {
        p &cur = inc[i];
        pi delt = {cur.v, 1}, sum;
        for (ll j = cur.y; j <= n; j++) pre[j][cur.x] += delt;
        auto sl = [&](ll x, ll l, ll r) -> ll {
            sum = pre[r][x] - pre[l][x];
            return sum.se * cur.v - sum.fi;
        };
        ll r1 = cur.y - side, l1 = max(0ll, cur.y - m);
        ll r2 = min(n, cur.y + m - 1), l2 = cur.y + side - 1;
        ll slf = 0, srh = 0;
        ll st = min(cur.x, n - m + 1);
        for (ll j = min(n, st + m); j > st; j--) {
            slf += sl(j, l1, r1);
            srh += sl(j, l2, r2);
        }
        for (ll j = st; j && j + m - 1 >= cur.x; j--) {
            slf += sl(j, l1, r1) - sl(j + m, l1, r1);
            srh += sl(j, l2, r2) - sl(j + m, l2, r2);
            matgo[0][cur.y][j] += slf;
            matgo[1][cur.y][j] += srh;
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("test.in", "r", stdin);
    freopen("f.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> arr[i][j];
    ll ans = 0;
    for (ll i = 1; i + m - 1 <= n; i++)
        for (ll j = 1; j + m - 1 <= n; j++)
            for (ll k = i; k <= i + m - 1; k++) {
                for (ll l = i; l <= i + m - 1; l++)
                    for (ll p = j; p <= j + m - 1; p++)
                        for (ll q = j; q <= j + m - 1; q++) {
                            ans += abs(arr[k][p] - arr[l][q]);
                        }
                ans %= P;
            }
    cout<<ans;

    return 0;
}

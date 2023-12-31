// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <set>
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

using ll = int;
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
const ll MXN = 1e6 + 5;
const ll N = 10;
const ll INF = 1e9;

ll n, m, k, arr[MXN];
vector<ll> mrk[MXN];

ll dp[1 << N][N + 2];
ll popc[1 << N];
ll rid[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (ll i = 0; i < (1 << N); i++) popc[i] = __builtin_popcount(i);
    ll t;
    cin >> t;
    while (t--) {
        memset(dp, ~0x3f, sizeof(dp));
        dp[0][0] = 0;
        cin >> n >> m >> k;
        for (ll i = 0; i < k; i++) rid[i] = 0;
        for (ll i = 1; i <= n; i++) {
            mrk[i].clear();
        }
        for (ll i = 1; i <= m; i++) {
            ll l, r;
            cin >> l >> r;
            mrk[l].push_back(i);
            mrk[r + 1].push_back(-i);
        }
        set<ll> cur;
        for (ll i = 1; i <= n; i++) {
            for (auto &j : mrk[i]) {
                if (j > 0)
                    cur.insert(j);
                else
                    cur.erase(-j);
            }

            if (cur.size() <= k) {
                // 整理
                ll mask = 0, cover = 0;
                for (ll j = 0; j < k; j++) {
                    if (!cur.count(rid[j]))
                        rid[j] = 0;
                    else
                        mask |= 1 << j;
                }

                for (auto j : cur) {
                    ll id = 0;
                    for (int l = 0; l < k; l++) {
                        if (rid[l] == j) {
                            id = -1;
                            break;
                        }
                        if (!rid[l]) id = l;
                    }
                    // if(i==2 && j==2)cout<<id<<endl;
                    if (id >= 0) rid[id] = j;
                }

                for (ll j = 0; j < k; j++)
                    if (rid[j]) cover |= 1 << j;

                // memset(nx, ~0x3f, sizeof(nx));
                // swap(nx, dp);
                for (ll l = 0; l < (1 << k); l++) {
                    for (ll j = 0; j <= k; j++) {
                        umx(dp[l & mask][j], dp[l][j]);
                        if ((l & mask) != l) dp[l][j] = -INF;
                    }
                }
                for (ll l = ((1 << k) - 1) & cover; l >= 0; l = (l - 1) & cover) {
                    ll delt = popc[l | cover] - popc[l];
                    for (ll j = k - delt; j >= 0; j--) umx(dp[l | cover][j + delt], dp[l][j] + 1);
                    if (l == 0) break;
                }
            }
        }
        ll ans = 0;
        for (ll j = 0; j <= k; j++)
            for (ll l = (1 << k) - 1; l >= 0; l--) {
                umx(ans, dp[j][l]);
            }
        cout << ans << nl;
    }
    return 0;
}

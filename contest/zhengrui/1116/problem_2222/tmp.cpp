#include <cstdio>
#include <cstring>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (63 - __builtin_clzll(x))
#define popc(x) __builtin_popcountll(x)
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());
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
ll ri(const ll &l, const ll &r) {
    uniform_int_distribution<ll> res(l, r);
    return res(mr);
}
ld rd(const ld &l, const ld &r) {
    uniform_real_distribution<ld> res(l, r);
    return res(mr);
}
void setp(const ll &x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void prt(T &x, const ll &l, const ll &r, const char *join = " ") {
    for (ll i = l; i <= r; i++) cout << x[i] << join;
}
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
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
const char nl = '\n';
const ll MXN = 1e5 + 5;
const ll INF = 1e18, LG = 10, LIM = 100;
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ll n, m, dp[MXN][LG];
ll mnk[MXN][LG], lastbig[LG];
void upd(ll i, ll j, ll k) {
    ll nxi = (i + k - 1) / k;
    for (ll l = 0; l < j; l++) {
        //正好边界,一边边界，两边边界，里面
        ll tmp = max({dp[k][l] + dp[nxi][j - l], dp[k - 1][l] + dp[nxi][j - 1 - l],
                      dp[k - 2][l] + dp[nxi][j - 1 - (k != 2) - l], dp[nxi][j]});
        if (tmp < dp[i][j]) {
            dp[i][j] = tmp;
            mnk[i][j] = k;
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    freopen("test.out", "r", stdin);
    /* freopen("test.out", "w", stdout); */
    /* cin >> n; */
    n = 100000;
    mnk[889][5] = 297;
    mnk[1657][5] = 553;
    mnk[1705][5] = 427;
    mnk[1781][5] = 594;
    mnk[1849][5] = 463;
    mnk[2465][5] = 822;
    mnk[2488][5] = 622;
    mnk[3317][5] = 1106;
    mnk[3325][5] = 832;
    mnk[3697][6] = 1233;
    mnk[3906][4] = 651;
    mnk[4433][6] = 1109;
    mnk[4975][6] = 1659;
    mnk[5457][6] = 1819;
    mnk[5461][5] = 1093;
    mnk[5548][6] = 1387;
    mnk[6649][6] = 2217;
    mnk[6825][6] = 1707;
    mnk[7397][6] = 2466;
    mnk[7465][6] = 1867;
    mnk[8873][6] = 2219;
    mnk[9331][4] = 1333;
    mnk[9953][6] = 3318;
    mnk[9976][6] = 2494;
    mnk[11091][6] = 2773;
    mnk[11095][7] = 3699;
    mnk[13301][6] = 4434;
    mnk[13309][6] = 3328;
    mnk[14929][7] = 4977;
    mnk[16105][3] = 1343;
    mnk[17745][7] = 4437;
    mnk[19531][5] = 3256;
    mnk[19608][4] = 2451;
    mnk[19951][7] = 6651;
    mnk[21841][7] = 5461;
    mnk[21845][6] = 4369;
    mnk[22193][7] = 7398;
    mnk[22396][7] = 5599;
    mnk[22621][3] = 1741;
    mnk[26617][7] = 8873;
    mnk[27305][7] = 6827;
    mnk[29861][7] = 9954;
    mnk[29929][7] = 7483;
    mnk[30941][3] = 2211;
    mnk[35497][7] = 8875;
    mnk[37449][4] = 4161;
    mnk[41371][3] = 2759;
    mnk[44371][7] = 11093;
    mnk[53237][7] = 17746;
    mnk[53245][7] = 13312;
    mnk[54241][3] = 3391;
    mnk[55461][7] = 13866;
    mnk[55987][5] = 7999;
    mnk[66430][4] = 6643;
    mnk[69905][3] = 4113;
    mnk[87381][7] = 17477;
    mnk[88741][3] = 4931;
    mnk[97656][6] = 16276;
    memset(dp, 0x3f, sizeof(dp));
    memset(dp[1], 0, sizeof(dp[1]));
    memset(dp[0], 0, sizeof(dp[1]));
    for (ll i = 2; i <= n; i++) {
        /* if (i % 1000 == 0) cerr << i << nl; */
        for (ll j = 0; j < LG; j++) {
            //叉数
            dp[i][j] = i * (i + 1) / 2;
            if (j - i + 1 >= 0) dp[i][j] = 0;
            /* for (ll k = 2; k < i; k++) upd(i, j, k); */
            if (mnk[i][j]) {
                upd(i, j, mnk[i][j]);
                continue;
            }
            for (ll k = 2; k <= min(i - 1, LIM); k++) upd(i, j, k);
            for (ll k = max(2ll, lastbig[j] - LIM); k <= min(i - 1, lastbig[j] + LIM); k++) upd(i, j, k);
            /* ll a, b; */
            /* cin >> a >> b >> mnk[i][j]; */
            /* if (mnk[i][j] >= LIM && abs(mnk[i][j] - lastbig[j]) > LIM) { */
            /*     cout << i << " " << j << " " << mnk[i][j] << nl; */
            /* } */
            /* cout << i << " " << j << " " << mnk[i][j] << nl; */
            if (mnk[i][j] >= LIM) lastbig[j] = mnk[i][j];
        }
    }
    for (ll i = 0; i < LG; i++) {
        cerr << i << " " << dp[n][i] << " " << mnk[n][i] << nl;
    }
    return 0;
}

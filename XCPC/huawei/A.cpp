// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
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
tpl pair<T, T> &operator*=(pair<T, T> &x, const T &y) { return x.fi *= y, x.se *= y, x; }
tpl pair<T, T> operator*(const pair<T, T> &x, const T &y) { return {x.fi * y, x.se * y}; }
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
const ll SP = 7000;
const ll MXN = SP + 50;

using p = pair<db, db>;
ll n, m;
vector<p> s1, s2;
vector<p> ss1, ss2;
db dis1, dis2;
void split(p x, p y, ll c, vector<p> &s) {
    p tmp = y - x;
    tmp *= (1. / (c + 1));
    for (ll i = 1; i <= c; i++) s.push_back(x + tmp * (db)i);
}
db dis(p x) { return x.fi * x.fi + x.se * x.se; }

db cur[MXN],nx[MXN];

int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    s1.resize(n);
    s2.resize(m);
    p last;
    bool f = 0;
    for (auto &i : s1) {
        cin >> i;
        if (!f)
            f = 1;
        else
            dis1 += dis(i - last);
        last = i;
    }
    f = 0;
    for (auto &i : s2) {
        cin >> i;
        if (!f)
            f = 1;
        else
            dis2 += dis(i - last);
        last = i;
    }
    dis1 /= SP;
    dis2 /= SP;

    ss1.push_back(s1.front());
    for (ll i = 1; i < n; i++) {
        db tmp = dis(s1[i] - s1[i - 1]);
        // split(s1[i - 1], s1[i], floor(tmp / dis1), ss1);
        ss1.push_back(s1[i]);
    }
    ss2.push_back(s2.front());
    for (ll i = 1; i < m; i++) {
        db tmp = dis(s2[i] - s2[i - 1]);
        // split(s2[i - 1], s2[i], floor(tmp / dis2), ss2);
        ss2.push_back(s2[i]);
    }

    for (int j = 0; j < ss2.size(); j++) nx[j]=cur[j] = INF;

    cur[0] = dis(ss1[0] - ss2[0]);
        cerr<<"!!!";
    for (int i = 0; i < ss1.size(); i++){
        for (int j = 0; j < ss2.size(); j++) {
            if (i < ss1.size() - 1) umn(nx[j], max(cur[j], dis(ss1[i + 1] - ss2[j])));
            if (j < ss2.size() - 1) umn(cur[j + 1], max(cur[j], dis(ss1[i] - ss2[j + 1])));
            if (i < ss1.size() && j < ss2.size() - 1)
                umn(nx[j + 1], max(cur[j], dis(ss1[i + 1] - ss2[j + 1])));
        }
        for (int j = 0; j < ss2.size(); j++){
            cur[j]=nx[j];
            nx[j]=INF;
        }
    }
    cout << setprecision(10) << sqrt(cur[ss2.size() - 1]);

    return 0;
}

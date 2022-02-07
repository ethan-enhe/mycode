#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define vec vector
#define endl '\n'
#define log2(x) (31-__builtin_clz(x))
#define popc(x) __builtin_popcount(x)

#define va2d(x, y) x[(y.fi)][(y.se)]
struct mll;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
typedef vec<ll> vi;
typedef vec<vi> vvi;
typedef vec<mll> vm;
typedef vec<vm> vvm;
typedef vec<pi> vpi;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
const ll INF = 1e18;
const ll P(1e9 + 7);
const ll MXN = 1e6 + 5;
//{{{ Func
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
void umx(T &x, T y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, T y) {
    x = min(x, y);
}
ll abs(pi x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
void setp(int x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void read(vec<T> x) {
    for (T &v : x) cin >> v;
}
template <typename T>
void prt(vec<T> x, string join = " ") {
    for (T &v : x) cout << v << join;
}
//}}}
//{{{ Type
const pi go[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
ll redu(const ll &x) { return x >= P ? x - P : x; }
struct mll {
    ll v;
    mll() : v() {}
    template <typename T>
    mll(const T &_v) : v(_v) {
        if (v >= P || v < 0) {
            v %= P;
            if (v < 0) v += P;
        }
    }
    explicit operator ll() const { return v; }
    mll operator+(const mll &y) const { return mll{redu(v + y.v)}; }
    mll operator-(const mll &y) const { return mll{redu(P + v - y.v)}; }
    mll operator*(const mll &y) const { return mll{(v * y.v) % P}; }
    mll operator/(const mll &y) const { return mll{(v * (ll)qpow(y, P - 2)) % P}; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = v * y.v % P, *this; }
    mll &operator/=(const mll &y) { return v = v * (ll)qpow(y, P - 2) % P, *this; }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mll &y) {
        ll x;
        is >> x;
        return y = mll(x), is;
    }
    friend ostream &operator<<(ostream &os, mll &y) { return os << y.v; }
};
//}}}
ll n, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setp(6);

    return cout.flush(), 0;
}

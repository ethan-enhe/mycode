// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
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
const ll MXN = (1 << 20) + 5;

ll n, m;
vector<ll> base, codewords;
ll dis[MXN];
queue<ll> q;
ll get_dis() {
    memset(dis, 0x3f, sizeof(dis));
    for (ll i = 0; i < (1 << m); i++) {
        if (i) {
            ll lbt = i & (-i);
            codewords[i] = codewords[i ^ lbt] ^ base[log2(lbt)];
        }
        dis[codewords[i]] = 0;
        q.push(codewords[i]);
    }
    // get the distance of each word to the nearest codeword
    ll weight = 0;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        if (dis[u] == 4)
            weight++;
        else if (dis[u] > 4)
            weight = MXN;
        for (ll i = 0; i < n; i++) {
            ll v = u ^ (1 << i);
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    while (!q.empty()) q.pop();
    return weight;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    n = 20, m = 10;
    base.resize(m);
    codewords.resize(1 << m);
    ll best = MXN;
    vector<ll> best_base;
    while (1) {
        // cerr << "---";
        for (ll i = 0; i < m; i++) {
            // a k-sparse vector
            base[i] = ri(0, (1 << n) - 1);
        }
        // Simulated annealing
        ld T = 1e6, delta = 0.97, eps = 1e-3;
        ll last = get_dis(), cur;
        while (T > eps) {
            ll x = ri(0, m - 1), y = 0;
            for (ll i = 0; i < n; i++) {
                if (ri(0, 3) == 0) {
                    y ^= (1 << i);
                }
            }
            ll tmp = base[x];
            base[x] ^= y;
            cur = get_dis();
            ll d = cur - last;
            if (d > 0 && exp(-d / T) < rd(0, 1)) {
                base[x] = tmp;
            } else {
                last = cur;
                // cerr << T << " " << cur << endl;
            }
            T *= delta;
        }
        if (last < best) {
            best = last;
            best_base = base;
            cerr << best << endl;
            for (ll i = 0; i < m; i++) {
                cerr << best_base[i] << " ";
            }
            cerr << endl;
        }
    }

    return 0;
}
/*
118784
340386 886401 816070 620247 116987 767633 182255 161892 697760 61842
*/

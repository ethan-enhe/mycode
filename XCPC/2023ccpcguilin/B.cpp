#include <bits/stdc++.h>

#include <vector>

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
const ll MXN = 3e5 + 5;

ll n, m, arr[MXN], brr[MXN];

// struct cmp {
//     bool operator()(const pi &x, const pi &y) const {
//         if (x.fi == y.fi) return x.se > y.se;
//         return x.fi < y.fi;
//     }
// };

multiset<pi> all;

int main() {
    // freopen("1", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        all.clear();

        cin >> n >> m;
        generate_n(arr + 1, n, nxt<int>);
        generate_n(brr + 1, m, nxt<int>);
        sort(arr + 1, arr + 1 + n);
        sort(brr + 1, brr + 1 + m);
        bool f = 1;
        ll waste_time = n - m;
        for (ll i = 1; i <= m; i++) {
            if (arr[n - m + i] > brr[i]) {
                f = 0;
                break;
            }
            ll dis = brr[i] - arr[n - m + i];
            waste_time -= dis;
            all.insert({arr[n - m + i], dis});
        }
        for (ll i = 1; i <= n - m; i++) all.insert({arr[i], -1});
        if (waste_time < 0) f = 0;
        if (!f) {
            cout << "-1" << nl;
            continue;
        }
        vector<ll> ans;
        for (ll i = 1; i <= n - m; i++) {
            if (!waste_time) break;
            ll mn=all.begin()->first;
            auto it=prev(all.lower_bound({mn,INF}));
            auto v = *it;
            all.erase(it);
            if (v.second == 0) {
                f = 0;
                break;
            }
            if (v.second < 0) --waste_time;
            // cerr<<v.first<<endl;
            ans.push_back(v.first);
            v.first++;
            --v.second;
            all.insert(v);

            // 删除
            v = *all.begin();
            all.erase(all.begin());
            if (v.second >= 0) {
                f = 0;
                break;
            }
        }
        if (!f || waste_time > 0) {
            cout << "-1" << nl;
            continue;
        }
        for (auto [u, v] : all) {
            if (v > 0)
                for (ll j = 0; j < v; j++) ans.push_back(u + j);
        }
        cout << ans.size() << nl;
        for (auto i : ans) cout << i << " ";
        cout << nl;
    }
    return 0;
}

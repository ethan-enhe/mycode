#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define all(x) (x).begin(), (x).end()
#define tpl template <typename T>

using ll = long long;
//}}}
//{{{ Func
tpl T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
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
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

ll n, m, arr[MXN];
bool f;
// 特判：
// 大小相同的环
// 3元环
mod solve_cycle_tree(vector<ll> chain_length) {
    reverse(all(chain_length));
    ll cnt = INF;
    mod ans = 1;
    for (ll i = chain_length.size() - 1; i >= 0; i--) {
        ++cnt;
        if (chain_length[i]) cnt = 0;
    }
    for (ll i = chain_length.size() - 1; i >= 0; i--) {
        ++cnt;
        if (chain_length[i]) {
            if (chain_length[i] < cnt)
                ans *= 2;
            else if (chain_length[i] > cnt)
                ans = 0;

            cnt = 0;
        }
    }
    return ans;
}
ll deg0[MXN], deg[MXN];
ll sz[MXN];
queue<ll> q;
void tpsort() {
    for (ll i = 1; i <= n; i++) {
        ++deg[arr[i]];
    }
    for (ll i = 1; i <= n; i++) {
        if (!deg[i]) q.push(i);
        deg0[i] = deg[i];
        sz[i] = 1;
        if (deg[i] > 2) f = 0;
    }
    while (!q.empty()) {
        ll p = q.front();
        q.pop();
        sz[arr[p]] += sz[p];
        if (--deg[arr[p]] == 0) q.push(arr[p]);
    }
    for (ll i = 1; i <= n; i++) {
        if (deg0[i] == 2 && !deg[i]) f = 0;
    }
}
ll pure_cnt[MXN];
mod fac[MXN], ifac[MXN];
mod c(ll x, ll y) {
    if (y > x || y < 0) return 0;
    return fac[x] * ifac[x - y] * ifac[y];
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = ifac[0] = 1;
    for (ll i = 1; i < MXN; i++) {
        fac[i] = fac[i - 1] * i;
        ifac[i] = (mod)1 / fac[i];
    }

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    f = 1;
    tpsort();
    if (!f) return cout << 0, 0;

    mod ans = 1;
    for (ll i = 1; i <= n; i++)
        if (deg[i]) {
            ll csz = 0;
            ll p = i;
            bool pure = 1;
            vector<ll> chain_length;
            while (deg[p]) {
                --deg[p];
                ++csz;
                p = arr[p];
                pure &= sz[p] == 1;
                chain_length.push_back(sz[p] - 1);
            }
            if (pure) {
                ++pure_cnt[csz];
            } else
                ans *= solve_cycle_tree(chain_length);
        }
    for (ll i = 1; i <= n; i++) {
        mod sum = 0;
        for (ll t = 0; t * 2 <= pure_cnt[i]; t++) {
            sum += c(pure_cnt[i], t) * c(pure_cnt[i] - t, t)*fac[t] * qpow((mod)i, t) / qpow((mod)2, t) *
                   qpow((mod)(1 + (i & 1 && i > 1)), pure_cnt[i] - t * 2);
        }
        ans *= sum;
    }
    cout << ans;

    return 0;
}

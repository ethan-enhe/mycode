#include <bits/stdc++.h>

#include <algorithm>
#include <cstdio>

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
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
}
const ll P = 998244353;
const char nl = '\n';
const ll MXN = 1e6 + 5, LG = 50;

ll getphi(ll x) {
    ll r = x;
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0) {
            do
                x /= i;
            while (x % i == 0);
            r -= r / i;
        }
    if (x != 1) r -= r / x;
    return r;
}
ll phi[LG], phii;
void init() {
    ll x = P;
    do {
        phi[phii++] = x;
        x = getphi(x);
    } while (x != 1);
    phi[phii++]=1;
}

ll emod(ll x, ll mod) { return x <= mod ? x : (x % mod + mod); }
ll qpow(ll x, ll y, ll mod) {
    ll r = 1;
    x = emod(x, mod);
    while (y) {
        if (y & 1) r = emod(r * x, mod);
        x = emod(x * x, mod), y >>= 1;
    }
    return r;
}
ll n;
ll arr[MXN], dp[MXN], cnt[MXN];
void add(ll x, ll y) {
    for (; x <= n; x += x & (-x)) dp[x] = (dp[x] + y) % P;
}
ll pre(ll x) {
    ll r = 0;
    for (; x; x ^= x & (-x)) r = (r + dp[x]) % P;
    return r;
}
ll cal(ll l, ll r) {
    r = min(r, l + phii - 1);
    ll last = 1;
    while (r >= l) {
        last = qpow(arr[r], (ll)last, phi[r - l]);
        --r;
    }
    return last % P;
}
int main() {
    freopen("zote.in","r",stdin);
    /* freopen("zote.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();
    n = nxt();
    generate(arr + 1, arr + 1 + n, nxt<ll>);
    cnt[0] = cnt[1] = 1;
    for (ll i = 0; i < n; i++) {
        ll cdp = pre(i);
        add(i + 1, cdp);
        for (ll j = i + 1; j <= min(n, i + phii); j++) {
            ll tmp = cal(i + 1, j) * cnt[i] % P;
            add(j, tmp);
            add(j + 1, -tmp);
        }
        ll tmp = cnt[i] * cal(i + 1, i + phii + 1) % P;
        add(i + phii + 1, tmp);
        if (i) cnt[i + 1] = (cnt[i] << 1) % P;
    }
    cout << (pre(n) + P) % P;
    return 0;
}

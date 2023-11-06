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
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
}
const ll P = 998244353;
const char nl = '\n';
const ll MXN = 1e6 + 5, LG = 40;

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
typedef __uint128_t L;
typedef unsigned long long ull;
struct Barrett {
    ull m, b;
    Barrett(const ull &m = 1) : m(m), b(((L(1) << 64) + m - 1) / m) {}
    friend inline ull operator/(const ull &a, const Barrett &mod) { return L(mod.b) * a >> 64; }
    friend inline ull operator%(const ull &a, const Barrett &mod) { return a - mod.m * (L(mod.b) * a >> 64); }
} phi[LG];
ll phii;
void init() {
    ll x = P;
    do {
        phi[phii++] = x;
        x = getphi(x);
    } while (x != 1);
    phi[phii++] = 1;
}

ll arr[MXN], dp[MXN], cnt[MXN];
ll emod(const ll &x, const Barrett &mod) { return x <= mod.m ? x : (x % mod + mod.m); }
ll emod2(const ll &x, const ll &mod) { return x <= mod ? x : (x & (mod - 1)) + mod; }
ll qpow(ll xid, ll y, ll modid) {
    ll r = 1, x = arr[xid], mod = phi[modid].m;
    if (modid >= 3) {
        x = emod2(x, mod);
        while (y) {
            if (y & 1) r = emod2(r * x, mod);
            x = emod2(x * x, mod), y >>= 1;
        }
    } else {
        x = emod(x, phi[modid]);
        while (y) {
            if (y & 1) r = emod(r * x, phi[modid]);
            x = emod(x * x, phi[modid]), y >>= 1;
        }
    }
    return r;
}
ll n;
void add(ll x, ll y) { dp[x] = (dp[x] + y) % P; }
ll cal(ll l, ll r) {
    r = min(r, l + phii - 1);
    ll last = 1;
    while (r >= l) {
        last = qpow(r, (ll)last, r - l);
        --r;
    }
    return last % P;
}

int main() {
    freopen("zote.in", "r", stdin);
    freopen("zote.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();
    n = nxt();
    generate(arr + 1, arr + 1 + n, nxt<ll>);
    cnt[0] = cnt[1] = 1;
    for (ll i = 0; i < n; i++) {
        ll cdp = dp[i];
        add(i + 1, cdp);
        for (ll j = i + 1; j <= min(n, i + phii); j++) {
            ll tmp = cal(i + 1, j) * cnt[i] % P;
            add(j, tmp);
            add(j + 1, -tmp);
        }
        ll tmp = cnt[i] * cal(i + 1, i + phii + 1) % P;
        add(i + phii + 1, tmp);

        if (i) cnt[i + 1] = (cnt[i] << 1) % P;
        dp[i + 1] += dp[i];
    }
    cout << (dp[n] + P) % P;
    return 0;
}

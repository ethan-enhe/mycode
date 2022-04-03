#pragma GCC optimize("Ofast", "-funroll-loops")
#pragma GCC target("sse4.1", "sse4.2", "ssse3", "sse3", "sse2", "sse", "avx2", "avx", "popcnt")
#include <bits/stdc++.h>

using namespace std;
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()

using ll = long long;
using pi = pair<ll, ll>;
const char nl = '\n';
const ll INF = 1e18;

ll n, m, P;
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> P;
        // 算原根
        vector<ll> fact;
        ll phi = P - 1;
        for (ll i = 2; i * i <= phi; i++)
            if (phi % i == 0) {
                fact.push_back(i);
                do
                    phi /= i;
                while (phi % i == 0);
            }
        if (phi != 1) fact.push_back(phi);
        auto qpow = [](ll x, ll y, ll mod) {
            ll r = mod != 1;
            while (y) {
                if (y & 1) r = r * x % mod;
                x = x * x % mod, y >>= 1;
            }
            return r;
        };
        auto chk = [&](ll x) -> bool {
            if (P == 2 && x == 1) return 1;
            for (ll i : fact)
                if (qpow(x, (P - 1) / i, P) == 1) return 0;
            return 1;
        };
        ll g = 1;
        while (!chk(g)) ++g;
        auto cmp = [](const pi &x, const pi &y) {
            if (x.fi != y.fi) return x.fi < y.fi;
            return x.se > y.se;
        };
        auto bsgs = [&](ll x, ll y, ll mod) -> ll {
            ll sq = sqrtl(mod) + 1;
            vector<pi> bs;
            for (ll i = 0; i < sq; i++) {
                bs.push_back({y, i});
                y = y * x % mod;
            }
            sort(all(bs), cmp);
            for (ll i = 1, va = 1; i <= sq; i++) {
                va = va * y % mod;
                auto it = lower_bound(all(bs), pi{va, INF}, cmp);
                if (it != bs.end() && it->fi == va) return i * sq - it->se;
            }
            return -1;
        };
        n = bsgs(g, n, P);
        --P;
        ll gnp = __gcd(n, P);
        n /= gnp, P /= gnp;
        ll cnt = 1, cd;
        while ((cd = __gcd(m, P)) != 1) P /= cd, ++cnt;
        cout << cnt << " " << bsgs(m, 1, P) + cnt << nl;
    }
    return 0;
}

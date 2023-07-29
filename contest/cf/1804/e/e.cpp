// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
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
const ll P = 1e9 + 7;
const char nl = '\n';
const ll N = 20;
const ll U = 1 << N;

ll n, m;
ll neib[U];
ll ring[U][N];
ll ans[N];
bool solve(ll s) {
    ll full = (1 << (s + 1)) - 1;
    for (ll i = 1; i <= full; i++) memset(ring[i], -1, sizeof(ring[i]));

    ring[1 << s][s] = -2;
    for (ll i = 1; i <= full; i++) {
        for (ll j = 0; j <= s; j++) {
            if (~ring[i][j]) {
                if (i != (1 << s) && neib[i] == ((1 << n) - 1) && ((neib[1 << j] >> s) & 1)) {
                    cout << "Yes" << endl;
                    ll x = i, y = j;
                    ans[y] = s;
                    while (ring[x][y] != -2) {
                        ll nxj = ring[x][y];
                        ans[nxj] = y;
                        x ^= (1 << y), y = nxj;
                    }
                    for (ll l = 0; l < n; l++) {
                        if (ans[l] != -1)
                            cout << ans[l] + 1 << " ";
                        else
                            for (ll q = 0; q < n; q++)
                                if (((neib[1 << l] >> q) & 1) && ((i >> q) & 1)) {
                                    cout << q + 1 << " ";
                                    break;
                                }
                    }
                    return 1;
                }
                for (ll k = 0; k < s; k++) {
                    if (((neib[1 << j] >> k) & 1) == 0) continue;
                    if ((i >> k) & 1) continue;
                    ring[i | (1 << k)][k] = j;
                }
            }
        }
    }
    return 0;
}
int main() {
    memset(ans, -1, sizeof(ans));
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 0; i < n; i++) neib[1 << i] |= 1 << i;
    for (ll i = 1; i <= m; i++) {
        ll u, v;
        cin >> u >> v;
        --u, --v;
        neib[1 << u] |= 1 << v;
        neib[1 << v] |= 1 << u;
    }
    ll full = (1 << n) - 1;
    for (ll i = 1; i <= full; i++) {
        ll lbt = i & (-i);
        neib[i] = neib[i ^ lbt] | neib[lbt];
    }
    for (ll i = n - 1; i >= 0; i--) {
        if (solve(i)) return 0;
    }
    cout << "No";
    return 0;
}

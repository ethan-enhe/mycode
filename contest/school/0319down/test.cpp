#include <bits/stdc++.h>

#include <algorithm>

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
/* mt19937_64 mr(12); */
//}}}
ll ri(const ll &l, const ll &r) {
    uniform_int_distribution<ll> res(l, r);
    return res(mr);
}
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
}
const ll P = 6;
const char nl = '\n';
const ll MXN = 1e6 + 5, LG = 100;

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
}
ll n, m;
ll arr[MXN];

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
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();
    for (int i = 1; i <= 100; i++) {
        n = ri(1, 6);
        for (int i = 1; i <= n; i++) arr[i] = ri(1, 2);
        /* freopen("test.in", "r", stdin); */
        /* freopen("test.out","w",stdout); */
        /* n = nxt(); */
        /* generate(arr + 1, arr + 1 + n, nxt<ll>); */
        for (ll i = 1; i <= 1; i++) {
            ll l = ri(1, n);
            ll r = ri(l, min(l + 3, n));
            /* ll l, r; */
            /* cin >> l >> r; */
            ll x = 1;
            for (int j = r; j >= l; j--) {
                x = pow(arr[j], x);
            }
            if (x % P != cal(l, r)) {
                cout << n << endl;
                for (int i = 1; i <= n; i++) cout << arr[i] << " ";
                cout << endl;
                cout << l << " " << r << endl;
                cout << x << " " << x % P << " " << cal(l, r) << endl;
                break;
                assert(x % P == cal(l, r));
            }
        }
    }
    return 0;
}

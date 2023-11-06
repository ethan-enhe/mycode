#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll P = 20051131;
ll n, m, k, res;
ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
set<ll> ind;
void mod(ll x) {
    auto it = ind.upper_bound(x);
    ll r = *it--;
    if (x == *it) return;
    res = (res - qpow(r - *it, k) + qpow(r - x, k) + qpow(x - *it, k)) % P;
    if (res < 0) res += P;
    ind.insert(x);
}
int main() {
    scanf("%lld%lld%lld", &n, &m, &k);
    ind.insert(1);
    ind.insert(n + 1);
    res = qpow(n, k);
    while (m--) {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        mod(x);
        printf("%lld\n", res);
    }

    return 0;
}

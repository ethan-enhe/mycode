#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll P = 998244353;
const ll MXN = 1e7 + 5;
ll n;
ll pri[MXN], pcnt;
ll mnf[MXN];
void sieve() {
    mnf[1] = 1;
    for (ll i = 2; i <= n; i++) {
        if (!mnf[i]) {
            pri[++pcnt] = i;
            mnf[i] = i;
        }
        for (ll j = 1; i * pri[j] <= n; j++) {
            mnf[i * pri[j]] = pri[j];
            if (i % pri[j] == 0) break;
        }
    }
}
// ll fcnt[MXN];
ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
// void fac(ll x) {
//     ll last = 0, cnt = 0;
//     auto report = [](ll x, ll y) { fcnt[x] = max(fcnt[x], y); };
//     while (x > 1) {
//         if (mnf[x] == last) {
//             cnt++;
//         } else {
//             report(last, cnt);
//             last = mnf[x], cnt = 1;
//         }
//         x /= mnf[x];
//     }
//     report(last, cnt);
// }
ll inv[MXN], fact[MXN], ifact[MXN];
void init() {
    fact[0] = 1;
    for (ll i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % P;
    }
    ifact[n] = qpow(fact[n], P - 2);
    for (ll i = n; i; i--) {
        ifact[i - 1] = ifact[i] * i % P;
        inv[i] = ifact[i] * fact[i - 1] % P;
    }
}
int main() {
    cin >> n;
    sieve();
    init();
    // cerr << inv[2] * 2 % P << endl;
    ll sum = 0, ans = 0;
    for (ll i = 1; i <= n; i++) {
        // fac(i);
        ans = (ans + sum - inv[i] * (i - 1)) % P;
        sum = (sum + inv[i]) % P;
    }
    for (ll i = 2; i <= n; i++) {
        if (mnf[i] == i) {
            ll v = i;
            while (v * i <= n) v *= i;
            ans = ans * v % P;
        }
    }
    cout << (ans + P) % P;
    return 0;
}

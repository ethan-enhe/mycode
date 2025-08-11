#include <bits/stdc++.h>

#include <random>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
mt19937_64 rnd(clock());
ll ri(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rnd); }
int main() {
    ll t = 100;
    cout << t << endl;
    while (t--) {
        ll n = ri(1, 5);
        cout << n << endl;
        for (ll i = 1; i <= n; i++) cout << ri(-10, 10) << " ";
        cout << endl;
    }
    return 0;
}

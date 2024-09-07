#include <bits/stdc++.h>

#include <cctype>
#define fi first
#define se second
using namespace std;
using pi = pair<int, int>;
using ll = long long;
using ld = long double;
const ll MXN = 505;
const ll INF = 1e9;
ll n, d, r;

ld dp[MXN][MXN][MXN];
ld c(ll x, ll y) {
    ld r = 1;
    for (ll i = 1; i <= y; i++) {
        r *= ld(x - i + 1) / i;
    }
    return r;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> d >> r;
    dp[d + 1][0][0] = 1;
    for (ll i = d + 1; i > 1; i--) {
        for (ll j = 0; j * i <= d; j++) {
            for (ll k = j * i; k <= d; k++) {
                for (ll l = 0; k + l * (i - 1) <= d; l++) {
                }
            }
        }
    }
    return 0;
}

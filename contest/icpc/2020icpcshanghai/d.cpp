#include <iomanip>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 40;
const ll P = 1e9 + 7;
ll x, y, dp[MXN][2][2];
double a, b, c, d, e;
int main() {
    ll t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> a >> b >> c >> d >> e;
        double tmp = abs(d - b);
        cout << fixed << setprecision(10) << min(a + tmp, tmp + (a - tmp) * 2) / (c + e) << '\n';
    }

    return 0;
}

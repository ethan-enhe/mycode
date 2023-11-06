#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    vector<double> p;
    cin >> n;
    n = 1 << n;
    p.resize(n);
    for (double &v : p) cin >> v;
    for (int w = 1; w < n; w <<= 1)
        for (int _w = w << 1, i = w; i < n; i += _w)
            for (int j = 0; j < w; j++) p[i ^ j] += p[i ^ j ^ w];
    double ans = 0;
    for (int i = 0; i < n - 1; i++) {
        if (fabs(p[i] - 1) <= 1e-9) {
            cout << "INF";
            return 0;
        }
        ans += (__builtin_popcount(i ^ (n - 1)) & 1 ? 1. : -1.) / (1 - p[i]);
    }
    cout.flags(ios::fixed);
    cout.precision(10);
    cout << ans;

    return 0;
}

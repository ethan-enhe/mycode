

#include <bits/stdc++.h>

#include <cmath>
#include <cstdlib>
#define fi first
#define se second
using namespace std;
using db = long double;
using ll = long long;
using pi = pair<db, db>;
const ll MXN = 1e4 + 5;
const ll INF = 1e18;
ll n, h, a, b;
pi coor[MXN];
db dp[MXN];
pi operator-(const pi &x, const pi &y) { return {x.fi - y.fi, x.se - y.se}; }
pi operator+(const pi &x, const pi &y) { return {x.fi + y.fi, x.se + y.se}; }
pi operator*(const pi &x, const db &y) { return {x.fi * y, x.se * y}; }
db len(pi x) { return sqrt(x.fi * x.fi + x.se * x.se); }
bool chk(ll i, ll j) {
    db r = (coor[j].fi - coor[i].fi) / 2;
    pi center = {coor[j].fi - r, h - r};
    for (int k = i; k <= j; k++) {
        if (coor[k].se > center.se && len(center - coor[k]) > r) {
            return 0;
        }
    }
    return 1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    const ll mxx = 10000;
    srand(time(0));
    n = 10000, h = rand() % 100 + 1;
    a = rand() % 10, b = rand() % 10;
    cout << n << " " << h << " " << a << " " << b << endl;
    for (int i = 1; i <= n; i++) {
        coor[i] = {rand() % mxx, rand() % h};
    }
    sort(coor + 1, coor + 1 + n);
    for (int i = 1; i <= n; i++) {
        cout << coor[i].fi << " " << coor[i].se << endl;
    }
    return 0;
}

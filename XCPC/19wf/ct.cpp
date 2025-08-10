

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
    srand(time(0));
    for (int i = 1; i <= 100; i++) {
        system("./gen.exe> 1.in");
        system("./B.exe<1.in>2.out");
        system("./Bf.exe<1.in>3.out");
        if (system("diff 2.out 3.out")) {
            cout << "!";
            break;
            ;
        }
        cout << i << endl;
    }
    return 0;
}

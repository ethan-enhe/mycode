#include <bits/stdc++.h>
#include <unistd.h>

#include <algorithm>
#include <cmath>
#include <vector>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ld = long double;
using pi = pair<ll, ll>;

const ll MXN = 1005;
const ld EPS = 0.001;
ll n;
ll cnt[MXN];

ld readfrac() {
    ld x, y;
    cin >> x >> y;
    return (ld)x / y;
}
map<pi, ld> cache;
ld qry(ld fx) {
    ll x = round(fx * 1000), y = 1000;
    ll g = __gcd(x, y);
    x /= g, y /= g;
    auto it = cache.find({x, y});
    if (it != cache.end()) return it->second;
    cout << "? " << x << " " << y << endl;
    cout.flush();
    return cache[{x, y}] = readfrac();
}

ld solve(ll x1, ll x2) {
    ld qx1 = x1 + EPS * (cnt[x1] > 1);
    ld qx2 = x2 - EPS * (cnt[x2] > 1);
    ld qh1 = qry(qx1);
    ld qh2 = qry(qx2);

    ld slope = (qh1 - qh2) / (qx1 - qx2);
    ld h1 = qh1 + ((ld)x1 - qx1) * slope;
    ld h2 = qh2 + ((ld)x2 - qx2) * slope;
    // cerr << slope << endl;
    // cerr << qh1 << " " << qh2 << endl;
    // cerr << x1 << " " << qx1 << " " << qx2 << " " << x2 << endl;
    // cerr << h1 << " " << h2 << endl;
    return (h1 + h2) * (x2 - x1);
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        for (ll i = 0; i < MXN; i++) cnt[i] = 0;
        cache.clear();
        vector<ll> xcoor;
        cin >> n;
        for (ll i = 1; i <= n; i++) {
            ll x, y;
            cin >> x >> y;
            ++cnt[x];
            xcoor.push_back(x);
        }
        sort(xcoor.begin(), xcoor.end());
        xcoor.erase(unique(xcoor.begin(), xcoor.end()), xcoor.end());

        if (cnt[xcoor.front()] == 1) {
            cache[{xcoor.front(), 1}] = 0;
        }
        if (cnt[xcoor.back()] == 1) {
            cache[{xcoor.back(), 1}] = 0;
        }
        ld ans = 0;
        for (ll i = 1; i < xcoor.size(); i++) {
            ans += solve(xcoor[i - 1], xcoor[i]);
        }
        ll fz = round(ans);
        if (fz % 2)
            cout << "! " << fz << " 2" << endl;
        else
            cout << "! " << fz / 2 << " 1" << endl;
        cout.flush();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n1, n2, n3;
ll a, b, g;
ll p, q;
ll exgcd(ll x, ll y, ll &a, ll &b) {
    if (y == 0) {
        a = 1, b = 0;
        return x;
    }
    ll res = exgcd(y, x % y, b, a);
    b -= a * (x / y);
    return res;
}
bool chk(ll x) {
    if (x % g) return 0;
    x /= g;
    ll ta = a * x, tb = b * x;
    if (ta < 0) {
        ll delt = (-ta + n2 - 1) / n2;
        ta += n2 * delt;
        tb -= n1 * delt;
        return ta >= 0 && tb >= 0;
    }
    if (tb < 0) {
        ll delt = (-tb + n1 - 1) / n1;
        ta -= n2 * delt;
        tb += n1 * delt;
        return ta >= 0 && tb >= 0;
    }
    return 1;
}
bool _chk(ll s, ll _p) {
    if (n2 == n1) {
        return s  == _p*n1;
    }
    ll rh = s - _p * n1, lh = n2 - n1;
    if (rh % lh) return 0;
    rh /= lh;
    if (rh > _p || rh < 0) return 0;
    return 1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> p >> q >> n1 >> n2 >> n3;
    ll INF = 1e18;
    ll mx = -1, mn = -1;
    for (ll i = 0; i <= p && i * n3 <= q; i++) {
        if (_chk(q - i * n3, p - i)) {
            mx = i;
            if (mn == -1) mn = i;
        }
    }
    if (mn == -1)
        cout << -1;
    else
        cout << mn << " " << mx;
    return 0;
}

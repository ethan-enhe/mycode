#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const ll MXN = 1 << 18;
ll n, m;
ll a[MXN], b[MXN], c[MXN], tmp[MXN];
#define upd(i, j) c[i | j] = max(c[i | j], a[i] + b[j])
inline void solve(ll *a, ll *b, ll *c, ll *tmp, ll len) {
    if (len <= 4) {
        upd(0,0);upd(0,1);upd(0,2);upd(0,3);
        upd(1,0);upd(1,1);upd(1,2);upd(1,3);
        upd(2,0);upd(2,1);upd(2,2);upd(2,3);
        upd(3,0);upd(3,1);upd(3,2);upd(3,3);
        return;
    }
    ll hlen = len >> 1;
    solve(a, b, c, tmp, hlen);
    solve(a + hlen, b, c + hlen, tmp, hlen);
    for (ll i = hlen; i < len; i++) {
        *tmp++ = a[i];
        a[i] = max(a[i], a[i - hlen]);
    }
    solve(a + hlen, b + hlen, c + hlen, tmp, hlen);
    memcpy(a + hlen, tmp-hlen, sizeof(ll) * hlen);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    n = 1 << n;
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> b[i];
    solve(a, b, c, tmp, n);
    for (ll i = 0; i < n; i++) cout << c[i] << ' ';
    return 0;
}

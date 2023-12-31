#include <bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
const ll INF = 1e18;
const ll MXN = 3e5 + 5;

inline long double inter(const pi &x, const pi &y) {
    return x.fi == y.fi ? (x.se > y.se ? -INF : INF) : (long double)(y.se - x.se) / (x.fi - y.fi);
}

ll n, s, sc[MXN], st[MXN], dp[MXN];
pi q[MXN];
ll ql = 1, qr;
int main() {
    scanf("%lld%lld", &n, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", st + i, sc + i);
        st[i] += st[i - 1], sc[i] += sc[i - 1];
    }
    q[++qr] = mp(0, s * sc[n]);
    for (int i = 1; i <= n; i++) {
        ll l = ql, r = qr;
        while (l < r) {
            ll mid = (l + r) >> 1;
            if (inter(q[mid], q[mid + 1]) >= st[i])
                r = mid;
            else
                l = mid + 1;
        }
        dp[i] = q[l].fi * st[i] + q[l].se + st[i] * sc[i];
        pi curseg = mp(-sc[i], dp[i] + s * (sc[n] - sc[i]));
        while (ql < qr && inter(q[qr - 1], q[qr]) >= inter(q[qr], curseg)) qr--;
        q[++qr] = curseg;
    }
    printf("%lld", dp[n]);

    return 0;
}

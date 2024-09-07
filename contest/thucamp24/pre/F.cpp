#include <bits/stdc++.h>

#include <queue>

using namespace std;
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using ld = long double;
using pi = pair<ll, ll>;
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

ll n, m;
ll h[MXN], p[MXN];
ll mxt[MXN], mnt[MXN];

struct mxavg {
    ll sum, cnt;
    priority_queue<pi, vec<pi>, greater<pi>> can_be_remove;
    mxavg(ll _sum = 0, ll _cnt = 0) : sum(_sum), cnt(_cnt) {}
    void ins(pi x) {
        can_be_remove.push(x);
        while (!can_be_remove.empty()) {
            auto [v, c] = can_be_remove.top();
            ll r = (sum - 1) / cnt;
            if (r * cnt >= sum) --r;
            if (v <= r) {
                cnt -= c;
                sum -= v * c;
                can_be_remove.pop();
            } else
                break;
        }
    }
    pi getva() { return {sum, cnt}; }
} mx, mn;
ll sum = 0, cnt = 0;
ll getans(ll t) {
    ll l = 0, r = n + 1;
    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        if (t >= mnt[mid] && t <= mxt[mid])
            l = mid;
        else
            r = mid - 1;
    }
    if (l == 0) return -1;
    return n - l + 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> p[i] >> h[i];
        sum += p[i] * h[i];
        cnt += h[i];
    }
    mx = mxavg(sum, cnt);
    mn = mxavg(-sum, cnt);

    mxt[n + 1] = sum / cnt;
    mnt[n + 1] = (sum + cnt - 1) / cnt;
    for (ll i = n; i; i--) {
        mx.ins({p[i], h[i]});
        mn.ins({-p[i], h[i]});
        pi x = mx.getva();
        pi y = mn.getva();
        y.fi = -y.fi;
        mxt[i] = x.fi / x.se;
        mnt[i] = (y.fi + y.se - 1) / y.se;
    }
    while (m--) {
        ll t;
        cin >> t;
        cout << getans(t) << nl;
    }

    return 0;
}

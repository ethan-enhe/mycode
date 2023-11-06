#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
using ld = long double;
const ll MXN = 1e6 + 5, INF = 1e18;
ll n, m, mxt, A, B, C, ans = INF;

struct rt {
    ll u, v, t;
};
vector<rt> rts[MXN];

struct line {
    ll p;
    pi f;
};
vector<line> lines[MXN];

ld itsc(pi x, pi y) {
    if (x.se == y.se) return x.fi > y.fi ? -INF : INF;
    return ld(x.fi - y.fi) / (y.se - x.se);
}
ll cal(pi f, ll x) { return f.fi + f.se * x; }
struct convex {
    ll ql, qr;
    vector<pi> q;
    convex() { ql = 0, qr = -1; }
    void pb(pi x) {
        if (++qr == (ll)q.size())
            q.push_back(x);
        else
            q[qr] = x;
    }
    void ins(pi x) {
        while (ql < qr && itsc(q[qr - 1], x) > itsc(q[qr], x)) --qr;
        pb(x);
    }
    ll que(ll x) {
        if (q.empty()) return INF;
        while (ql < qr && itsc(q[ql], q[ql + 1]) < x) ++ql;
        return cal(q[ql], x);
    }
} dp[MXN];

/*
dp[i]=(dp[j]+At_j^2-Bt_j)+(-2At_j)*s_i
+As_i^2+Bs_i+C
*/

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> A >> B >> C;
    for (ll i = 1, u, v, s, t; i <= m; i++) {
        cin >> u >> v >> s >> t;
        rts[s].push_back({u, v, t});
        mxt = max(mxt, t);
    }
    lines[0].push_back({1, {0, 0}});
    for (int t = 0; t <= mxt; t++) {
        for (line &i : lines[t]) dp[i.p].ins(i.f);
        for (rt &i : rts[t]) {
            ll cdp = A * t * t + B * t + C + dp[i.u].que(t);
            if (cdp >= INF) continue;
            lines[i.t].push_back({i.v, {cdp + A * i.t * i.t - B * i.t, -2 * A * i.t}});
            if (i.v == n) ans = min(ans, cdp + i.t);
        }
    }
    cout << ans;
    return 0;
}

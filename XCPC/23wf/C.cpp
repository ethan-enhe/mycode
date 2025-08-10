#include <bits/stdc++.h>
#define fi first
#define se second
using ll = long long;
using ld = long double;
using namespace std;
const ll MXN = 1e6 + 5;
ll pool[MXN], cnt;
ld dot(ld *x, ld *y) {
    ld res = 0;
    for (ll i = 1; i <= cnt; i++) res += x[i] * y[i];
    return res;
}
struct dice {
    ll len, ori[MXN];
    ld F[MXN], f[MXN], mod;
    void read() {
        cin >> len;
        for (ll i = 1; i <= len; i++) {
            cin >> ori[i];
            pool[++cnt] = ori[i];
            pool[++cnt] = ori[i] + 1;
            pool[++cnt] = ori[i] - 1;
        }
    }
    void tovec() {
        for (ll i = 1; i <= len; i++) {
            ori[i] = lower_bound(pool + 1, pool + 1 + cnt, ori[i]) - pool;
        }
        for (ll i = 1; i <= len; i++) {
            ++f[ori[i]];
        }
        for (ll i = 1; i <= cnt; i++) {
            f[i] /= len;
            F[i] += F[i - 1] + f[i];
        }
        ld last = 0;
        for (ll i = 1; i <= cnt; i++) {
            ld tmp = last - (F[cnt] - F[i]);
            last = F[i];
            F[i] = tmp / 2;
            cerr << pool[i] << " " << f[i] << " " << F[i] << "\n";
        }
        mod = sqrt(dot(F, F));
        cerr << "---\n";
    }
} a, b;
using pi = pair<ld, ld>;

ll up_top, down_top;
pi up_convex[MXN], down_convex[MXN];
pi tmp[MXN];
pi operator-(const pi &x, const pi &y) { return pi{x.fi - y.fi, x.se - y.se}; }
ld operator*(const pi &x, const pi &y) { return x.fi * y.se - x.se * y.fi; }
ld operator&(const pi &x, const pi &y) { return x.fi * y.fi + x.se * y.se; }
void init_convex() {
    for (ll i = 1; i <= cnt; i++) {
        tmp[i] = {a.F[i], b.F[i]};
    }
    sort(tmp + 1, tmp + cnt + 1);
    up_top = down_top = 0;
    for (ll i = 1; i <= cnt; i++) {
        while (up_top > 1 && (tmp[i] - up_convex[up_top]) * (tmp[i] - up_convex[up_top - 1]) <= 0) up_top--;
        up_convex[up_top++] = tmp[i];
        while (down_top > 1 && (tmp[i] - down_convex[down_top]) * (tmp[i] - down_convex[down_top - 1]) <= 0) down_top--;
        down_convex[down_top++] = tmp[i];
    }
}

bool query(pi dir, ld t) { // 查询是否有 dot dir <t 的点
    ll l = 1, r = up_top;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if ((up_convex[mid] & dir) < (up_convex[mid + 1] & dir))
            l = mid + 1;
        else
            r = mid;
    }
    if ((up_convex[l] & dir) < t) return 1;
    l = 1, r = down_top;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if ((down_convex[mid] & dir) < (down_convex[mid + 1] & dir))
            l = mid + 1;
        else
            r = mid;
    }
    if ((down_convex[l] & dir) < t) return 1;
    return 0;
}
const ld INF = 1e18;
void solve(ld *x, ld *y) {
    // 1 dot z=1
    // x dot z=0
    // min y dot z
    // a1 x1+a2 x2 =0
    ld ans = INF;
    for (ll i = 1; i <= cnt; i++) {
        ld l = -INF, r = INF;
        for (ll j = 1; j <= 100; j++) {
            ld mid = (l + r) / 2;
            if (query({x[i], y[i]}, mid)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        ans = min(ans, r);
        if (x[i] >= 0) ans = min(ans, y[i]);
    }
    cout<<ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    a.read();
    b.read();
    sort(pool + 1, pool + 1 + cnt);
    cnt = unique(pool + 1, pool + 1 + cnt) - pool - 1;
    a.tovec();
    b.tovec();

    cout << dot(a.f, b.F) + dot(a.F, b.f) << endl;

    if (dot(a.f, b.F) < 0) {
        swap(a, b);
    }

    bool opp = 0;
    if (dot(a.F, b.F) < 0) {
        opp = 1;
    }

    cout << a.mod << " " << b.mod << endl;
    ld cos_theta = dot(a.F, b.F) / a.mod / b.mod;
    ld theta = acos(cos_theta);
    ld sin_theta = sin(theta);
    cout << b.mod * sin_theta + 0.5 << endl;

    return 0;
}

#include <bits/stdc++.h>

#include <cstdio>

using namespace std;
//{{{ Def

using ll = long long;
//}}}
//
const ll P = 1e9 + 7;
//{{{ Type
struct pi {
    ll fi, se;
};
pi &operator+=(pi &x, const pi &y) { return x.fi += y.fi, x.se += y.se, x; }
pi operator+(const pi &x, const pi &y) { return {x.fi + y.fi, x.se + y.se}; }
pi &operator-=(pi &x, const pi &y) { return x.fi -= y.fi, x.se -= y.se, x; }
pi operator-(const pi &x, const pi &y) { return {x.fi - y.fi, x.se - y.se}; }
pi &operator*=(pi &x, const ll &y) { return x.fi *= y, x.se *= y, x; }
pi operator*(const pi &x, const ll &y) { return {x.fi * y, x.se * y}; }
istream &operator>>(istream &is, pi &y) { return is >> y.fi >> y.se; }
ostream &operator<<(ostream &os, const pi &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

pi operator-(const pi &x) { return {-x.fi, -x.se}; }
ll operator*(const pi &x, const pi &y) { return x.fi * y.se - y.fi * x.se; }
ll xx(pi x) {
    if (x.fi >= 0)
        return x.se >= 0 ? 0 : 3;
    else
        return x.se >= 0 ? 1 : 2;
}
bool operator<(const pi &x, const pi &y) {
    if (xx(x) != xx(y)) return xx(x) < xx(y);
    return x * y > 0;
}
ll n, m;
pi s, t, l;
pi arr[MXN];
pi vs[MXN], vt[MXN];
vector<pi> qry[MXN];
vector<ll> add[MXN];

template <typename T>
ll lb(T *x, T y) {
    return lower_bound(x + 1, x + 1 + n, y) - x;
}
template <typename T>
ll ub(T *x, T y) {
    return upper_bound(x + 1, x + 1 + n, y) - x;
}

ll sum[MXN];
void mdf(ll x) {
    for (; x <= n; x += x & (-x)) sum[x]++;
}
ll pre(ll x) {
    ll r = 0;
    for (; x; x -= x & (-x)) r += sum[x];
    return r;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("test.in", "r", stdin);
    cin >> s >> t;
    l = t - s;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        vs[i] = arr[i] - s;
        vt[i] = arr[i] - t;
    }
    sort(vs + 1, vs + 1 + n);
    sort(vt + 1, vt + 1 + n);
    // for (ll i = 1; i <= n; i++) cout << vs[i];
    // cout << endl;
    // for (ll i = 1; i <= n; i++) cout << vt[i];
    // cout << endl;

    ll cpos = 0, cneg = 0;
    for (ll i = 1; i <= n; i++) {
        pi ds = arr[i] - s, dt = arr[i] - t;
        ll res = l * ds;
        if (!res) {
            if (ds.fi > 0)
                ++cpos;
            else
                ++cneg;
            continue;
        }

        add[lb(vs, ds)].push_back(lb(vt, dt));

        if (res < 0) ds = -ds, dt = -dt;
        vector<pi> qs, qt;
        if (ds < -ds) {
            qs.push_back(pi{ub(vs, -ds) - 1, 1});
            qs.push_back(pi{lb(vs, ds) - 1, -1});
        } else {
            qs.push_back(pi{ub(vs, -ds) - 1, 1});
            qs.push_back(pi{n, 1});
            qs.push_back(pi{lb(vs, ds) - 1, -1});
        }
        if (dt < -dt) {
            qt.push_back(pi{ub(vt, dt) - 1, 1});
            qt.push_back(pi{n, 1});
            qt.push_back(pi{lb(vt, -dt) - 1, -1});
        } else {
            qt.push_back(pi{ub(vt, dt) - 1, 1});
            qt.push_back(pi{lb(vt, -dt) - 1, -1});
        }
        for (auto &x : qs)
            for (auto &y : qt) {
                qry[x.fi].push_back({y.fi, x.se * y.se});
            }
    }

    ll ans = 0;
    for (ll i = 0; i <= n; i++) {
        for (auto &j : add[i]) mdf(j);
        for (auto &j : qry[i]) {
            ans += j.se * pre(j.fi);
        }
    }
    cout << ans + cpos * (cpos + 1) / 2 + cneg * (cneg + 1) / 2 - n;
    return 0;
}

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const char nl = '\n';
const ll MXN = 2e5 + 5;

ll n, m, arr[MXN];
vector<ll> adj[MXN];

struct vec {
    ll d_2, d_1, d0, d1, d2;
    ll sum() { return d_2 + d_1 + d0 + d1 + d2; }
    vec operator+(const vec &b) const { return {d_2 + b.d_2, d_1 + b.d_1, d0 + b.d0, d1 + b.d1, d2 + b.d2}; }
    vec operator-(const vec &b) const { return {d_2 - b.d_2, d_1 - b.d_1, d0 - b.d0, d1 - b.d1, d2 - b.d2}; }
};
using qr = pair<ll, vec>;
vec sum[MXN];
vec pre(ll x) {
    vec r{0, 0, 0, 0, 0};
    for (; x; x -= x & (-x)) r = r + sum[x];
    return r;
}
void mdf(ll x, vec y) {
    for (; x <= n; x += x & (-x)) sum[x] = sum[x] + y;
}
vec weight[MXN];
void solve(vector<pair<ll, vec>> &q) {
    for (ll i = 0; i <= n; i++) {
        adj[i].clear();
        sum[i] = {0, 0, 0, 0, 0};
    }
    for (ll i = 0; i < q.size(); i++) adj[q[i].first].push_back(i);
    for (ll i = 0; i <= n; i++) {
        if (i) mdf(arr[i], weight[i]);
        for (auto &j : adj[i]) {
            // cerr<<"q"<<i<<" "<<q[j].second.d0<<endl;
            q[j].second = pre(q[j].second.d0);
        }
    }
}
ll p[MXN];
ll u[MXN], v[MXN];
ll pu[MXN], pv[MXN];
ll cc(ll i) { return min(arr[i] - 1 - p[i], p[i]); }
int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) cin >> arr[i];
    cin >> m;
    for (ll i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
        if (u[i] > v[i]) swap(u[i], v[i]);
    }

    // 先求pre，suf
    vector<qr> q1;
    vector<qr> q2;
    for (ll i = 1; i <= n; i++) {
        weight[i] = {0, 0, 1, 0, 0};
        q1.push_back({i, {0, 0, arr[i] - 1, 0, 0}});
    }
    solve(q1);
    ll idx = 0;
    ll tot = 0;
    for (ll i = 1; i <= n; i++) {
        p[i] = q1[idx++].second.d0;
        // cerr << p[i] << nl;
        ll s = arr[i] - p[i] - 1;
        tot += cc(i);
        weight[i] = {0, 0, 0, 0, 0};
        if (s - p[i] <= -2)
            weight[i].d_2 = 1;
        else if (s - p[i] == -1)
            weight[i].d_1 = 1;
        else if (s == p[i])
            weight[i].d0 = 1;
        else if (s - p[i] == 1)
            weight[i].d1 = 1;
        else
            weight[i].d2 = 1;
    }
    for (ll i = 1; i <= m; i++) {
        q2.push_back({u[i], {0, 0, arr[u[i]], 0, 0}});
        q2.push_back({u[i], {0, 0, arr[v[i]], 0, 0}});
        q2.push_back({v[i] - 1, {0, 0, arr[u[i]], 0, 0}});
        q2.push_back({v[i] - 1, {0, 0, arr[v[i]], 0, 0}});
    }
    solve(q2);
    idx = 0;
    for (ll i = 1; i <= m; i++) {
        vec ruu = q2[idx++].second;
        vec ruv = q2[idx++].second;
        vec rvu = q2[idx++].second;
        vec rvv = q2[idx++].second;
        if (u[i] == v[i])
            cout << tot << nl;
        else {
            ll res = tot;
            ll pu = ruv.sum() - (arr[u[i]] <= arr[v[i]]);
            ll cu = min(pu, arr[v[i]] - pu - 1);
            ll pv = rvu.sum() - 1 + (arr[u[i]] >= arr[v[i]]);
            ll cv = min(pv, arr[u[i]] - pv - 1);
            res = res - cc(u[i]) - cc(v[i]);
            res = res + cu + cv;
            // cout<<mid.d2<<endl;
            if (arr[u[i]] <= arr[v[i]]) {
                vec mid = rvv - rvu - ruv + ruu;
                res = res + mid.d_2 - mid.d0 - mid.d1 - mid.d2;
            } else {
                vec mid = rvu - rvv - ruu + ruv;
                res = res - mid.d_2 - mid.d_1 - mid.d0 + mid.d2;
            }
            cout << res << nl;
        }
    }

    return 0;
}

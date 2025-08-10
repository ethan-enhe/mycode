#include <bits/stdc++.h>

#include <cstdlib>
#include <stack>

using namespace std;
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using pi = pair<ll, ll>;
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 5e5 + 5;

ll n, m, arr[MXN];
ll fa[MXN], rnd[MXN];
ll u[MXN], v[MXN];
ll conponent;
ll totconponent;
#define id(i, j) ((i) + ((j) ? n : 0))

stack<pi> hist;
int find(int x) { return fa[x] == x ? x : find(fa[x]); }
void mrg(ll x, ll y) {
    // cerr << x << " " << y << endl;
    x = find(x), y = find(y);
    if (x != y) conponent--;
    if (rnd[x] > rnd[y]) swap(x, y);
    hist.push({y, fa[y]});
    fa[y] = x;
}

bool add(ll u, ll v, ll w) {
    mrg(id(u, 0), id(v, w));
    mrg(id(u, 1), id(v, 1 ^ w));
    return find(id(u, 0)) != find(id(u, 1));
}
void withdraw() {
    pi t = hist.top();
    hist.pop();
    if (fa[t.fi] != t.se) conponent++;
    fa[t.fi] = t.se;
}
ll cnt = 0;
void solve(ll l, ll r) {
    // cerr << l << " " << r << endl;
    if (l == r) {
        if (add(u[l], v[l], 0)) {
            ++cnt;
            totconponent = conponent / 2;
            // cout << conponent;
        }
        withdraw();
        withdraw();
        return;
    }
    ll mid = (l + r) >> 1;
    bool f = 1;
    for (ll i = r; i > mid; i--) f &= add(u[i], v[i], 1);
    if (f) solve(l, mid);
    for (ll i = r; i > mid; i--) {
        withdraw();
        withdraw();
    }
    f = 1;
    for (ll i = l; i <= mid; i++) f &= add(u[i], v[i], 0);
    if (f) solve(mid + 1, r);
    for (ll i = l; i <= mid; i++) {
        withdraw();
        withdraw();
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i < n; i++) {
        ll useless;
        cin >> useless;
    }
    for (ll i = 1; i <= n; i++) {
        fa[id(i, 0)] = id(i, 0);
        fa[id(i, 1)] = id(i, 1);
        rnd[id(i, 0)] = rand();
        rnd[id(i, 1)] = rand();
    }
    u[1] = v[1] = 1;
    ++m;
    for (ll i = 2; i <= m; i++) {
        cin >> u[i] >> v[i];
    }
    conponent = n * 2;
    solve(1, m);
    while (--totconponent) {
        cnt = cnt * 2 % 998244353;
    }

    cout << cnt << nl;
    return 0;
}

#include <bits/stdc++.h>

#include <algorithm>
using namespace std;
using ll = long long;
using ld = long double;
const ll MXN = 1e5 + 5;
const ll MXK = 65;
const ll INF = 1e18;

struct mx {
    ll fi, se, fii, sei;
    mx(ll x = -INF, ll y = -INF) : fi(x), se(y), fii(-1), sei(-2) {}
    void ins(ll x, ll i) {
        if (fii == i)
            fi = max(fi, x);
        else if (sei == i) {
            se = max(se, x);
            if (se > fi) {
                swap(se, fi);
                swap(sei, fii);
            }
        } else {
            if (x > fi) {
                se = fi;
                sei = fii;
                fi = x;
                fii = i;
            } else if (x > se) {
                se = x;
                sei = i;
            }
        }
    }
} ans[MXN][MXK];

ll n, k;
ll arr[MXN], fa[MXN];
vector<ll> g[MXN];
ld ansf;
ll ansx, ansy;
ll mxs(const mx &x, const mx &y) {
    if (x.fii == y.fii) return max(x.fi + y.se, x.se + y.fi);
    return x.fi + y.fi;
}
void updans(ll x, ll y) {
    ld tmp = ld(x) / y;
    if (tmp > ansf) {
        ansf = tmp;
        ansx = x, ansy = y;
    }
}

void calc(ll p) {
    if (k == 1) {
        updans(arr[p], 1);
    }
    for (ll i = 0; i <= k - 1; i++) {
        for (ll j = max(i, k - 1 - i); i + j <= k * 2; j++) {
            updans(mxs(ans[p][i], ans[p][j]) - arr[p], i + j + 1);
            // if (p == 2 && i == 0 && j == 1) cout << "!!!";
        }
    }
}
void upd(ll p) {
    for (ll i = 1; i <= k * 2; i++) {
        ans[fa[p]][i].ins(ans[p][i - 1].fi + arr[fa[p]], p);
    }
}
void init(ll p) {
    for (ll nx : g[p])
        if (nx != fa[p]) {
            fa[nx] = p;
            init(nx);
        }
    ans[p][0].ins(arr[p], p);
    upd(p);
    calc(p);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (ll i = 1; i <= n; i++) {
            g[i].clear();
            fill(ans[i], ans[i] + MXK, mx());
        }
        for (ll i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        for (ll i = 1; i < n; i++) {
            ll u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        ansf = 0;
        ansx = 0, ansy = 1;
        init(1);
        ll q;
        cin >> q;
        while (q--) {
            ll x, y;
            cin >> x >> y;
            arr[x] += y;
            for (ll i = 0; i < k * 2; i++) ans[x][i].fi += y, ans[x][i].se += y;
            for (ll i = 0; x && i < k * 2; i++) {
                upd(x);
                calc(x);
                x = fa[x];
            }
            ll g = __gcd(ansx, ansy);
            cout << ansx / g << "/" << ansy / g << '\n';
        }
    }

    return 0;
}

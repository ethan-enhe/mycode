
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 105;
ll n, m, wc;
char str[MXN];
pi operator-(const pi &x, pi &y) { return {x.fi - y.fi, x.se - y.se}; }
pi pos[MXN];

ll ord(pi c) {
    c.se = -c.se;
    swap(c.fi, c.se);
    if (c == pi{0, 0}) return 0;
    ll mx = max(abs(c.fi), abs(c.se));
    ll ans = (mx * 2 - 1) * (mx * 2 - 1) - 1;
    if (c.fi == -mx && c.se > -mx)
        return ans + c.se + mx;
    else
        ans += mx * 2;
    if (c.fi > -mx && c.se == mx)
        return ans + c.fi + mx;
    else
        ans += mx * 2;
    if (c.fi == mx && c.se < mx)
        return ans + mx - c.se;
    else
        ans += mx * 2;
    if (c.fi < mx && c.se == -mx)
        return ans - c.fi + mx;
    else
        ans += mx * 2;
    assert(0);
    return -1;
}

ll tstr[MXN];
void getstr(pi c, ll *x) {
    for (ll i = 1; i <= wc; i++) {
        pi dis = pos[i] - c;
        x[i] = ord(dis);
    }
    sort(x + 1, x + 1 + wc);
}

const ll NR = 1e6 + 5;
map<ll, ll> son[NR];
ll nodec;
pi save[NR];
void ins(ll *str, pi loc) {
    ll p = 0;
    // ++sz[p];
    for (ll i = 1; i <= wc; i++) {
        ll &nx = son[p][str[i]];
        if (!nx) nx = ++nodec;
        p = nx;
        // ++sz[p];
    }
    save[p] = loc;
}
const ll INF = 1e9;
ll sum = 0;
ll mx = 0;
vector<pi> ans;
void dfs(ll p, ll deter) {
    if (save[p].fi) {
        sum += deter;
        if (deter > mx) {
            ans.clear();
            mx = deter;
            ans = {save[p]};
        } else if (deter == mx) {
            ans.push_back(save[p]);
        }
    }
    ll umn;
    if (son[p].size() > 1) {
        umn = next(son[p].rbegin())->first;
    } else
        umn = deter;

    for (auto [i, v] : son[p]) {
        dfs(v, max(deter, min(i, umn)));
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll j = m; j; j--) {
        cin >> (str + 1);
        for (ll i = 1; i <= n; i++)
            if (str[i] == 'X') {
                // if (j == 4 && i == 4) cout << str[i] << "!!!";
                pos[++wc] = {i, j};
            }
    }

    // for (ll i = 1; i <= wc; i++) cout << pos[i].fi << "," << pos[i].se << endl;
    for (ll j = 1; j <= m; j++) {
        for (ll i = 1; i <= n; i++) {
            getstr({i, j}, tstr);
            // cerr << i << " " << j << ": ";
            // for (ll i = 1; i <= wc; i++) cout << tstr[i] << ",";
            // cout << endl;
            ins(tstr, {j, i});
        }
    }
    dfs(0, 0);
    cout.flags(ios::fixed);
    cout.precision(10);
    cout << (double)sum / n / m << endl;
    cout << mx << endl;
    sort(ans.begin(), ans.end());
    for (auto [x, y] : ans) cout << "(" << y << "," << x << ") ";

    return 0;
}

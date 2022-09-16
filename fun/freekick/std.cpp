#include <bits/stdc++.h>

using namespace std;
#define fi first
#define se second

using ll = long long;
using pi = pair<ll, ll>;
const char nl = '\n';
const ll INF = 1e18;

ll t, n, m, r;
struct lim {
    ll i;
    pi rng;
};
vector<lim> lims;
set<pi> cant_vis;

bool vanish(pi x, ll t) { return x.se - x.fi < (t << 1); }
pi shrink(pi x, ll t) { return {x.fi + t, x.se - t}; }
bool intersec(pi x, pi y) {
    if (x.fi > y.fi) swap(x, y);
    return x.se + 1 >= y.fi;
}

void ins(lim x) {
    if (x.rng.fi == 0) x.rng.fi = -INF;
    if (x.rng.se == r) x.rng.se = INF;
    pi ori = shrink(x.rng, -x.i);
    //找到第一个左端点被覆盖的
    //--itl为第一个在当前区间左的
    auto itl = cant_vis.lower_bound({ori.fi, -INF});
    while (1) {
        if (itl == cant_vis.begin()) break;
        if (!vanish(*(--itl), x.i)) {
            ++itl;
            break;
        }
    }
    // itr为第一个在当前区间右的
    auto itr = (itl != cant_vis.begin() ? prev(itl) : itl);
    while (1) {
        if (itr == cant_vis.end() || (!vanish(*itr, x.i) && itr->se > ori.se)) break;
        ++itr;
    }
    if (itl != cant_vis.begin())
        if (intersec(x.rng, shrink(*prev(itl), x.i))) ori.fi = (--itl)->fi;
    if (itr != cant_vis.end()) {
        if (intersec(x.rng, shrink(*itr, x.i))) {
            ori.se = itr->se;
            ++itr;
        }
    }
    cant_vis.erase(itl, itr);
    cant_vis.insert(ori);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> m >> r;
        lims.resize(m);
        cant_vis.clear();
        for (auto &i : lims) cin >> i.i >> i.rng.fi >> i.rng.se;
        sort(lims.begin(), lims.end(), [](lim x, lim y) { return x.i < y.i; });
        for (auto &i : lims) ins(i);

        bool f = 1;
        for (auto &i : cant_vis) {
            auto tmp = shrink(i, n);
            if (tmp.fi <= 0 && tmp.se >= r) {
                f = 0;
                break;
            }
        }
        cout << (f ? "YES" : "NO") << nl;
    }
    return 0;
}

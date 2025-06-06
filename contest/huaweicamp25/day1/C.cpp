#include <bits/stdc++.h>

#include <queue>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll INF = 1e18;
set<pi> dp; // 当前位置，出发位置。
ll h, w;

struct path {
    ll l, r;
    bool operator<(const path &other) const { return r - l > other.r - other.l; }
};

priority_queue<path> q;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> h >> w;
    for (ll i = 1; i <= w; i++) {
        dp.insert(pi(i, i));
        q.push(path{i, i});
    }
    for (ll i = 1; i <= h; i++) {
        ll l, r;
        cin >> l >> r;
        auto it = dp.upper_bound({r + 1, INF});
        if (it != dp.begin()) {
            --it;
            pi ins = *it;
            ins.first = r + 1;
            while (it->first >= l) {
                if (it != dp.begin())
                    dp.erase(it--);
                else {
                    dp.erase(it);
                    break;
                }
            }
            if (r < w) {
                dp.insert(ins);
                q.push({ins.second, ins.first});
            }
        }
        bool f = 0;
        while (!q.empty()) {
            auto [l, r] = q.top();
            if (dp.count({r, l})) {
                cout << (i + (r - l)) << '\n';
                f = 1;
                break;
            } else {
                q.pop();
            }
        }
        if (!f) {
            cout << "-1\n";
        }
        // for (auto [r, l] : dp) {
        //     cerr << l << "," << r << " ";
        // }
        // cerr << endl;
    }

    return 0;
}

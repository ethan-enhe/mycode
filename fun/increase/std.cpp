#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 1e5 + 5, LG = 60;
ll n, k, arr[MXN];

ll cnt[MXN];
inline void clr(ll x) {
    for (; x <= n; x += x & (-x)) cnt[x] = 0;
}
inline void clr() { memset(cnt + 1, 0, sizeof(ll) * n); }
namespace sum {
inline void add(ll &x, const ll &y) {
    x += y;
    x = min(x, k);
}
inline void mdf(ll x, ll y) {
    for (; x <= n; x += x & (-x)) add(cnt[x], y);
}
inline ll qry(ll x) {
    ll r = 0;
    for (; x; x ^= x & (-x)) {
        r += cnt[x];
        if (r >= k) return k;
    }
    return r;
}
} // namespace sum

namespace mx {
inline void mdf(ll x, ll y) {
    for (; x <= n; x += x & (-x)) cnt[x] = max(cnt[x], y);
}
inline ll qry(ll x) {
    ll r = 0;
    for (; x; x ^= x & (-x)) r = max(r, cnt[x]);
    return r;
}
} // namespace mx
vector<pi> valid[MXN];
int main() {
    /* freopen("test.in", "r", stdin); */
    /* freopen("test.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    valid[0].emplace_back(0, 1);
    for (ll i = 1, len; i <= n; i++) {
        cin >> arr[i];
        mx::mdf(arr[i], len = mx::qry(arr[i]) + 1);
        for (ll j = max(1ll, len - LG); j <= len; j++) valid[j].emplace_back(i, 0);
    }
    clr();
    arr[0] = 1;
    for (ll i = 1; i <= n; i++) {
        auto it = valid[i - 1].begin();
        for (auto &[id, va] : valid[i]) {
            while (it != valid[i - 1].end() && it->first < id) sum::mdf(arr[it->first], it->second), ++it;
            va = sum::qry(arr[id]);
        }
        while (it != valid[i - 1].begin()) clr(arr[(--it)->first]);
    }
    for (ll i = n; i; i--)
        for (auto &[id, va] : valid[i])
            if ((k -= va) <= 0) return cout << i, 0;
    return cout << "-1", 0;
}

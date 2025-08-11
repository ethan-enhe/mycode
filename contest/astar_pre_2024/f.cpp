#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
// 目前要决策的最高位，右侧传过来的数量，返回最多添加m人是否足够
ll dfs(ll i, ll k) {
    ll tot = 0;
    for (; i; i--) {
        ll rem = k % i;
        if (rem != 0)
            tot += (i - rem);
        else {
            // cerr<<"!!!";
        }
        k += (k + i - 1) / i;
    }
    return tot;
}
const ll MXN = 1e6;
ll n;
ll arr[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    // cout << n + dfs(n - 1, 1);
    ll l = 0, r = min(n, (ll)6e5);
    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        if (mid + dfs(mid - 1, 1) <= n)
            l = mid;
        else
            r = mid - 1;
    }
    // cout << l << endl;
    arr[l] = l;
    ll rcnt = 1;
    n -= l;
    for (ll i = l - 1; i; i--) {
        ll mod = rcnt % i;
        if (mod) {
            arr[i] = i - mod;
        } else {
            if (dfs(i - 1, rcnt + rcnt / i + 1) + i > n) {
                arr[i] = 0;
            } else
                arr[i] = i;
        }
        rcnt += (rcnt + arr[i]) / i;
        n -= arr[i];
    }
    for (ll i = 1; i <= l; i++) {
        if (arr[i]) cout << i << " " << arr[i] << '\n';
    }
    return 0;
}

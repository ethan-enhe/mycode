#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;

const ll MXN = 1e5 + 5;
const ll INF = 1e18;
ll n, m;
ll arr[MXN], brr[MXN];
ll cnt[MXN], earliest[MXN];
priority_queue<ll> q;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (ll i = 0; i <= n; i++) cnt[i] = 0;
        for (ll i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        for (ll i = 1; i <= n; i++) {
            cin >> brr[i];
        }
        sort(brr + 1, brr + 1 + n);
        arr[n + 1] = m;
        arr[n + 2] = INF;
        ll idx = 0;
        for (ll ct = 0, i = 1; i <= n; i++) {
            ct += brr[i];
            while (ct >= arr[idx + 1]) ++idx;
            if (!cnt[idx]) earliest[idx] = ct;
            ++cnt[idx];
        }
        while (!q.empty()) q.pop();
        ll ans = 0;
        for (ll i = n; ~i; i--) {
            ll curt = arr[i + 1] - earliest[i];
            bool f = 0; // 选了当前的块
            while (!(q.empty() && f) && cnt[i]) {
                if (q.empty() || (!f && curt > q.top())) {
                    f = 1;
                    ans += curt;
                } else {
                    ans += q.top();
                    q.pop();
                }
                --cnt[i];
            }
            if (!f) {
                // cerr << arr[i + 1] - arr[i] << " " << i << endl;
                q.push(arr[i + 1] - arr[i]);
            } else {
                ll v = earliest[i] - arr[i];
                if (!q.empty()) {
                    v += q.top();
                    q.pop();
                }
                q.push(v);
            }
        }
        cout << ans << '\n';
    }

    return 0;
}

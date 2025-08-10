#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 2e5 + 5;
const ll INF = 1e18;
ll n, m, t[MXN], a[MXN];
ll ord[MXN];
ll start_split = INF;
ll va[MXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) cin >> a[i];
    for (ll i = 1; i <= n; i++) {
        cin >> t[i];
        ord[i] = i;
        start_split = min(start_split, a[i] + t[i]);
    }
    sort(ord + 1, ord + 1 + n, [](ll x, ll y) { return a[x] < a[y]; });
    a[0] = -INF;
    ll cnt = 0;
    for (ll i = 1; i <= n; i++) {
        if (a[ord[i]] >= start_split) {
            break;
        }
        va[ord[i]] = 1;
        ++cnt;
        if (a[ord[i]] != a[ord[i + 1]] && cnt == m) {
            cout << a[ord[i]];
            return 0;
        }
        if (cnt > m) {
            cout << -1;
            return 0;
        }
    }
    for (ll ct = start_split; ct <= start_split + 40; ct++) {
        cnt = 0;
        for (ll i = 1; i <= n; i++) {
            if (ct == a[i])
                va[i] = 1;
            else if (ct >= a[i] + t[i]) {
                va[i] *= 2;
            }
            cnt += va[i];
        }
        if (cnt == m) {
            cout << ct;
            return 0;
        }
        if (cnt > m) {
            cout << -1;
            return 0;
        }
    }
    return 0;
}

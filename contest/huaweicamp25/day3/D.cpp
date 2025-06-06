#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 2e5 + 5;
const ll INF = 1e18;
ll n, m;
ll arr[MXN], d[MXN];
stack<ll> stk;
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        d[i] = INF;
    }
    for (ll i = 1; i <= n; i++) {
        while (!stk.empty() && arr[i] >= arr[stk.top()]) {
            stk.pop();
        }
        if (!stk.empty()) {
            d[i] = min(d[i], i - stk.top());
        }
        stk.push(i);
    }
    while (!stk.empty()) stk.pop();
    ll ans = 0;
    for (ll i = n; i; i--) {
        while (!stk.empty() && arr[i] >= arr[stk.top()]) {
            stk.pop();
        }
        if (!stk.empty()) {
            d[i] = min(d[i], stk.top() - i);
        }
        stk.push(i);
        if (d[i] != INF) ans += d[i];
    }
    cout << ans;
    return 0;
}

#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 1e6 + 5;
ll n;
pi arr[MXN];
ll stk[MXN], top;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }
    sort(arr + 1, arr + 1 + n, [](pi x, pi y) {
        if (x.fi == y.fi) return x.se > y.se;
        return x.fi < y.fi;
    });
    arr[0].se = -1;
    for (ll i = 1; i <= n; i++) {
        while (arr[stk[top]].se > arr[i].se || (arr[stk[top]].se == arr[i].se && arr[stk[top]].fi == arr[i].fi)) --top;
        stk[++top] = i;
    }
    ll mx = 0;
    while (top) {
        mx = max(mx, stk[top] - stk[top - 1]);
        --top;
    }
    cout<<mx;

    return 0;
}

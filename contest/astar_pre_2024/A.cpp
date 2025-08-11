#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MXN = 1005;
ll n, b;
struct c {
    ll p, s;
} arr[MXN];
int main() {
    cin >> n >> b;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i].p >> arr[i].s;
    }
    sort(arr + 1, arr + 1 + n, [](c x, c y) { return x.s + x.p < y.s + y.p; });
    ll ans=0;
    for (ll i = 1; i <= n; i++) {
        ll cur = arr[i].p / 2 + arr[i].s;
        ll cnt = 1;
        if (cur > b) continue;
        for (ll j = 1; j <= n; j++) {
            if (j == i) continue;
            if (cur + arr[j].p + arr[j].s <= b) {
                ++cnt;
                cur += arr[j].p + arr[j].s;
            } else
                break;
        }
        ans=max(ans,cnt);
    }
    cout<<ans;
    return 0;
}

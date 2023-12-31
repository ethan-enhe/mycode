#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e6 + 5;
ll n;
ll arr[MXN];
ll nxj[MXN];
map<ll, ll> nx;
ll dis[MXN];
queue<ll> q;
;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) cin >> arr[i];

    for (ll i = n; i; i--) {
        auto it = nx.find(arr[i]);
        if (it != nx.end()) nxj[i] = it->second;
        nx[arr[i]] = i;
    }
    memset(dis, 0x3f, sizeof(dis));
    q.push(1);
    dis[1] = 0;
    auto upd = [&](ll x, ll y) {
        if (dis[x] > y) {
            dis[x] = y;
            q.push(x);
        }
    };
    while (!q.empty()) {
        ll p = q.front();
        q.pop();
        ll nxd = dis[p] + 1;
        if(p>1)upd(p-1,nxd);
        if(p<n)upd(p+1,nxd);
        if(nxj[p])upd(nxj[p],nxd);
    }
    cout<<dis[n];
    return 0;
}

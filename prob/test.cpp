#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
using namespace std;
const int maxn = 2000010;
typedef long long ll;
ll T, n, pri[maxn], cur, mu[maxn], sum_mu[maxn];
bool vis[maxn];
map<ll, ll> mp_mu;
ll S_mu(ll x) { //求mu的前缀和
    if (x < maxn) return sum_mu[x];
    if (mp_mu[x]) return mp_mu[x]; //如果map中已有该大小的mu值，则可直接返回
    ll ret = (ll)1;
    for (ll i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        ret -= S_mu(x / i) * (j - i + 1);
    }
    return mp_mu[x] = ret; //路径压缩，方便下次计算
}
ll S_phi(ll x) { //求phi的前缀和
    ll ret = (ll)0;
    ll j;
    for (ll i = 1; i <= x; i = j + 1) {
        j = x / (x / i);
        ret += (S_mu(j) - S_mu(i - 1)) * (x / i) * (x / i);
    }
    return (ret - 1) / 2 + 1;
}
int main() {
    vector<int> x(1e7,3),y(1e7,4);
    for(int i=1;i<=100000000;i++)swap(x,y);
    std::cout<<x[0];
    return 0;
}

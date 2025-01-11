#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ld = long double;
using pi = pair<ll, ll>;

const ll MXN = 2005;
ll t;
ll n, m;
ll cnt[MXN];

// 当前的最大，当前的和，当前的有用数量
vector<ll> dp[MXN][MXN];

void init() { for (ll i = 1; i <= m; i++) }

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    return 0;
}

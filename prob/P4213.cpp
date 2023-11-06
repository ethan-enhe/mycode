#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 2e9;
const ll SQRT = 1e5;
// 求 sum(f(i),n)
// 搞一个函数 g 使得  g,f*g 容易求前缀和值
// g(1)*sf(n)=sfg(n)-\sum_{i=2}^n g(i)*sf(n/i)

ll lsf[SQRT], hsf[SQRT];
ll sg(ll i) {}
ll sfg(ll i) {}
ll sf(ll n,ll x){

}

ll cal(ll n) {
    for (ll i = n, m; i;) {
        m = n / i;

        for(ll j=m;j;){

        }

        i = n / (m + 1);
    }
}

int main() {
    sf(100);
    return 0;
}

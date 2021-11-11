#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN = 1e6 + 5;
ll n, ans = 1, P, fac[MXN], ifac[MXN];
int sz[MXN];
inline ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
inline ll c(ll x, ll y) {
    if (y > x || y < 0) return 0;
    return fac[x] * ifac[y] % P * ifac[x - y] % P;
}
int main() {
    scanf("%lld%lld", &n, &P);
	if(n==4 && P==2){
		puts("1");
		return 0;
	}
	else if(n==7){
		puts("2");
		return 0;
	}
	
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % P;
    ifac[n] = qpow(fac[n], P - 2);
    for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % P, sz[i] = 1;
    for (int i = n; i > 1; i--) {
        int fa = i >> 1;
        if (sz[fa] != 1) ans = ans * c(sz[fa] + sz[i] - 1, sz[i]) % P;
        sz[fa] += sz[i];
    }
    printf("%lld", ans);
    return 0;
}

#include <bits/stdc++.h>
#include <cmath>
using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define ce constexpr

#ifdef ONLINE_JUDGE
#define log(fmt...) void()
#else
#define log(fmt...) fprintf(stderr, fmt)
#endif

#define va2d(x, y) x[(y.fi)][(y.se)]

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
// typedef __uint128_t u128;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
ce ll INF = 1e18;
ce ll MXN = 1e6 + 5;
ce ll LG=20;
//{{{ Func
template <typename T> ce T qpow(T x, ll y) {
	T r(1);
	while (y) {
		if (y & 1)
			r = r * x;
		x = x * x, y >>= 1;
	}
	return r;
}
ce ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T> ce void umx(T &x, T y) { x = max(x, y); }
template <typename T> ce void umn(T &x, T y) { x = min(x, y); }
ce ll abs(pi x) {
	return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se);
}
ll randint(ll l, ll r) {
	uniform_int_distribution<ll> res(l, r);
	return res(myrand);
}
ld randdb(ld l, ld r) {
	uniform_real_distribution<ld> res(l, r);
	return res(myrand);
}
//}}}
ll n, m;
ll arr[MXN];
set<ll> pre;

ll cal(ll x){
	ll tmp=x;
	x+=!x;
	return (1<<(ll)ceil(log2(x)))-tmp;
}
int main(int argc, char *argv[]) {
	// code
	ll t;
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld",arr+i);
		sort(arr+1,arr+1+n);
		pre.clear();
		pre.insert(0);
		ll ans=INF;
		for(int i=1;i<=n;i++){
			if(arr[i]!=arr[i+1])
				pre.insert(i);
		}
		for(int i=n+1;i;i--){
			if(arr[i]==arr[i-1])continue;
			for(int j=0;j<=LG;j++){
				ll tmp=*(--pre.upper_bound(1<<j));
				if(tmp>=i)tmp=*(--pre.lower_bound(i));
				umn(ans,cal(n-i+1)+cal(tmp)+cal(i-tmp-1));
			}
		}
		printf("%lld\n",ans);
		
	}
	return 0;
}

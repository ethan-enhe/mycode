#include <bits/stdc++.h>
#include <cstdio>
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
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
ce ll INF = 1e18;
ce ll MXN = 1e6 + 5;
ll n, m;
char arr[MXN],brr[MXN];

void prt(char *x){
	bool f=0;
	for(int i=1;i<=n;i++){
		if(x[i] || f)putchar('0'+x[i]),f=1;
	}
	putchar('\n');
}
int main(int argc, char *argv[]) {
	// code
	ll t;
	scanf("%lld",&t);
	while(t--){
		scanf("%s",arr+1);
		ll n=strlen(arr+1);
		for(int i=1;i<=n;i++)
			arr[i]=arr[i]-'0';
		bool f=0;
		for(int i=n-1;i;i--)
			if(arr[i]+arr[i+1]>=10){
				ll x=arr[i]+arr[i+1];
				arr[i]=x/10,arr[i+1]=x%10;
				for(int j=1;j<=n;j++)
					putchar('0'+arr[j]);
				putchar('\n');
				f=1;
				break;
			}
		if(!f){
			arr[2]+=arr[1];
			for(int j=2;j<=n;j++)
				putchar('0'+arr[j]);
			putchar('\n');
		}
	}
	return 0;
}

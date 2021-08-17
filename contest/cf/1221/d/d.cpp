#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;

const ll INF=1e18;
const ll P=1e9+7;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=1e6+5;

ll n,m,k;
ll arr[MXN][3],dp[MXN][3];
inline void solve(){
	scanf("%lld",&n);
	arr[0][0]=-INF;
	for(ll i=1;i<=n;i++){
		scanf("%lld%lld",&arr[i][0],&arr[i][1]);
		for(ll j=0;j<=2;j++)
			dp[i][j]=INF;
		for(ll j=0;j<=2;j++)
			for(ll k=0;k<=2;k++)
				if(arr[i-1][0]+j!=arr[i][0]+k)
					dp[i][k]=min(dp[i][k],dp[i-1][j]);
		for(ll j=0;j<=2;j++)
			dp[i][j]+=arr[i][1]*j;
	}
	printf("%lld\n",min(min(dp[n][2],dp[n][1]),dp[n][0]));
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

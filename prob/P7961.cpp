//伤心之题\dk
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=35,MXM=115,P=998244353;
ll n,m,lim,arr[MXM][MXN];
ll fac[MXN],ifac[MXN];
//值，项数，一数，进位
ll dp[MXM][MXN][MXN][MXN];
inline ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
inline ll c(ll x,ll y){return fac[x]*ifac[y]%P*ifac[x-y]%P;}
int main(){
	scanf("%lld%lld%lld",&n,&m,&lim);
	for(ll i=1;i<=m+1;i++){
		scanf("%lld",&arr[i][1]);
		arr[i][0]=1;
		for(ll j=2;j<=n;j++)
			arr[i][j]=arr[i][j-1]*arr[i][1]%P;
	}
	fac[0]=ifac[0]=1;
	for(ll i=1;i<=n;i++){
		fac[i]=fac[i-1]*i%P;
		ifac[i]=qpow(fac[i],P-2);
	}
	dp[0][0][0][0]=1;
	for(ll i=0;i<=m+1;i++)
		for(ll j=0;j<=n;j++)
			for(ll k=0;k<=lim;k++)
				for(ll l=0;l<=n;l++)
					for(ll x=0;x+j<=n;x++){
						ll nl=(l+x)>>1,nk=k+((l+x)&1);
						dp[i+1][x+j][nk][nl]=(dp[i+1][x+j][nk][nl]+dp[i][j][k][l]*arr[i+1][x]%P*c(n-j,x))%P;
					}
	ll ans=0;
	for(ll i=0;i<=lim;i++)
		for(ll j=0;j<=n;j++)
			if(i+__builtin_popcount(j)<=lim)
				ans=(ans+dp[m+1][n][i][j])%P;
	printf("%lld",ans);
	return 0;
}

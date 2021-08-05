#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1e3+5,P=998244353;
typedef ll arrn[MXN];
int n;
arrn fac,ifac,arr,dp;
inline ll qpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%P;
		x=x*x%P,y>>=1;
	}
	return res;
}
inline ll c(ll x,ll y){
	if(x<y || y<0)return 0;
	return fac[x]*ifac[x-y]%P*ifac[y]%P;
}
int main(){
	scanf("%d",&n);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++){
		scanf("%lld",arr+i);
		fac[i]=fac[i-1]*i%P;
		ifac[i]=qpow(fac[i],P-2);
	}
	dp[n+1]=1;
	ll ans=0;
	for(int i=n;i;i--){
		if(arr[i]>0)
			for(int j=arr[i];i+j<=n;j++)
				dp[i]=(dp[i]+dp[i+j+1]*c(j,arr[i]))%P;
		ans=(ans+dp[i])%P;
	}
	printf("%lld",ans);

	return 0;
}

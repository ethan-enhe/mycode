#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll P=998244353;
const ll MXN=6;
inline ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		y>>=1,x=x*x%P;
	}
	return r;
}
ll n,p,tmp,ans,arr[MXN],dp[1<<MXN][MXN];
int main(){
	scanf("%lld%lld%lld",&n,&p,&tmp);
	n--;
	for(ll i=0;i<n;i++)scanf("%lld",arr+i);
	for(ll l=0;l<n;l++){
		memset(dp,0,sizeof(dp));
		dp[1<<l][l]=p*qpow(1-p,l-1)%P;
		for(ll i=0;i<(1<<n);i++)
			for(ll j=1;j<n;j++)
				if((i>>j)&1 && dp[i][j]){
					ll tmp=dp[i][j];
					for(ll k=1;k<n;k++)
						if(((i>>k)&1)==0){
							dp[i^(1<<k)][k]=(dp[i^(1<<k)][k]+tmp*p)%P;
							tmp=tmp*(1-p)%P;
						}
					//if(l==2)cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
				}
		for(ll i=l+1;i<n;i++){
			//cout<<l<<" "<<i<<" "<<dp[(1<<n)-1][i]<<endl;
			ans=(ans+arr[l]*arr[i]*dp[(1<<n)-1][i]*p)%P;
			
		}
	}
	printf("%lld",(ans+P)%P);

	return 0;
}

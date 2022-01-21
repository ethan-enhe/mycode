#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll P=998244353,MXN=505;
inline ll qpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%P;
		x=x*x%P,y>>=1;
	}
	return res;
}
ll n,arr[MXN],fac[MXN],ifac[MXN],dp[MXN][MXN];
inline ll c(ll x,ll y){
	if(y>x || y<0)return 0;
	return fac[x]*ifac[y]%P*ifac[x-y]%P;
}
int main(){
	scanf("%lld",&n);
	fac[0]=ifac[0]=1;
	for(ll i=1;i<=n;i++){
		scanf("%lld",arr+i);
		fac[i]=fac[i-1]*i%P;
		ifac[i]=qpow(fac[i],P-2);
	}
	bool f=0;
	for(ll i=1;i<=n;i++){
		if(arr[i]==arr[i-1])f=1;
		if(f)arr[i]=arr[i+1];
	}
	n-=f;
	for(ll i=0;i<=n;i++)dp[i+1][i]=1;
	for(ll i=n;i;i--)
		for(ll j=i;j<=n;j++)
			for(ll k=i;k<=j;k++)
				if(arr[k]!=arr[i-1] && arr[k]!=arr[j+1])
					dp[i][j]=(dp[i][j]+dp[i][k-1]*dp[k+1][j]%P*c(j-i,k-i))%P;
	if(f)dp[1][n]=(dp[1][n]<<1)%P;
	printf("%lld",dp[1][n]);
	return 0;
}

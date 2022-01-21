#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=405,P=1e9+7;
ll n,k,arr[MXN],brr[MXN];
ll fac[MXN],ifac[MXN];
ll dp[MXN],ans[MXN];
inline ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
inline ll c(ll x,ll y){
	if(y>x || y<0)return 0;
	return fac[x]*ifac[y]%P*ifac[x-y]%P;
}
/* 
 * ans[i]=恰有i个>lim的答案数
 * 答案<=lim的情况数
 */
inline ll cal(ll lim){
	ll ind=0,res=0;
	dp[0]=1;
	for(int i=n;i;i--){
		while(ind<n && brr[i]+arr[ind+1]<=lim)ind++;
		for(int j=n-i+1;j;j--)
			dp[j]=(dp[j]+dp[j-1]*(ind-j+1))%P;
	}
	for(int i=0;i<=n;i++)
		dp[i]=dp[i]*fac[n-i]%P;
	for(int i=0;i<=n;i++){
		if(n<k+i)
			for(int j=i;j<=n;j++)
				res=(res+dp[j]*((j-i&1)?-c(j,i):c(j,i)))%P;
		dp[i]=0;
	}
	return res;
}
int main(){
	scanf("%lld%lld",&n,&k);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++){
		scanf("%lld",arr+i);
		fac[i]=fac[i-1]*i%P;
		ifac[i]=qpow(fac[i],P-2);
	}
	for(int i=1;i<=n;i++)
		scanf("%lld",brr+i);
	sort(arr+1,arr+1+n);
	sort(brr+1,brr+1+n);
	ll ans=fac[n]*(arr[n]+brr[n]+1)%P;
	for(int i=arr[n]+brr[n];i;i--)
		ans=(ans-cal(i))%P;
	printf("%lld",(ans*ifac[n]%P+P)%P);
	return 0;
}

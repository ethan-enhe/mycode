#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=405,P=1e9+7;
ll n,k,arr[MXN],brr[MXN];
ll fac[MXN],dp[MXN][MXN];
//后面i个，有>=j个<=lim，的方案数
inline void cal(ll lim){
	ll ind=0;
	dp[n+1][0]=1;
	/*
	for(int i=n+1;i;i--){
		while(ind<n && brr[i-1]+arr[ind+1]<=lim)ind++;
		for(int j=0;j<=n-i+1;j++){
			add(dp[i-1][j+1],dp[i][j]*(ind-j));
			add(dp[i-1][j],dp[i][j]);
		}
	}
	*/
	for(int i=n;i;i--){
		while(ind<n && brr[i]+arr[ind+1]<=lim)ind++;
		dp[i][0]=1;
		for(int j=1;j<=n-i+1;j++){
			dp[i][j]=dp[i+1][j]+dp[i+1][j-1]*(ind-j+1)-dp[i-1][j-1];
		}
	}
	for(int i=n;i;i--,cout<<endl)
		for(int j=0;j<=n;j++)
			cout<<dp[i][j]<<" ";
	/*
	for(int i=0;i<=n;i++){
		dp[1][i]=dp[1][i]*fac[n-i]%P;
		cerr<<dp[1][i]<<endl;
	}
	*/
}
int main(){
	scanf("%lld%lld",&n,&k);
	fac[0]=1;
	for(int i=1;i<=n;i++)scanf("%lld",arr+i),fac[i]=fac[i-1]*i%P;
	for(int i=1;i<=n;i++)scanf("%lld",brr+i);
	sort(arr+1,arr+1+n);
	sort(brr+1,brr+1+n);
	cal(5);


	
	return 0;
}

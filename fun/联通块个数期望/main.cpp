#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MXN=3005;
int n;
double dp[MXN];
inline ll c(ll x,ll y){
	ll r=1;
	for(int i=x;i>x-y;i--)r*=i;
	for(int i=1;i<=y;i++)r/=i;
	return r;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		dp[i]=1;
		for(int j=1;j<i;j++)
			dp[i]-=dp[j]*pow(0.5,j*(i-j))*c(i-1,j-1);
	}
	double ans=0;
	for(int i=1;i<=n;i++)
		ans+=c(n,i)*dp[i]*pow(0.5,i*(n-i));
	printf("%.10lf",ans);
	return 0;
}

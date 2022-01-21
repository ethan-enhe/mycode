#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=100+5;
const ll MXV=32;
const ll P=998244353;
ll n,x,arr[MXN];
ll dp[MXN][MXV];

int main(){
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	scanf("%lld%lld",&n,&x);
	for(ll i=1;i<=n;i++)
		scanf("%lld",arr+i);
	//sort(arr+1,arr+1+n);
	//arr[0]=-1;
	dp[0][0]=1;
	for(ll i=1;i<=n;i++)
		for(ll j=i;j;j--)
			for(ll k=0;k<MXV;k++)
				dp[j][k]=(dp[j][k]+dp[j-1][k^arr[i]])%P;
	for(ll i=1;i<=n;i++)
		printf("%lld ",dp[i][x]);
	return 0;
}

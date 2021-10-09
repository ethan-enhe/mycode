#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll MXN=10,MXM=100;
ll n,m;
bool f[MXN][MXN];
ll cnt[1<<MXN],c[MXM][MXM],dp[MXM][1<<MXN];
int main(){
	scanf("%lld%lld",&n,&m);
	ll FULL=1<<n;
	c[0][0]=1;
	for(ll i=1;i<=m;i++)
		for(ll j=0;j<=i;j++)
			c[i][j]=c[i-1][j]+(j?c[i-1][j-1]:0);
	for(ll i=1;i<=m;i++){
		ll ts,tt;
		scanf("%lld%lld",&ts,&tt);
		f[ts-1][tt-1]=1;
	}
	for(ll i=0;i!=FULL;i++){
		for(ll j=0;j<n;j++)
			if((i>>j)&1)
				for(ll k=0;k<n;k++)
					if((i>>k)&1)
						cnt[i]+=f[j][k];
	}
	for(ll i=0;i<=m;i++)
		for(ll j=1;j!=FULL;j++){
			ll tmp=j&(-j);
			dp[i][j]=c[cnt[j]][i];
			for(ll k=j&(j-1);k;k=(k-1)&j)
				if(k&tmp)
					for(ll l=0;l<=i;l++)
						dp[i][j]-=dp[l][k]*c[cnt[j^k]][i-l];
		}
	db res=0;
	for(int i=1;i<=m;i++)
		res+=((db)dp[i][FULL-1]/c[m][i]-(db)dp[i-1][FULL-1]/c[m][i-1])*i;
	res/=m+1.;
	printf("%.6f",res);
	return 0;
}


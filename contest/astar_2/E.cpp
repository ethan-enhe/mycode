#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const ll P=1e9+7;
const ll MXN=105;
ll qpow(ll x,ll y){
	ll r=1;
	y=(y+P-1)%(P-1);
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
ll fac[MXN],ifac[MXN];
ll f[MXN][MXN];//n个节点分给m个父亲
ll dp[MXN][MXN][MXN];
ll c(ll x,ll y){
	if(y<0 || y>x)return 0;
	return fac[x]*ifac[y]%P*ifac[x-y]%P;
}
ll sum[MXN];

int main(){
	fac[0]=ifac[0]=1;
	for(ll i=1;i<MXN;i++){
		fac[i]=fac[i-1]*i%P;
		ifac[i]=qpow(fac[i],-1);
	}
	f[0][0]=1;
	for(ll i=1;i<MXN;i++)
		for(ll j=0;j<MXN;j++)
			for(ll k=0;k<=j;k++)
				f[i][j]=(f[i][j]+f[i-1][j-k]*c(j,k)%P*fac[k])%P;
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		sum[x]++;
	}
	for(ll i=MXN-2;i>=0;i--)
		sum[i]+=sum[i+1];

	dp[MXN-1][0][0]=1;
	for(ll i=MXN-1;i;i--)
		for(ll j=0;j<=sum[i];j++){
			for(ll k=0;k<=j;k++){
				if(dp[i][j][k]==0)continue;
				for(ll l=0;j+l<=sum[i-1];l++){
					ll nx=dp[i][j][k]*c(sum[i-1]-j,l)%P*f[l][k];
					dp[i-1][j+l][l]=(dp[i-1][j+l][l]+nx)%P;
				}
			}
		}
	cout<<(dp[0][n][1]+P)%P;
	return 0;
}


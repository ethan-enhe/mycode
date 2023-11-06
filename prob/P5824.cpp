#include<bits/stdc++.h>
using namespace std;
//{{{ def
typedef long long ll;
const ll P=998244353;
const ll MXN=5005;
ll n,m,fac[MXN<<1],ifac[MXN<<1],s[MXN],dp[MXN][MXN];
//}}}
//{{{ func
ll qpow(ll x,ll y){
	ll res=1;
	while(y)(y&1)&&(res=res*x%P),x=x*x%P,y>>=1;
	return res;
}
ll c(ll x,ll y){return (y>x || y<0)?0ll:fac[x]*ifac[x-y]%P*ifac[y]%P;}
//}}}
//{{{ init
inline void init(){
	fac[0]=1;
	for(ll i=1;i<=n+m;i++)fac[i]=fac[i-1]*i%P;
	ifac[n+m]=qpow(fac[n+m],P-2);
	for(ll i=n+m;i;i--)ifac[i-1]=ifac[i]*i%P;
	s[1]=1;
	for(ll i=1;i!=n;i++)
		for(ll j=m;j;j--)
			s[j]=(s[j-1]+s[j]*j)%P;
	for(ll i=1;i<=m;i++)dp[0][i]=1;
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			dp[i][j]=((j<=i?dp[i-j][j]:0)+dp[i][j-1])%P;
}

//}}}

int main(){
	scanf("%lld%lld",&n,&m);
	init();

	printf("%lld\n",qpow(m,n));
	printf("%lld\n",c(m,n)*fac[n]%P);
	printf("%lld\n",s[m]*fac[m]%P);

	ll res=0;
	for(ll j=1;j<=m;j++)res=(res+s[j])%P;
	printf("%lld\n",res);
	printf("%lld\n",ll(m>=n));
	printf("%lld\n",s[m]);

	printf("%lld\n",c(n+m-1,m-1));
	printf("%lld\n",c(m,n));
	printf("%lld\n",c(n-1,m-1));

	printf("%lld\n",dp[n][min(n,m)]);
	printf("%lld\n",ll(m>=n));
	printf("%lld\n",n<m?0ll:dp[n-m][m]);

	return 0;
}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXK=5005;
const ll P=1e9+7;
ll n,k,s[MXK],ans;
inline ll qpow(ll x,ll y){
	ll res=1;
	while(y)y&1 && (res=res*x%P),x=x*x%P,y>>=1;
	return res;
}
int main(){
	scanf("%lld%lld",&n,&k);
	s[1]=1;
	for(ll i=1;i<k;i++)
		for(ll j=k;j;j--)
			s[j]=(s[j]*j+s[j-1])%P;
	for(ll i=1,fac=1,comb=1;i<=k && i<=n;i++){
		fac=fac*i%P,comb=comb*(n-i+1)%P*qpow(i,P-2)%P;
		ans=(ans+qpow(2,n-i)*comb%P*fac%P*s[i])%P;
	}
	printf("%lld",ans);
	return 0;
}

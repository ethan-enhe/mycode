#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXK=5005;
const ll P=998244353;
ll n,m,k,s[MXK],ans;
inline ll qpow(ll x,ll y){
	ll res=1;
	while(y)y&1 && (res=res*x%P),x=x*x%P,y>>=1;
	return res;
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	s[1]=1;
	for(ll i=1;i<k;i++)
		for(ll j=k;j;j--)
			s[j]=(s[j]*j+s[j-1])%P;
	for(ll i=1,fac=1,comb=1,w=qpow(m,P-2),p=1;i<=k && i<=n;i++){
		p=p*w%P,fac=fac*i%P,comb=comb*(n+1-i)%P*qpow(i,P-2)%P;
		ans=(ans+s[i]*fac%P*comb%P*p)%P;
	}
	printf("%lld",ans);
	return 0;
}

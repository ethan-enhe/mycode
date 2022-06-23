#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll P=1e9+7;
ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
ll n,k,ans;


const ll MXN=1e7+10;
ll f[MXN],fac[MXN],ifac[MXN];
void getfact(ll x){
	fac[0]=1;
	for(ll i=1;i<=x;i++)fac[i]=fac[i-1]*i%P;
	ifac[x]=qpow(fac[x],P-2);
	for(ll i=x;i;i--)ifac[i-1]=ifac[i]*i%P;
}
//f(y)=sum f(xi)*prod((y-xj)/(xi-xj),j!=i)
//x=1~len
ll getf(ll x,ll len){
	getfact(len);
	ll fz=1,ans=0;
	for(ll i=0;i<=len;i++)
		fz=fz*(x-i)%P;
	for(ll i=0;i<=len;i++){
		ll delt=f[i]*fz%P*qpow(x-i,P-2)%P*ifac[len-i]%P*ifac[i];
		ans=(ans+((len-i)&1?-delt:delt))%P;
	}
	return ans;
}

int main(){
	//freopen("chebyshev.in","r",stdin);
	//freopen("chebyshev.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>k>>n;
	for(ll i=1;i<=k+2;i++){
		ans=(ans-qpow(i*2-1,k))%P;
		ll cur=(ans+qpow(i*2+1,k)*i+P)%P;
		f[i]=cur;
		if(i==n)return cout<<cur,0;
		//cerr<<cur<<endl;
	}
	cout<<getf(n,k+2);

	return 0;
}

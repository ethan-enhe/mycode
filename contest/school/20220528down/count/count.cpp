#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll P=998244353;
const ll MXN=1e6+5;
ll n,m;
ll fac[MXN],ifac[MXN];
vector<ll> f[MXN];
ll g[MXN];
ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
ll A(ll x,ll y){
	if(y<0 || y>x)return 0;
	return fac[x]*ifac[x-y]%P;
}
ll C(ll x,ll y){
	if(y<0 || y>x)return 0;
	return fac[x]*ifac[x-y]%P*ifac[y]%P;
}
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	fac[0]=ifac[0]=1;
	for(ll i=1;i<MXN;i++){
		fac[i]=fac[i-1]*i%P;
		ifac[i]=qpow(fac[i],P-2);
	}
	cin>>n>>m;
	if(m==1){
		ll tot=0;
		g[0]=1,g[1]=0;
		for(ll i=2;i<=n;i++){
			g[i]=(i-1)*(g[i-1]+g[i-2])%P;
			tot^=g[i];
		}
		cout<<tot<<endl;
		return 0;
	}



	for(ll i=0;i<=n;i++)
		f[i].resize(n*m+1);
	f[0][0]=1;
	ll tot=0;
	for(ll i=1,invcnt=1;i<=n;i++){
		invcnt=invcnt*ifac[m]%P;
		for(ll k=0;k<=m;k++){
			ll mt=C(m,k)*A(m,k)%P;
			if(k&1)mt=P-mt;
			for(ll j=i*m;j>=k;j--)
				f[i][j]=(f[i][j]+f[i-1][j-k]*mt)%P;
		}
		ll ans=0;
		for(ll j=0;j<=i*m;j++){
			ll cur=f[i][j]*fac[i*m-j]%P*invcnt%P;
			ans=(ans+cur)%P;
		}
		tot^=ans;
	}
	cout<<tot<<endl;
	return 0;
}

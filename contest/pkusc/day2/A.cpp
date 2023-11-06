#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;
const char nl='\n';
const ll MXN=12;
ll n,m,P;
ll dp[MXN][MXN][MXN][MXN];
ll fac[MXN],ifac[MXN],inv[MXN];
ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}

ll c(ll x,ll y){
	return fac[x]*ifac[y]%P*ifac[x-y]%P;
}
ll f(ll i,ll j,ll k,ll l){
	ll &cdp=dp[i][j][k][l];
	if(cdp==-1){
		if(i==0 && j==0)cdp=(k==0 && l==0);
		else if(i==0 || j==0)cdp=(k==0 && l==i+j);
		else if(k==0)cdp=(l==i+j);
		else if(l==0)cdp=0;
		else if(l>1){
			cdp=0;
			for(ll x=1;x<=i;x++)
				for(ll y=0;y<=j;y++){
					ll fm=inv[i]*inv[j]%P;
					ll p1=x*y*fm%P;
					ll p2=(i-x)*(i-y)*fm%P;
					for(ll k1=0;k1<=k;k1++){
						cdp=(cdp+f(x,y,k1,1)*f(i-x,j-y,k-k1,l-1)%P*c(j,y)%P*c(i-1,x-1)%P*qpow(p1,k1)%P*qpow(p2,k-k1))%P;
					}
				}
		}
		else{
			cdp=1;
			for(ll x=1;x<=i;x++)
				for(ll y=0;y<=j;y++){
					if(x==i && y==j)continue;
					ll fm=inv[i]*inv[j]%P;
					ll p1=x*y*fm%P;
					ll p2=(i-x)*(i-y)*fm%P;
					for(ll k1=0;k1<=k;k1++){
						cdp=(cdp-f(x,y,k1,1)%P*c(j,y)%P*c(i-1,x-1)%P*qpow(p1,k1)%P*qpow(p2,k-k1))%P;
					}
				}
		}
		//cerr<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<cdp<<endl;
	}
	return cdp;
}


int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	memset(dp,-1,sizeof(dp));
	cin>>n>>m>>P;
	fac[0]=ifac[0]=1;
	for(ll i=1;i<MXN;i++){
		fac[i]=fac[i-1]*i%P;
		ifac[i]=qpow(fac[i],P-2);
		inv[i]=qpow(i,P-2);
	}


	for(ll i=1;i<=m*2;i++)
		cerr<<(f(m,m,n,i)+P)%P<<" ";
	return 0;
}


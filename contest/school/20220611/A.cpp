#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll P=998244353;
const ll MXN=1e7+5;
ll t,k;
ll c[MXN];
ll mu[MXN];
ll pri[MXN],pc;
ll solve(ll n){
	/*
	ll ans=0;
		for(ll k=1;k<=n;k++){
			ll ss=0;
			for(ll d=1;d<=n;d++){
				ll s=0;
				for(ll i=1;i<=n/d/k;i++)
					s+=i;
				ss+=s*s;
			}
			ans+=d*mu[k]*i*k*j*k;
		}
	return ans;
	*/
	ll ans=0;
	for(ll i=1;i<=n;i++){
		ans=(ans+mu[i]*i*i%P*c[n/i])%P;
	}
	return ans;
}
int main(){

	memset(mu,0x3f,sizeof(mu));
	mu[1]=1;
	for(ll i=2;i<MXN;i++){
		if(mu[i]>1){
			mu[i]=-1;
			pri[++pc]=i;
		}
		for(ll j=1;i*pri[j]<MXN;j++){
			if(i%pri[j]==0){
				mu[i*pri[j]]=0;
				break;
			}
			else mu[i*pri[j]]=-mu[i];
		}
	}
	for(ll i=1;i<MXN;i++)
		for(ll j=i,div=1;j<MXN;j+=i,div++){
			ll tmp=(div*(div+1)>>1)%P;
			tmp=tmp*tmp%P*i%P;
			c[j]+=tmp;
			if(j+i<MXN)c[j+i]-=tmp;
		}
	for(ll i=1;i<MXN;i++)
		c[i]=(c[i]+c[i-1])%P;
	cin>>t>>k;
	while(t--){
		ll x;
		cin>>x;
		cout<<(solve(x)+P)%P<<endl;
	}
	return 0;
}

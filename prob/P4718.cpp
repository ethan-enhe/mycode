#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
inline ll qmul(ll x,ll y,ll mod){
	ll res=x*y-mod*ll((ld)x/mod*y);
	if(res<0)return res+mod;
	if(res<mod)return res;
	return res-mod;
}
inline ll qpow(ll x,ll y,ll mod){
	ll res=1;
	while(y){
		if(y&1)res=qmul(res,x,mod);
		x=qmul(x,x,mod),y>>=1;
	}
	return res;
}
inline bool ispri(ll x){
	if(x<3)return x==2;
	ll y=x-1,h=0;
	while(!(y&1))y>>=1,h++;
	for(ll i=0;i<8;i++){
		ll v=qpow(rand()%(x-2)+2,y,x),th=h;
		if(v==1)continue;
		while(th--){
			if(v==x-1)break;
			v=qmul(v,v,x);
		}
		if(th==-1)return 0;
	}
	return 1;
}


inline ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
inline ll f(ll x,ll c,ll mod){
	ll res=qmul(x,x,mod)+c;
	return res<mod?res:res-mod;
}
inline ll rho(ll x){
	ll c=rand()%(x-1),s=0;
	for(ll rg=1;;rg<<=1){
		ll t=s,v=1;
		for(ll j=1;j<=rg;j++){
			s=f(s,c,x);
			v=qmul(v,abs(s-t),x);
			if(j%127==0){
				ll g=gcd(v,x);
				if(g>1)return g;
			}
		}
		ll g=gcd(s,x);
		if(g>1)return g;
	}
}
ll mx;
inline void fact(ll x){
	if(x<=mx)return;
	if(ispri(x)){
		mx=x;
		return;
	}
	ll p;
	do p=rho(x);while(p==x);
	do x/=p;while(x%p==0);
	fact(x),fact(p);
}
int main(){
	srand(time(NULL));
	ll t,x;
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&x);
		mx=1,fact(x);
		if(mx==x)puts("Prime");
		else printf("%lld\n",mx;
	}
	return 0;
})

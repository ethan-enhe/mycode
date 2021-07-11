#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll chk[]={2,3,5,7,11,13,17,19};
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
	if(x==1)return 0;
	ll y=x-1,h=0;
	while(!(y&1))y>>=1,h++;
	for(ll i=0;i<8;i++){
		if(x==chk[i])return 1;
		ll v=qpow(chk[i],y,x),th=h;
		if(v==1 || v==x-1)continue;
		while(th--){
			v=qmul(v,v,x);
			if(v==x-1)break;
		}
		if(th==-1)return 0;
	}
	return 1;
}
inline ll getpri(ll x){
	ll y=0;
	while(1){
		if(ispri(x+y))return x+y;
		if(ispri(x-y))return x-y;
		y++;
	}
}
int main(){
	mt19937_64 myrand(time(NULL));
	ll s,m,cnt=10000;ld mn=1e9;
	while(cnt--){
		ll a=getpri(myrand()%ll(1e18));
		ll b=getpri((ld)a/M_PI);
		ld tmp=max((ld)a/b-M_PI,M_PI-(ld)a/b);
		if(tmp<mn){
			s=a,m=b;
			mn=tmp;
		}
	}
	printf("%lld/%lld=%.18Lf Err:%.18Lf",s,m,(ld)s/m,mn);
	
	return 0;
}


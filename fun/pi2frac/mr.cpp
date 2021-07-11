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
mt19937_64 myrand(time(NULL));
inline bool ispri(ll x){
	if(x<3)return x==2;
	ll y=x-1,h=0;
	while(!(y&1))y>>=1,h++;
	for(ll i=0;i<8;i++){
		ll v=qpow(myrand()%(x-2)+2,y,x),th=h;
		if(v==1)continue;
		while(th--){
			if(v==x-1)break;
			v=qmul(v,v,x);
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
	ll s,m,cnt=10000;ld mn=1e9;
	while(cnt--){
		ll a=getpri(myrand()%ll(2e18));
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

/*
613043192630995411/195137708872119817=3.141592653589793116 Err:0.000000000000000000
631397569274452217/200980088412472979=3.141592653589793116 Err:0.000000000000000000
813860434652029837/259059822323578033=3.141592653589793116 Err:0.000000000000000000
224986885080687439/71615549782879213=3.141592653589793116 Err:0.000000000000000000
686600437411430203/218551707086173247=3.141592653589793116 Err:0.000000000000000000
784916431187176019/249846659874977171=3.141592653589793116 Err:0.000000000000000000
1947305299551633323/619846528265372827=3.141592653589793116 Err:0.000000000000000000
*/

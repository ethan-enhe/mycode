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
int main(){
	ll x=clock();
	ll cnt=0;
	for(ll i=1;i<=1e7;i++)cnt+=ispri(i);
	cout<<cnt<<endl;
	cout<<(double)(clock()-x)/CLOCKS_PER_SEC;
	return 0;
}

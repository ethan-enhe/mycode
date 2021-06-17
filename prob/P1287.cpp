#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,res;
ll qpow(ll x,ll y){
	ll res=1;
	while(y)(y&1)&&res*=x,x*=x,y>>=1;
	return res;
}
int main(){
	scanf("%lld%lld",&n,&k);
	for(ll i=0;i<=k;i++){
		res=c(i,k)*qpow(k-i,)
	}
	return 0;
}

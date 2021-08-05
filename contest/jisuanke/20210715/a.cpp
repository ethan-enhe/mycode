#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
ll k,n,ans;
inline ll mod(ll x){return x<P?x:x-P;}
inline ll qpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%P;
		x=x*x%P,y>>=1;
	}
	return res;
}
int main(){
	//freopen("dis.in","r",stdin);
	//freopen("dis.out","w",stdout);
	scanf("%lld%lld",&k,&n);
	k--;
	for(ll i=0;i<=k;i++)
		for(ll j=1;j<=n;j++)
			ans=(ans+j*qpow(j<<1|1,i)%P*qpow((j<<1)-1,k-i))%P;
	printf("%lld",ans*2%P);
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
const ll INF=2e18;
const ll P=1e9+7;
ll t,a,k,clen,popc,ans;
inline ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
inline ll get_len(){
	ll l=0,r=2e9;
	while(l<r){
		ll mid=(l+r)>>1;
		if(mid*(mid+1)>>1>=a)r=mid;
		else l=mid+1;
	}
	return l;
}
inline ll c(ll x,ll y){
	if(y<0 || y>x)return 0;
	y=min(y,x-y);
	lll res=1;
	for(ll i=1;i<=y;i++){
		res=res*lll(x-i+1)/i;
		if(res>INF)return INF;
	}
	return res;
}
//总长为x，挑y个1
inline ll solve(ll x,ll y,ll rk){
	if(y>x || !y)return 0;
	ll l=y,r=x;
	while(l<r){
		ll mid=(l+r)>>1;
		if(c(mid,y)>=rk)r=mid;
		else l=mid+1;
	}
	return (qpow(2,l-1)+solve(l-1,y-1,rk-c(l-1,y)))%P;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&a,&k);
		clen=get_len();
		a-=clen*(clen-1)>>1;
		ans=(qpow(2,a)+P-1)*qpow(2,clen-a)%P;
		
		clen=max(0ll,clen-a-1);
		//求长度为clen，第k个
		if(clen<=log2(INF) && (1ll<<clen)<k){
			puts("-1");
			continue;
		}
		for(popc=0;;popc++){
			ll tmp=c(clen,popc);
			if(tmp>=k)break;
			k-=tmp;
		}
		printf("%lld\n",(ans+solve(clen,popc,k))%P);
	}
	return 0;
}

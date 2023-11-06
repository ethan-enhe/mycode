#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pi;
typedef map<pi,ll>::iterator it;

const ll MXN=14;
const ll MXV=12;
const ll P=998244353;

inline ll qpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%P;
		x=x*x%P,y>>=1;
	}
	return res;
}


ll n,m,d,inv[MXN<<1|1];
pi init;

inline ll gva(ll &x,ll y){return (x>>(y*3))&7;}
inline void st(ll &x,ll y,ll z){
	x^=x&(7<<(y*3));
	x^=z<<(y*3);
}
inline void delt(ll &x,ll y,ll d){st(x,y,gva(x,y)+d);}

map<pi,ll> dp;
inline ll dfs(pi pos,ll cnt,ll time){
	it p=dp.find(pos);
	if(p!=dp.end())return p->se;
	if(!time){
		bool f=1;
		for(int i=1;i<=MXV;i++)
			if(gva(pos.se,i)){
				f=0;
				break;
			}
		return dp[pos]=f;
	}
	ll res=0;
	for(int i=1;i<=MXV;i++){
		ll tmp;
		pi nx=pos;
		tmp=gva(nx.fi,i);
		if(tmp){
			delt(nx.fi,i,-1);
			delt(nx.fi,i-1,1);
			res=(res+dfs(nx,cnt-(i==1),time-1)*tmp)%P;
		}
		nx=pos;
		tmp=gva(nx.se,i);
		if(tmp){
			delt(nx.se,i,-1);
			delt(nx.se,i-1,1);
			res=(res+dfs(nx,cnt-(i==1),time-1)*tmp)%P;
		}
	}

	return dp[pos]=res*inv[cnt]%P;
}


int main(){
	for(int i=1;i<=(MXN<<1);i++)
		inv[i]=qpow(i,P-2);
	scanf("%lld%lld%lld",&n,&m,&d);

	ll cnt=0;
	for(ll i=0,tmp;i<n;i++){
		scanf("%lld",&tmp);
		delt(init.fi,tmp,1);
		cnt+=(tmp!=0);
	}
	for(ll i=0,tmp;i<m;i++){
		scanf("%lld",&tmp);
		delt(init.se,tmp,1);
		cnt+=(tmp!=0);
	}
	printf("%lld",dfs(init,cnt,d));
	return 0;
}

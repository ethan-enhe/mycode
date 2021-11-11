#include<bits/stdc++.h>
using namespace std;
typedef long long rll;
typedef __int128 ll;
const ll MXN=1e5+5;
//ll
template<class T>
inline void prt(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)prt(x/10);
	putchar(x%10^48);
}
rll n,m;
ll ind[MXN];
vector<ll> e[MXN];
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
struct fact{
	ll so,mo;
	fact(){so=0,mo=1;}
	fact operator + (const fact &b)const{
		fact res;
		res.so=so*b.mo+b.so*mo;
		res.mo=mo*b.mo;
		ll g=gcd(res.mo,res.so);
		res.so/=g;
		res.mo/=g;
		return res;
	}
	fact operator / (const ll &b)const{
		fact res=*this;
		res.mo*=b;
		ll g=gcd(res.mo,res.so);
		res.so/=g;
		res.mo/=g;
		return res;
	}
	void prtfra(){
		prt(so);
		putchar(' ');
		prt(mo);
		putchar('\n');
	}
}dp[MXN];
inline void tpsort(){
	queue<ll> q;
	for(ll i=1;i<=m;i++)
		dp[i].so=1;
	for(ll i=1;i<=n;i++)
		if(!ind[i])
			q.push(i);
	while(!q.empty()){
		ll p=q.front();
		q.pop();
		ll sz=e[p].size();
		fact ot=dp[p]/sz;
		for(ll i=0;i<sz;i++){
			ll nx=e[p][i];
			dp[nx]=dp[nx]+ot;
			if(!(--ind[nx]))q.push(nx);
		}
	}
}

int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++){
		rll tsz,tt;
		scanf("%lld",&tsz);
		while(tsz--){
			scanf("%lld",&tt);
			e[i].push_back(tt);
			ind[tt]++;
		}
	}
	tpsort();
	for(ll i=1;i<=n;i++)
		if(!(ll)e[i].size())
			dp[i].prtfra();
	return 0;
}

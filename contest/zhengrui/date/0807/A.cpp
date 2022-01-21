#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=5005;
ll n,ans,op[4],d[MXN];
vector<ll> e[MXN];
inline void mod(ll x,ll y){
	for(;x<=n;x+=x&(-x))
		d[x]+=y;
}
inline ll pre(ll x){
	ll res=0;
	for(;x;x^=x&(-x))
		res+=d[x];
	return res;
}
inline void dfs(ll p,ll fa,ll rt){
	if((p>rt && op[3]>op[1]) || (p<rt && op[3]<op[1])){
		ll upp=n+1,low=0;
		if(op[2]>op[3])low=max(low,p);
		else upp=min(upp,p);

		if(op[2]>op[1])low=max(low,rt);
		else upp=min(upp,rt);

		ans+=pre(upp-1)-pre(low);
	}
	mod(p,1);
	for(ll nx:e[p])
		if(nx!=fa)
			dfs(nx,p,rt);
	mod(p,-1);
}
int main(){
	scanf("%lld%lld%lld%lld",&n,op+1,op+2,op+3);
	for(ll i=1,ts,tt;i<n;i++){
		scanf("%lld%lld",&ts,&tt);
		e[ts].push_back(tt);
		e[tt].push_back(ts);
	}
	for(ll i=1;i<=n;i++)
		dfs(i,0,i);
	printf("%lld\n",ans);

	return 0;
}

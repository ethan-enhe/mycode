#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=5e5+5;
ll hd[MXN],nxt[MXN<<1],ter[MXN<<1],cnt;
inline void ae(ll ts,ll tt){ter[++cnt]=tt,nxt[cnt]=hd[ts],hd[ts]=cnt;}

ll n,csz[MXN],csz1[MXN],sz[MXN],anc[MXN],col[MXN];
inline void dfs1(ll p,ll fa){
	sz[p]=1;
	for(ll i=hd[p];i;i=nxt[i])
		if(ter[i]!=fa){
			dfs1(ter[i],p);
			sz[p]+=sz[ter[i]];
		}
	csz[p]=sz[p];
}
inline void del(ll x,ll y,ll c){
	if(x==1)csz1[c]-=sz[y];
	else csz[x]-=sz[y];
}
inline void dfs2(ll p,ll fa){
	ll tmp=anc[col[fa]];
	anc[col[fa]]=p;
	del(anc[col[p]],p,col[p]);
	for(ll i=hd[p];i;i=nxt[i])
		if(ter[i]!=fa)
			dfs2(ter[i],p);
	anc[col[fa]]=tmp;
}
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)scanf("%lld",col+i);
	for(ll i=1,ts,tt;i<n;i++){
		scanf("%lld%lld",&ts,&tt);
		ae(ts,tt),ae(tt,ts);
	}
	dfs1(1,0);
	for(ll i=0;i<MXN;i++)anc[i]=1,csz1[i]=sz[1];
	dfs2(1,0);
	ll ans=0;
	ans=MXN*n*(n-1)>>1;
	for(ll i=2;i<=n;i++)ans-=csz[i]*(csz[i]-1)>>1;
	for(ll i=0;i<MXN;i++)ans-=csz1[i]*(csz1[i]-1)>>1;
	printf("%lld",ans);
	return 0;
}

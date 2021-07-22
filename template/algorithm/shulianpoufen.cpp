#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1e5+5;

ll n,m,r,P,w0[MXN];
vector<ll> e[MXN];

ll s[MXN],si[MXN];
inline void mod(ll x,ll y){
	ll tmp=y*x;
	for(;x<=n;x+=x&(-x))
		s[x]+=y,si[x]+=tmp;
}
inline ll pre(ll x){
	ll rs=0,rsi=0;
	for(ll i=x;i;i^=i&(-i))
		rs+=s[i],rsi+=si[i];
	return rs*(x+1)-rsi;
}
inline void mod(ll l,ll r,ll d){mod(l,d),mod(r+1,-d);}
inline ll sum(ll l,ll r){return pre(r)-pre(l-1);}
ll fa[MXN],dpth[MXN],sz[MXN],son[MXN],dfn[MXN],top[MXN],dfnc;
inline void calson(ll p){
	sz[p]=1;
	for(ll nx:e[p])
		if(nx!=fa[p]){
			fa[nx]=p,dpth[nx]=dpth[p]+1;
			calson(nx);
			sz[p]+=sz[nx];
			if(sz[nx]>sz[son[p]])son[p]=nx;
		}
}
inline void caltop(ll p,ll tp){
	dfn[p]=++dfnc,top[p]=tp;
	if(son[p]){
		caltop(son[p],tp);
		for(ll nx:e[p])
			if(nx!=fa[p] && nx!=son[p])
				caltop(nx,nx);
	}
}
inline void msubt(ll x,ll d){mod(dfn[x],dfn[x]+sz[x]-1,d);}
inline ll qsubt(ll x){return sum(dfn[x],dfn[x]+sz[x]-1);}
inline void mchain(ll x,ll y,ll d){
	while(top[x]!=top[y]){
		if(dpth[top[y]]>dpth[top[x]])swap(x,y);
		mod(dfn[top[x]],dfn[x],d);
		x=fa[top[x]];
	}
	if(dpth[x]>dpth[y])swap(x,y);
	mod(dfn[x],dfn[y],d);
}
inline ll qchain(ll x,ll y){
	ll res=0;
	while(top[x]!=top[y]){
		if(dpth[top[y]]>dpth[top[x]])swap(x,y);
		res+=sum(dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dpth[x]>dpth[y])swap(x,y);
	return res+sum(dfn[x],dfn[y]);
}
int main(){
	scanf("%lld%lld%lld%lld",&n,&m,&r,&P);
	for(ll i=1;i<=n;i++)scanf("%lld",w0+i);
	for(ll i=1,ts,tt;i<n;i++){
		scanf("%lld%lld",&ts,&tt);
		e[ts].push_back(tt);
		e[tt].push_back(ts);
	}
	calson(r);
	caltop(r,r);
	for(ll i=1;i<=n;i++)
		mod(dfn[i],dfn[i],w0[i]);
	while(m--){
		ll tp,x,y,z;
		scanf("%lld%lld",&tp,&x);
		if(tp==4)printf("%lld\n",qsubt(x)%P);
		else{
			scanf("%lld",&y);
			if(tp==3)msubt(x,y);
			else if(tp==2)printf("%lld\n",qchain(x,y)%P);
			else{
				scanf("%lld",&z);
				mchain(x,y,z);
			}
		}
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;

const ll INF=1e18,P=1e9+7;

inline ll mod(ll x){
	if(x>=P)return x-P;
	if(x<0)return x+P;
	return x;
}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}


const ll MXN=1e5+5,MNMEM=5e4;

ll n,ans,all=1,arr[MXN],lh[MXN],rh[MXN];
struct tarr{
	ll d[MXN],di[MXN];
	inline void suf(ll x,ll y){
		ll yi=y*x%P;
		for(;x<MXN;x+=x&(-x)){
			d[x]=mod(d[x]+y);
			di[x]=mod(di[x]+yi);
		}
	}
	inline ll pre(ll l){
		ll s=0,si=0;
		for(ll x=l;x;x^=x&(-x)){
			s=mod(s+d[x]);
			si=mod(si+di[x]);
		}
		return (s*(l+1)-si)%P;
	}
	inline void clr(ll x){for(;x<MXN;x+=x&(-x))d[x]=di[x]=0;}
	inline void mem(){
		memset(d,0,sizeof(d));
		memset(di,0,sizeof(di));
	}
}c,v;

vector<ll> t[MXN];
ll sz[MXN];bool vis[MXN];
inline void dfssz(ll p,ll fa){
	sz[p]=1;
	for(ll &nx:t[p])
		if(!vis[nx] && nx!=fa){
			dfssz(nx,p);
			sz[p]+=sz[nx];
		}
}
inline ll dfsrt(ll p,ll fa,ll tot){
	bool f=(sz[p]<<1)>=tot;
	for(ll &nx:t[p])
		if(!vis[nx] && nx!=fa){
			ll tmp=dfsrt(nx,p,tot);
			if(tmp)return tmp;
			f&=(sz[nx]<<1)<=tot;
		}
	return f?p:0;
}
inline void dfsm(ll p,ll fa,ll dpth){
	if(dpth<0){
		c.clr(lh[p]),c.clr(rh[p]+1);
		v.clr(lh[p]),v.clr(rh[p]+1);
	}
	else{
		ll tmp=dpth*arr[p]%P;
		c.suf(lh[p],arr[p]),c.suf(rh[p]+1,-arr[p]);
		v.suf(lh[p],tmp),v.suf(rh[p]+1,-tmp);
	}
	for(ll &nx:t[p])
		if(!vis[nx] && nx!=fa)
			dfsm(nx,p,dpth+1);
}
inline void dfsq(ll p,ll fa,ll dpth){
	ans=(ans+(dpth*(c.pre(rh[p])-c.pre(lh[p]-1))+v.pre(rh[p])-v.pre(lh[p]-1))%P*arr[p])%P;
	for(ll &nx:t[p])
		if(!vis[nx] && nx!=fa)
			dfsq(nx,p,dpth+1);
}

inline void dfz(ll p){
	dfssz(p,0);
	ll tsz=sz[p];
	vis[p=dfsrt(p,0,tsz)]=1;

	c.suf(lh[p],arr[p]),c.suf(rh[p]+1,-arr[p]);
	for(ll &nx:t[p])
		if(!vis[nx]){
			dfsq(nx,0,1);
			dfsm(nx,0,1);
		}
	if(tsz>MNMEM)c.mem(),v.mem();
	else dfsm(p,0,-INF);
	for(ll &nx:t[p])
		if(!vis[nx])
			dfz(nx);
}



int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",lh+i,rh+i);
		arr[i]=qpow(rh[i]-lh[i]+1,P-2);
		all=all*(rh[i]-lh[i]+1)%P;
	}
	for(ll i=1,ts,tt;i<n;i++){
		scanf("%lld%lld",&ts,&tt);
		t[ts].pb(tt);
		t[tt].pb(ts);
	}
	dfz(1);
	
	printf("%lld\n",all*(ans+P)%P);
	return 0;
}

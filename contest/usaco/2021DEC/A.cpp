#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const ll MXN=1e6+5,INF=1e18;
vector<pi> g[MXN];
void ae(ll u,ll v,ll w){
	g[u].push_back({v,w});
}
ll n,k,nodec;
ll dis1[MXN],disn[MXN],dis1n[MXN];
bool vis[MXN];
priority_queue<pi,vector<pi>,greater<pi>> q;
void dij(ll s,ll *dis){
	memset(vis,0,sizeof(vis));
	if(s)q.push({dis[s],s});
	else for(ll i=1;i<=nodec;i++)
		q.push({dis[i],i});
	while(!q.empty()){
		ll p=q.top().se;q.pop();
		if(vis[p])continue;
		vis[p]=1;
		for(pi &nx:g[p]){
			ll nd=dis[p]+nx.se;
			if(nd<dis[nx.fi])
				q.push({dis[nx.fi]=nd,nx.fi});
		}
	}
}
ll ind(ll l,ll r){return l+r|(l!=r);}
ll build(ll l,ll r){
	ll mid=(l+r)>>1,p=ind(l,r);
	if(l<r){
		ae(build(l,mid),p,0);
		ae(build(mid+1,r),p,0);
	}
	return p;
}
void que(ll l,ll r,ll ul,ll ur,ll v){
	ll mid=(l+r)>>1,p=ind(l,r);
	if(ul<=l && r<=ur){
		ae(p,v,0);
		return;
	}
	if(ul<=mid)que(l,mid,ul,ur,v);
	if(ur>mid) que(mid+1,r,ul,ur,v);
}

int main(){
	scanf("%lld%lld",&n,&k);
	build(1,n);
	nodec=n*2+10;
	for(ll i=1;i<=k;i++){
		ll c,p,a,b;
		scanf("%lld%lld%lld%lld",&c,&p,&a,&b);
		ae(++nodec,ind(c,c),p);
		que(1,n,a,b,nodec);
	}
	for(int i=1;i<=nodec;i++)
		dis1[i]=disn[i]=INF;
	dis1[ind(1,1)]=disn[ind(n,n)]=0;
	dij(ind(1,1),dis1);
	dij(ind(n,n),disn);
	for(int i=1;i<=nodec;i++)
		dis1n[i]=dis1[i]+disn[i];
	dij(0,dis1n);
	for(int i=1;i<=n;i++)
		printf("%lld\n",dis1n[ind(i,i)]>=INF?-1:dis1n[ind(i,i)]);

	return 0;
}

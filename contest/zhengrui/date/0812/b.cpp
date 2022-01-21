#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const ll MXN=1e5+5;
struct edge{ll v,w,l,r,opp;bool f;};
vector<edge> g[MXN],rg[MXN];
ll n,m,s1,s2,t;
ll dis[MXN],ans[MXN];
bool vis[MXN];
inline void dj(ll s){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	priority_queue<pi> q;
	q.push({dis[s]=0,s});
	while(!q.empty()){
		ll p=q.top().second;q.pop();
		if(vis[p])continue;
		vis[p]=1;
		for(edge &nx:rg[p]){
			ll nd=dis[p]+nx.w;
			if(nd<dis[nx.v])
				q.push({-(dis[nx.v]=nd),nx.v});
		}
	}
}
inline void bfsmark(ll s,bool tp){
	for(ll i=1;i<=n;i++)
		for(edge &j:g[i])
			j.f=0;
	memset(vis,0,sizeof(vis));
	queue<ll> q;
	vis[s]=1;
	q.push(s);
	while(!q.empty()){
		ll p=q.front();q.pop();
		for(edge &nx:g[p]){
			//if(tp)cout<<p<<" "<<nx.v<<" "<<nx.w<<"-"<<dis[p]<<" "<<dis[nx.v]<<endl;
			if(dis[p]-nx.w==dis[nx.v]){
				if(tp)nx.w=rg[nx.v][nx.opp].w=nx.r;
				else nx.f=1;
				if(!vis[nx.v]){
					vis[nx.v]=1;
					q.push(nx.v);
				}
			}
		}
	}
}
inline bool chk(ll s){
	memset(vis,0,sizeof(vis));
	queue<ll> q;
	vis[s]=1;
	q.push(s);
	while(!q.empty()){
		ll p=q.front();q.pop();
		for(edge &nx:g[p])
			if(!nx.f && dis[p]-nx.w==dis[nx.v]){
				nx.f=1;
				if(!vis[nx.v]){
					vis[nx.v]=1;
					q.push(nx.v);
				}
			}
	}
	return vis[t];
}


int main(){
	//freopen("ex_run5.in","r",stdin);
	//freopen("test.out","w",stdout);
	ll end=clock()+CLOCKS_PER_SEC*0.9;
	scanf("%lld%lld%lld%lld%lld",&n,&m,&s1,&s2,&t);
	for(ll i=1,tu,tv,tl,tr;i<=m;i++){
		scanf("%lld%lld%lld%lld",&tu,&tv,&tl,&tr);
		g[tu].push_back({tv,tl,tl,tr,(ll)rg[tv].size()});
		rg[tv].push_back({tu,tl,tl,tr,i});
	}
	dj(t);
	bfsmark(s2,0);
	while(clock()<=end && chk(s1)){
		bfsmark(s2,1);
		dj(t);
		bfsmark(s2,0);
	}
	dj(t);
	cerr<<dis[s1]<<" "<<dis[s2]<<endl;
	if(dis[s1]<=dis[s2]){
		puts(dis[s1]==dis[s2]?"DRAW":"WIN");
		for(ll i=1;i<=n;i++)
			for(edge &j:rg[i])
				ans[j.opp]=j.w;
		for(ll i=1;i<=m;i++)
			printf("%lld ",ans[i]);
	}
	else puts("LOSE");

	return 0;
}

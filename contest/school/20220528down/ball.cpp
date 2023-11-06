#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const char nl='\n';
const ll MXN=610,INF=1e17;

struct edge{
	ll v,c,o;
};
vector<edge> g0[MXN],cur[MXN],g[MXN];
void ae(ll u,ll v,ll c){
	g[u].push_back({v,c,(ll)g[v].size()});
	g[v].push_back({u,0,(ll)g[u].size()-1});
}
ll dis[MXN];
queue<ll> q;
bool bfs(ll s,ll t){
	while(!q.empty())q.pop();
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
	q.push(s);
	while(!q.empty()){
		ll p=q.front();q.pop();
		for(auto &nx:g[p])
			if(nx.c && dis[nx.v]==-1){
				dis[nx.v]=dis[p]+1;
				if(nx.v==t)return 1;
				q.push(nx.v);
			}
	}
	return 0;
}

ll cure[MXN];
ll dfs(ll p,ll t,ll fin){
	if(p==t)return fin;
	ll fout=0;
	for(ll &i=cure[p];i<(ll)g[p].size();i++){
		auto &nx=g[p][i];
		if(nx.c && dis[nx.v]==dis[p]+1){
			ll delt=dfs(nx.v,t,min(fin-fout,nx.c));
			if(delt){
				nx.c-=delt;
				g[nx.v][nx.o].c+=delt;
				fout+=delt;
				if(fin==fout)break;
			}
			else dis[nx.v]=-1;
		}
	}
	return fout;
}
ll dinic(ll s,ll t){
	ll r=0;
	while(bfs(s,t)){
		memset(cure,0,sizeof(cure));
		r+=dfs(s,t,INF);
	}
	return r;
}
void copye(vector<edge> *x,vector<edge> *y){
	for(ll i=0;i<MXN;i++)y[i]=x[i];
}
ll n,m,p[MXN];
char str[MXN];
#define st (n+m+1)
#define en (n+m+2)
#define kn(x) (x)
#define ld(x) (n+(x))
mt19937_64 mr(65536);


ll cal(){
	shuffle(p+1,p+1+n,mr);
	ll ans=0;
	copye(g0,cur);
	for(ll i=1;i<=n;i++){
		copye(cur,g);
		ae(st,kn(p[i]),2);
		if(dinic(st,en)==2){
			++ans;
			copye(g,cur);
		}
	}
	return ans;
}


int main(){
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll t0=clock();
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		cin>>(str+1);
		for(ll j=1;j<=m;j++)
			if(str[j]=='1')
				ae(kn(i),ld(j),1);
	}
	for(ll i=1;i<=m;i++)
		ae(ld(i),en,1);
	copye(g,g0);
	iota(p+1,p+1+n,1);
	ll ans=0;
	while(clock()-t0<=(double)CLOCKS_PER_SEC*1.5)
		ans=max(ans,cal());
	cout<<ans;

	return 0;
}


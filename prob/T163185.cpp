#include<bits/stdc++.h>
#define pb push_back
#define id(x) ((x)+2)
#define idc1(x) ((x)+n+2)
#define idc2(x) ((x)+n+m+2)

using namespace std;
typedef long long ll;
const ll MXN=5000;
const ll INF=1e18;
struct edge{
	ll ter,cap,opp;
	edge(ll ter=0,ll cap=0,ll opp=0):ter(ter),cap(cap),opp(opp){}
};
vector<edge> e[MXN];
inline void ae(ll ts,ll tt,ll cap){
	e[ts].pb(edge(tt,cap,e[tt].size()));
	e[tt].pb(edge(ts,0,e[ts].size()-1));
}
ll dis[MXN],cure[MXN];
queue<ll> q;

inline bool bfs(){
	memset(dis,0,sizeof(dis));
	while(!q.empty())q.pop();
	dis[1]=1;
	q.push(1);
	while(!q.empty()){
		ll p=q.front();q.pop();
		for(edge nx:e[p])
			if(nx.cap && !dis[nx.ter]){
				dis[nx.ter]=dis[p]+1;
				if(nx.ter==2)return 1;
				q.push(nx.ter);
			}
	}
	return 0;
}

inline ll dfs(ll p,ll fin){
	if(p==2)return fin;
	ll fout=0;
	for(ll &i=cure[p];i<(ll)e[p].size();i++){
		edge &nx=e[p][i];
		if(!nx.cap || dis[nx.ter]!=dis[p]+1)continue;
		ll tmp=dfs(nx.ter,min(fin-fout,nx.cap));
		if(tmp){
			nx.cap-=tmp;
			e[nx.ter][nx.opp].cap+=tmp;
			fout+=tmp;
			if(fout==fin)break;
		}
		else dis[nx.ter]=-1;
	}
	return fout;
}

inline ll dinic(){
	ll res=0;
	while(bfs()){
		memset(cure,0,sizeof(cure));
		res+=dfs(1,INF);
	}
	return res;
}
ll n,m,tot;
int main(){
	scanf("%lld",&n);
	for(ll i=1,tmp;i<=n;i++){
		scanf("%lld",&tmp);
		ae(1,id(i),tmp);
		tot+=tmp;
	}
	for(ll i=1,tmp;i<=n;i++){
		scanf("%lld",&tmp);
		ae(id(i),2,tmp);
		tot+=tmp;
	}
	scanf("%lld",&m);
	for(ll i=1,k,c1,c2,tmp;i<=m;i++){
		scanf("%lld%lld%lld",&k,&c1,&c2);
		tot+=c1+c2;
		ae(1,idc1(i),c1);
		ae(idc2(i),2,c2);
		while(k--){
			scanf("%lld",&tmp);
			ae(idc1(i),id(tmp),INF);
			ae(id(tmp),idc2(i),INF);
		}
	}
	printf("%lld",tot-dinic());
	return 0;
}

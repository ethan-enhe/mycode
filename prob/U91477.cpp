#include <bits/stdc++.h>
#include <deque>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const ll MXN=1e6+5;
ll n,m,c,nodec,p[MXN];
map<ll,ll> id[MXN];
vector<pi> g[MXN];
ll dis[MXN];
deque<ll> q;
inline void spfa(){
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	q.push_back(1);
	while(!q.empty()){
		ll p=q.front();q.pop_front();
		for(pi &nx:g[p]){
			ll nd=dis[p]+nx.second;
			if(nd<dis[nx.first]){
				dis[nx.first]=nd;
				nx.second?q.push_back(nx.first):q.push_front(nx.first);
			}
		}
	}
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&c);
	for(int i=1;i<=c;i++)scanf("%lld",p+i);
	nodec=n;
	while(m--){
		ll u,v,c;
		scanf("%lld%lld%lld",&u,&v,&c);
		if(!id[u][c])id[u][c]=++nodec;
		if(!id[v][c])id[v][c]=++nodec;
		u=id[u][c],v=id[v][c];
		g[u].push_back({v,0});
		g[v].push_back({u,0});
	}
	for(int i=1;i<=n;i++)
		for(auto &j:id[i]){
			g[i].push_back({j.second,p[j.first]});
			g[j.second].push_back({i,0});
		}
	spfa();
	for(int i=1;i<=n;i++)
		printf("%lld ",dis[i]>=1e18?-1:dis[i]);
	
	return 0;
}

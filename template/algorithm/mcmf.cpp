#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<const ll MXN>
struct mcmf{
	static const ll INF=1e18;
	struct edge{
		ll ter,cap,cost,opp;
		inline edge(ll ter,ll cap,ll cost,ll opp):ter(ter),cap(cap),cost(cost),opp(opp){}
	};
	queue<ll> q;
	bool vis[MXN];
	vector<edge> e[MXN];
	ll fs,ft,dis[MXN],cure[MXN];

	inline mcmf(){memset(vis,0,sizeof(vis));}
	inline void adde(ll ts,ll tt,ll tcap,ll tcost){
		e[ts].push_back(edge(tt,tcap,tcost,e[tt].size()));
		e[tt].push_back(edge(ts,0,-tcost,e[ts].size()-1));
	}
	inline bool spfa(){
		memset(dis,0x3f,sizeof(dis));
		dis[fs]=0;q.push(fs);
		while(!q.empty()){
			ll p=q.front();q.pop();
			vis[p]=0;
			for(ll i=0;i<(ll)e[p].size();i++){
				edge &nx=e[p][i];ll nd=dis[p]+nx.cost;
				if(dis[nx.ter]<=nd || !nx.cap)continue;
				dis[nx.ter]=nd;
				if(!vis[nx.ter]){
					vis[nx.ter]=1;
					q.push(nx.ter);
				}
			}
		}
		return dis[ft]<INF;
	}
	inline ll dinic(ll p,ll fin){
		if(p==ft)return fin;
		vis[p]=1;
		ll fout=0;
		for(ll &i=cure[p];i<(ll)e[p].size();i++){
			edge &nx=e[p][i];
			if(dis[nx.ter]!=dis[p]+nx.cost || vis[nx.ter] || !nx.cap)continue;
			ll delt=dinic(nx.ter,min(fin-fout,nx.cap));
			if(delt){
				nx.cap-=delt;
				e[nx.ter][nx.opp].cap+=delt;
				fout+=delt;
				if(fin==fout)break;
			}
			else dis[nx.ter]=-INF;
		}
		return vis[p]=0,fout;
	}
	inline pair<ll,ll> run(ll ts,ll tt){
		fs=ts,ft=tt;
		pair<ll,ll> res;
		while(spfa()){
			memset(cure,0,sizeof(cure));
			ll tmp=dinic(fs,INF);
			res.first+=tmp,res.second+=tmp*dis[ft];
		}
		return res;
	}
};
mcmf<(ll)5e3+5> f;
int main(){
	ll n,m,s,t;
	scanf("%lld%lld%lld%lld",&n,&m,&s,&t);
	while(m--){
		ll ts,tt,tcap,tcost;
		scanf("%lld%lld%lld%lld",&ts,&tt,&tcap,&tcost);
		f.adde(ts,tt,tcap,tcost);
	}
	pair<ll,ll> res=f.run(s,t);
	printf("%lld %lld",res.first,res.second);
	return 0;
}

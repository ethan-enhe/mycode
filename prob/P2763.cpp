#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1e18;
template<const ll MXN>
struct mcmf{
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
const int MXN=2e3+5;
mcmf<MXN> f;
vector<int> ans[MXN];
int k,n,m;
inline int prob(int x){return 2+x;}
inline int type(int x){return 2+n+x;}
int main(){
	scanf("%d%d",&k,&n);
	for(int i=1,tmp;i<=k;i++){
		scanf("%d",&tmp);
		m+=tmp;
		f.adde(type(i),2,tmp,0);
	}
	for(int i=1,p,tmp;i<=n;i++){
		scanf("%d",&p);
		f.adde(1,prob(i),1,0);
		while(p--){
			scanf("%d",&tmp);
			f.adde(prob(i),type(tmp),1,0);
		}
	}
	if(f.run(1,2).first!=m)puts("No Solution!");
	else{
		for(int i=1;i<=n;i++){
			int p=prob(i);
			for(size_t j=0;j<f.e[p].size();j++)
				if(f.e[p][j].cap==0 && f.e[p][j].ter>n+2){
					ans[f.e[p][j].ter-n-2].push_back(i);
					break;
				}
		}
		for(int i=1;i<=k;i++){
			printf("%d: ",i);
			for(int j:ans[i])printf("%d ",j);
			putchar('\n');
		}
	}

	return 0;
}

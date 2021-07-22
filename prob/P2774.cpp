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
const int MXN=105;
mcmf<MXN*MXN> f;
int n,m;
int id[MXN][MXN],cnt[2],sum;
int main(){
	scanf("%d%d",&n,&m);
	cnt[1]=(cnt[0]=2)+((n*m+1)>>1);
	for(int i=1,tmp;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&tmp);
			sum+=tmp;
			id[i][j]=++cnt[(i+j)&1];
			if((i+j)&1)f.adde(1,id[i][j],tmp,0);
			else f.adde(id[i][j],2,tmp,0);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if((i+j)&1){
				if(i>1)f.adde(id[i][j],id[i-1][j],INF,0);
				if(j>1)f.adde(id[i][j],id[i][j-1],INF,0);
				if(i<n)f.adde(id[i][j],id[i+1][j],INF,0);
				if(j<m)f.adde(id[i][j],id[i][j+1],INF,0);
			}
	printf("%d\n",sum-(int)f.run(1,2).first);

	return 0;
}

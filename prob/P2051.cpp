#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1e18;
template<const ll MXN>
struct flow{
	struct edge{
		ll ter,cap,cost,opp;
		inline edge(ll t,ll ca,ll co,ll o):ter(t),cap(ca),cost(co),opp(o){}
	};
	vector<edge> e[MXN];
	ll fs,ft,dis[MXN],cure[MXN];
	queue<ll> q;
	bool vis[MXN];
	inline void ae(ll ts,ll tt,ll tca,ll tco){
		cout<<ts<<" "<<tt<<" "<<tca<<" "<<tco<<endl;
		e[ts].push_back(edge(tt,tca,tco,e[tt].size()));
		e[tt].push_back(edge(ts,0,-tco,e[ts].size()-1));
	}
	inline bool spfa(){
		memset(dis,0x3f,sizeof(dis));
		dis[fs]=0;q.push(fs);
		while(!q.empty()){
			ll p=q.front();q.pop();
			vis[p]=0;
			for(ll i=0;i<(ll)e[p].size();i++){
				edge &nx=e[p][i];ll nd=dis[p]+nx.cost;
				if(nx.cap && nd<dis[nx.ter]){
					dis[nx.ter]=nd;
					if(!vis[nx.ter]){
						vis[nx.ter]=1;
						q.push(nx.ter);
					}
				}
			}
		}
		return dis[ft]<INF;
	}
	inline ll dinic(ll p,ll fin){
		if(p==ft)return fin;
		ll fout=0;vis[p]=1;
		for(ll &i=cure[p];i<(ll)e[p].size();i++){
			edge &nx=e[p][i];
			if(!vis[nx.ter] && dis[nx.ter]==dis[p]+nx.cost && nx.cap){
				ll delt=dinic(nx.ter,min(fin-fout,nx.cap));
				if(delt){
					nx.cap-=delt;
					e[nx.ter][nx.opp].cap+=delt;
					fout+=delt;
					if(fin==fout)break;
				}
				else dis[nx.ter]=-INF;
			}
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

flow<(ll)1e3+5> f;
ll m,n;
inline ll car(ll x){return x+2;}
inline ll rep(ll x,ll y){return 2+x*n+y;}

int main(){
	scanf("%lld%lld",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			ll tmp;
			scanf("%lld",&tmp);
			for(int k=1;k<=n;k++)
				f.ae(car(j),rep(i,k),1,tmp*k);
		}
	for(int i=1;i<=n;i++)
		f.ae(1,car(i),1,0);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			f.ae(rep(i,j),2,1,0);
	printf("%.2f",(double)f.run(1,2).second/n);
	return 0;
}

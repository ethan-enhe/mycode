
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const ll INF=1e18;
const ll MXN=505;
template <const int MXN, typename T=int>
struct raw_flow{
	const T INF=numeric_limits<T>::max();
	struct edge{
		int v,o;
		T c,w;
		edge (int _v,T _c,T _w,int _o): v(_v),o(_o),c(_c),w(_w){}
	};
	vector<edge> g[MXN];
	queue<int> q;
	int s,t,cure[MXN];
	bool vis[MXN];
	T dis[MXN];
	void adduedge(int u,int v,T c){
		g[u].push_back(edge(v,c,1,g[v].size()));
		g[v].push_back(edge(u,0,1,g[u].size()-1));
		//cerr<<u<<v<<c<<endl;
	}
	void clear_edge(){
		for(int i=0;i<MXN;i++)
			g[i].clear();
	}
	bool spfa(){
		for(int i=0;i<MXN;i++)dis[i]=INF,cure[i]=0;
		dis[s]=0;
		q.push(s);
		while(!q.empty()){
			int p=q.front();
			q.pop();
			vis[p]=0;
			for(edge &nx:g[p]){
				if(nx.c && dis[nx.v]>dis[p]+nx.w){
					dis[nx.v]=dis[p]+nx.w;
					if(!vis[nx.v]){
						vis[nx.v]=1;
						q.push(nx.v);
					}
				}
			}
		}
		return dis[t]!=INF;
	}
	T dinic(int p,T fi){
		if(p==t)return fi;
		T fo=0;
		vis[p]=1;
		for(int &i=cure[p];i<(int)g[p].size();i++){
			edge &nx=g[p][i];
			if(dis[nx.v]==dis[p]+nx.w && !vis[nx.v] && nx.c){
				T delt=dinic(nx.v,min(fi-fo,nx.c));
				if(delt){
					nx.c-=delt;
					g[nx.v][nx.o].c+=delt;
					fo+=delt;
					if(fi==fo)return vis[p]=0,fo;
				}
				else
					dis[nx.v]=-1;
			}
		}
		return vis[p]=0,fo;
	}
	T run(int _s,int _t){
		s=_s,t=_t;
		int res=0;
		while(spfa()){
			T delt=dinic(s,INF);
			res+=delt;
		}
		return res;
	}
};
ll n,m,p;
ll a[MXN],b[MXN],c[MXN],d[MXN];
raw_flow<MXN,ll> f;
vector<pair<ll,ll>> e;
bool chk(ll bound){//<=bound
	ll ans=0;
	for(ll i=1;i<=n;i++){
		if(c[i]+d[i]>bound){
			ans+=a[i];
		}
	}
	if(ans>p)return 0;
	f.clear_edge();
	for(auto [u,v]:e){
		if(c[u]+d[u]<=bound && d[v]>bound){
			f.adduedge(u,v,INF);
		}
		if(c[v]+d[v]<=bound && d[u]>bound){
			f.adduedge(v,u,INF);
		}
	}
	for(ll i=1;i<=n;i++){
		if(c[i]+d[i]<=bound){
			f.adduedge(n+1,i,a[i]);
		}
		if(d[i]>bound){
			f.adduedge(i,n+2,b[i]-a[i]);
		}
	}
	return ans+f.run(n+1,n+2)<=p;
}
int main(){
	freopen("test.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>p;
	ll l=0,r=0;
	for(ll i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>c[i]>>d[i];
		r=max(r,c[i]+d[i]);
	}
	while(m--){
		ll u,v;
		cin>>u>>v;
		e.push_back({u,v});
	}
	while(l<r){
		ll mid=(l+r)>>1;
		bool res=chk(mid);
		//cerr<<mid<<" "<<res<<endl;
		if(res)r=mid;
		else l=mid+1;
	}
	cout<<l<<endl;




	return 0;
}




#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const char nl='\n';
const ll MXN=1e5+5,INF=1e17;

struct edge{
	ll v,c,o;
};
vector<edge> g[MXN],save[MXN];
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
	//cerr<<t<<":\n";
	while(!q.empty()){
		ll p=q.front();q.pop();
		for(auto &nx:g[p])
			if(nx.c && dis[nx.v]==-1){
				//cerr<<p<<"->"<<nx.v<<"\n";
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
		//getchar();
	}
	return r;
}
void copye(vector<edge> *x,vector<edge> *y){
	for(ll i=0;i<MXN;i++)
		y[i]=x[i];
}



ll n;
double w[MXN],wc[MXN];
#define start (1<<n)
#define term ((1<<n)+1)
#define cat(x) ((1<<n)+10+(x))
#define rset(x) (x)
ll lg2(ll x){return __builtin_ctz(x);}

bool chk(double x){
	ll full=0;
	copye(save,g);
	for(ll i=0;i<n;i++){
		ll w=INF*wc[i]*x;
		//cerr<<wc[i]<<nl;
		full+=w;
		ae(start,cat(i),w);
	}
//	cerr<<full<<" "<<dinic(start,term)<<nl;
//	return 1;
	return full<=dinic(start,term)*(1.+1e-6);
}


int main(){
	//freopen("test.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(ll i=0;i<(1<<n);i++){
		cin>>w[i];
		ae(rset(i),term,INF*w[i]);
		if(i){
			ll lbt=i&(-i);
			ae(rset(i^lbt),rset(i),INF);
			ae(cat(lg2(lbt)),rset(i),INF);
		}
		for(ll j=0;j<n;j++)
			if((i>>j)&1){
				//wc[j]+=w[i]/(__builtin_popcount(i));
				wc[j]+=w[i];
			}
	}
	//copye(g,save);
	//chk(0.28);
	//cerr<<wc[1]<<wc[2];
	copye(g,save);
	double l=0,r=1;
	for(ll i=1;i<=30;i++){
		double mid=(l+r)/2;
		if(chk(mid))l=mid;
		else r=mid;
	}
	cout<<fixed<<setprecision(10)<<l;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;

const ll INF=1e18;
const ll P=1e9+7;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=1e5+5;

ll n,m,k;

struct edge{ll v,w;};
vector<edge> t[MXN],g[MXN];
vector<ll> spec;
inline void ae(vector<edge> tmp[MXN],ll ts,ll tt,ll tw){
	tmp[ts].pb({tt,tw});
	tmp[tt].pb({ts,tw});
}

ll rt[MXN];
inline ll find(ll x){return x==rt[x]?x:rt[x]=find(rt[x]);}

//{{{ mndis
ll spdis[45][MXN];
priority_queue<pi> q;
bool vis[MXN];

inline void initdis(ll s,ll dis[MXN]){
	for(ll i=1;i<=n;i++)
		dis[i]=INF,vis[i]=0;
	dis[s]=0;
	q.push(mp(0,s));
	while(!q.empty()){
		ll p=q.top().se;q.pop();
		if(vis[p])continue;
		vis[p]=1;
		for(edge &nx:g[p]){
			ll nd=dis[p]+nx.w;
			if(dis[nx.v]>nd){
				dis[nx.v]=nd;
				q.push(mp(-nd,nx.v));
			}
		}
	}
}
//}}}


//{{{ lca
const ll LG=20;
ll fa[MXN][LG+1],dis[MXN],dpth[MXN];
inline void initlca(ll p){
	for(ll i=1;i<=LG;i++)fa[p][i]=fa[fa[p][i-1]][i-1];
	for(edge &nx:t[p])
		if(nx.v!=fa[p][0]){
			fa[nx.v][0]=p;
			dpth[nx.v]=dpth[p]+1;
			dis[nx.v]=dis[p]+nx.w;
			initlca(nx.v);
		}
}
ll lca(ll x,ll y){
	if(dpth[x]>dpth[y])swap(x,y);
	ll tmp=dpth[y]-dpth[x];
	for(ll i=LG;~i;i--)if((tmp>>i)&1)y=fa[y][i];
	if(x==y)return x;
	for(ll i=LG;~i;i--)
		if(fa[y][i]!=fa[x][i])y=fa[y][i],x=fa[x][i];
	return fa[x][0];
}
//}}}

inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)rt[i]=i;
	while(m--){
		ll ts,tt,tw;
		scanf("%lld%lld%lld",&ts,&tt,&tw);
		ae(g,ts,tt,tw);
		if(find(ts)!=find(tt)){
			rt[find(ts)]=find(tt);
			ae(t,ts,tt,tw);
		}
		else spec.pb(ts),spec.pb(tt);
	}

	for(size_t i=0;i<spec.size();i++)initdis(spec[i],spdis[i]);
	initlca(1);
	scanf("%lld",&k);
	while(k--){
		ll ts,tt,res;
		scanf("%lld%lld",&ts,&tt);
		res=dis[ts]+dis[tt]-dis[lca(ts,tt)]*2;
		for(size_t i=0;i<spec.size();i++)
			res=min(res,spdis[i][ts]+spdis[i][tt]);
		printf("%lld\n",res);
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

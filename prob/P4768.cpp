#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;

const ll MXN=4e5+5;
const ll LG=20;
const ll INF=1e16;

struct edge{
	ll ts,tt,th;
	inline bool operator < (const edge &b)const{return th>b.th;};
}arr[MXN];
ll t,n,m,q,k,s,last;
vector<pi> e[MXN];

ll fa[20][MXN],va[2][MXN],ufa[MXN],nodec;
inline ll find(ll x){return ufa[x]==x?x:ufa[x]=find(ufa[x]);}
inline void build(){
	memset(fa,0,sizeof(fa));
	sort(arr+1,arr+1+m);
	for(int i=1;i<=m;i++){
		ll x=arr[i].ts,y=arr[i].tt;
		if(find(x)!=find(y)){
			va[0][++nodec]=min(va[0][ufa[x]],va[0][ufa[y]]);
			va[1][nodec]=arr[i].th;
			ufa[ufa[x]]=ufa[ufa[y]]=fa[0][ufa[x]]=fa[0][ufa[y]]=nodec;
		}
	}
	do{
		for(int i=1;i!=LG;i++)
			fa[i][nodec]=fa[i-1][fa[i-1][nodec]];
	}while(--nodec);
}
inline ll que(ll v,ll p){
	for(int i=LG-1;~i;i--)
		if(fa[i][v] && va[1][fa[i][v]]>p)
			v=fa[i][v];
	return va[0][v];
}

priority_queue<pi> pq;
bool vis[MXN];
inline void dij(){
	memset(va[0],0x3f,sizeof(va[0]));
	memset(vis,0,sizeof(vis));
	va[0][1]=0;
	pq.push(mp(0,1));
	while(!pq.empty()){
		ll p=pq.top().se;pq.pop();
		if(vis[p])continue;
		vis[p]=1;
		for(pi nx:e[p])
			if(va[0][nx.fi]>va[0][p]+nx.se)
				pq.push(mp(-(va[0][nx.fi]=va[0][p]+nx.se),nx.fi));
	}
}


int main(){
	//freopen("test.in","r",stdin);
	scanf("%lld",&t);
	while(t--){
		last=0;
		scanf("%lld%lld",&n,&m);
		for(int i=1;i!=n<<1;i++)e[i].clear(),ufa[i]=i,va[1][i]=INF;
		nodec=n;
		for(int i=1;i<=m;i++){
			ll ts,tt,tl,tw;
			scanf("%lld%lld%lld%lld",&ts,&tt,&tl,&tw);
			arr[i]=edge{ts,tt,tw};
			e[ts].pb(mp(tt,tl));
			e[tt].pb(mp(ts,tl));
		}
		dij();
		build();
		scanf("%lld%lld%lld",&q,&k,&s);
		while(q--){
			ll tv,tp;
			scanf("%lld%lld",&tv,&tp);
			tv=(tv+k*last-1)%n+1;
			tp=(tp+k*last)%(s+1);
			last=que(tv,tp);
			printf("%lld\n",last);
		}
	}
	return 0;
}

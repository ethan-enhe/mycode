#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=2e5+5,LG=18,INF=1e18;
ll n,m,k;
struct edge{ll u,v,w;}arr[MXN];
struct adj{ll v,w;};
vector<adj> e[MXN];
inline void add(ll u,ll v,ll w){
	e[u].push_back({v,w});
	e[v].push_back({u,w});
}
inline ll cal(const edge &x){return x.w>k?x.w-k:0;}
inline bool cmp(const edge &x,const edge &y){return cal(x)<cal(y);}
ll rt[MXN];
inline ll find(ll x){return x==rt[x]?x:rt[x]=find(rt[x]);}
inline ll kk(){
	ll res=0;
	sort(arr+1,arr+1+m,cmp);
	for(ll i=1;i<=n;i++)rt[i]=i;
	for(ll i=1;i<=m;i++)
		if(find(arr[i].u)!=find(arr[i].v)){
			rt[find(arr[i].u)]=find(arr[i].v);
			ll tw=cal(arr[i]);
			add(arr[i].u,arr[i].v,tw);
			res+=tw;
		}
	return res;
}

ll dpth[MXN],fa[MXN][LG+1],mx[MXN][LG+1];
inline void init(ll p){
	for(ll i=1;i<=LG;i++){
		fa[p][i]=fa[fa[p][i-1]][i-1];
		mx[p][i]=max(mx[p][i-1],mx[fa[p][i-1]][i-1]);
	}
	for(adj& nx:e[p])
		if(nx.v!=fa[p][0]){
			fa[nx.v][0]=p;
			mx[nx.v][0]=nx.w;
			dpth[nx.v]=dpth[p]+1;
			init(nx.v);
		}
}
inline ll gmx(ll x,ll y){
	if(dpth[x]<dpth[y])swap(x,y);
	ll res=-INF,tmp=dpth[x]-dpth[y];
	for(ll i=LG;~i;i--)
		if((tmp>>i)&1){
			res=max(res,mx[x][i]);
			x=fa[x][i];
		}
	if(x==y)return res;
	for(ll i=LG;~i;i--)
		if(fa[x][i]!=fa[y][i]){
			res=max(res,mx[x][i]);
			res=max(res,mx[y][i]);
			x=fa[x][i],y=fa[y][i];
		}
	return max(res,max(mx[x][0],mx[y][0]));
}
int main(){
	freopen("sample_tree.in","r",stdin);
	freopen("sample_tree.ans","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&k);
	for(ll i=1;i<=m;i++)
		scanf("%lld%lld%lld",&arr[i].u,&arr[i].v,&arr[i].w);
	//开ll！！！
	ll tot=kk(),ans=INF;
	memset(mx,~0x3f,sizeof(mx));
	init(1);
	for(ll i=1;i<=m;i++)
		ans=min(ans,tot+abs(arr[i].w-k)-gmx(arr[i].u,arr[i].v));
	printf("%lld",ans);
	return 0;
}

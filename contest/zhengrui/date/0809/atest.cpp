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
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(ll i=1;i<=m;i++)
		scanf("%lld%lld%lld",&arr[i].u,&arr[i].v,&arr[i].w);
	//开ll！！！
	ll tot=kk(),ans=INF;
	if(tot)return printf("%lld",tot),0;
	for(ll i=1;i<=m;i++)ans=min(ans,abs(arr[i].w-k));
	printf("%lld",ans);
	return 0;
}


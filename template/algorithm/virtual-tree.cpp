#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1e18,MXN=2.5e5+5,LG=18;
struct edge{ll v,w;};
vector<edge> e[MXN];
ll n,m;
ll dfn[MXN],dfnc;
ll mnw[MXN],dpth[MXN];int fa[MXN][LG+1];
inline void add(ll x,ll y,ll z=0){e[x].push_back({y,z});}
inline void init(ll p){
	dfn[p]=++dfnc;
	for(ll i=1;i<=LG;i++)fa[p][i]=fa[fa[p][i-1]][i-1];
	for(edge &nx:e[p])
		if(nx.v!=fa[p][0]){
			mnw[nx.v]=min(mnw[p],nx.w);
			dpth[nx.v]=dpth[p]+1;
			fa[nx.v][0]=p;
			init(nx.v);
		}
	e[p].clear();
}
int lca(int x,int y){
	if(dpth[x]>dpth[y])swap(x,y);
	int tmp=dpth[y]-dpth[x];
	for(int i=LG;~i;i--)if((tmp>>i)&1)y=fa[y][i];
	if(x==y)return x;
	for(int i=LG;~i;i--)
		if(fa[y][i]!=fa[x][i])y=fa[y][i],x=fa[x][i];
	return fa[x][0];
}
bool isvip[MXN];


ll sta[MXN],top,vip[MXN],vipc;
inline bool cmp(ll x,ll y){return dfn[x]<dfn[y];}
inline void build(){
	sort(vip+1,vip+1+vipc,cmp);
	sta[top=1]=1;
	for(ll i=1;i<=vipc;i++){
	    if(vip[i]==1)continue;
		ll l=lca(vip[i],sta[top]);
		if(l!=sta[top]){
			while(dfn[l]<dfn[sta[top-1]])
				add(sta[top-1],sta[top]),top--;
			add(l,sta[top]);
			if(dfn[l]>dfn[sta[top-1]])sta[top]=l;
			else top--;
		}
		sta[++top]=vip[i];
	}
	while(top-->1)add(sta[top],sta[top+1]);
}
inline ll dp(ll p){
	ll res=0;
	for(edge &nx:e[p])res+=dp(nx.v);
	e[p].clear();
	if(isvip[p])return isvip[p]=0,mnw[p];
	return min(mnw[p],res);
}

int main(){
	scanf("%lld",&n);
	for(ll i=1,ts,tt,tw;i<n;i++){
		scanf("%lld%lld%lld",&ts,&tt,&tw);
		add(ts,tt,tw);
		add(tt,ts,tw);
	}
	mnw[1]=INF;
	init(1);
	scanf("%lld",&m);
	while(m--){
		scanf("%lld",&vipc);
		for(ll i=1;i<=vipc;i++)
			scanf("%lld",vip+i),isvip[vip[i]]=1;
		build();
		printf("%lld\n",dp(1));
	}

	return 0;
}

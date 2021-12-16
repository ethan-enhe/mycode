#include <bits/stdc++.h>
using namespace std;
const int MXN=2e6+5;
vector<int> g[MXN],t[MXN];
int n,m,q;
int dfn[MXN],low[MXN],dfnc,nodec;
stack<int> stk;
void ae(vector<int> *_g,int u,int v){
	_g[u].push_back(v);
	_g[v].push_back(u);
	//cerr<<u<<" "<<v<<endl;
}
void tj(int p){
	low[p]=dfn[p]=++dfnc;
	stk.push(p);
	for(int nx:g[p]){
		if(!dfn[nx]){
			tj(nx);
			low[p]=min(low[p],low[nx]);
			if(low[nx]==dfn[p]){
				++nodec;
				int x;
				do{
					ae(t,x=stk.top(),nodec);
					stk.pop();
				}while(x!=nx);
				ae(t,p,nodec);
			}
		}
		else low[p]=min(low[p],dfn[nx]);
	}
}


int fa[MXN],top[MXN],son[MXN],sz[MXN],dpth[MXN];
void div(int p){
	sz[p]=1;
	for(int nx:t[p])
		if(nx!=fa[p]){
			fa[nx]=p,dpth[nx]=dpth[p]+1;
			div(nx);
			sz[p]+=sz[nx];
			if(sz[nx]>sz[son[p]])son[p]=nx;
		}
}
void caltop(int p){
	if(!top[p])top[p]=p;
	top[son[p]]=top[p];
	for(int nx:t[p])
		if(nx!=fa[p])
			caltop(nx);
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dpth[top[x]]<dpth[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dpth[x]<dpth[y]?x:y;
}
int main(){
	//freopen("test.in","r",stdin);
	scanf("%d%d",&n,&m);
	nodec=n;
	while(m--){
		int u,v;
		scanf("%d%d",&u,&v);
		ae(g,u,v);
	}
	tj(1);
	div(1);
	caltop(1);
	scanf("%d",&q);
	while(q--){
		int x,y,ans;
		scanf("%d%d",&x,&y);
		ans=dpth[x]+dpth[y]-2*dpth[lca(x,y)];
		printf("%d\n",ans/2+1);
	}
	

	
	return 0;
}

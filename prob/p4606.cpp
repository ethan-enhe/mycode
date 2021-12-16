#include <bits/stdc++.h>
using namespace std;
const int MXN=5e5+5;
vector<int> g[MXN],t[MXN];//
int n,m,q;//
int dfn[MXN],low[MXN],dfnc,nodec;//
stack<int> stk;//
void ae(vector<int> *_g,int u,int v){
	_g[u].push_back(v);
	_g[v].push_back(u);
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


int fa[MXN],top[MXN],son[MXN],sz[MXN],dpth[MXN];//
void div(int p){
	dfn[p]=++dfnc;
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
bool chk(int x){return x<=n;}
int que(int x,int y){
	int l=lca(x,y);
	return (dpth[x]+dpth[y]-2*dpth[l])/2-1-chk(l);
}


int ask[MXN],askc;
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}
int solve(){
	int res=0;
	sort(ask+1,ask+1+askc,cmp);
	ask[askc+1]=ask[1];
	//这里是恰好把每个边统计两遍，有点问题
	for(int i=1;i<=askc;i++)
		res+=que(ask[i],ask[i+1]);

	return res/2+chk(lca(ask[1],ask[askc]));
}
#define mem(x) memset((x),0,sizeof(x))

int main(){
	int task;
	scanf("%d",&task);
	while(task--){
		mem(dfn);
		mem(low);
		mem(son);
		mem(top);
		//???
		dfnc=0;
		while(!stk.empty())stk.pop();
		scanf("%d%d",&n,&m);
		nodec=n;
		while(m--){
			int u,v;
			scanf("%d%d",&u,&v);
			ae(g,u,v);
		}
		tj(1);
		memset(dfn,0,sizeof(dfn));
		dfnc=0;
		div(1);
		caltop(1);
		scanf("%d",&q);
		while(q--){
			scanf("%d",&askc);
			for(int i=1;i<=askc;i++)
				scanf("%d",ask+i);
			printf("%d\n",solve());
		}
		for(int i=1;i<=nodec;i++){
			g[i].clear();
			t[i].clear();
		}
	}
	return 0;
}

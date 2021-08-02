#include<bits/stdc++.h>
using namespace std;
const int MXN=2e5+5;
const int MXK=1e6+5;
const int INF=1e9;
struct edge{int ter,wei;};
vector<edge> e[MXN];
int n,k,ans;
bool vis[MXN];
int sz[MXN],mncnt[MXN];
inline void dfssz(int p,int fa){
	sz[p]=1;
	for(edge nx:e[p])
		if(!vis[nx.ter] && nx.ter!=fa){
			dfssz(nx.ter,p);
			sz[p]+=sz[nx.ter];
		}
}
inline int dfsrt(int p,int fa,int tot){
	bool f=(sz[p]<<1)>=tot;
	for(edge nx:e[p])
		if(!vis[nx.ter] && nx.ter!=fa){
			int tmp=dfsrt(nx.ter,p,tot);
			if(tmp)return tmp;
			f&=(sz[nx.ter]<<1)<=tot;
		}
	return f?p:0;
}
inline void dfsm(int p,int fa,int dis,int len,bool tp){
	if(dis>k)return;
	mncnt[dis]=tp?min(mncnt[dis],len):INF;
	for(edge nx:e[p])
		if(!vis[nx.ter] && nx.ter!=fa)
			dfsm(nx.ter,p,dis+nx.wei,len+1,tp);
}
inline void dfsq(int p,int fa,int dis,int len){
	if(dis>k)return;
	ans=min(ans,mncnt[k-dis]+len);
	for(edge nx:e[p])
		if(!vis[nx.ter] && nx.ter!=fa)
			dfsq(nx.ter,p,dis+nx.wei,len+1);
}
inline void dfz(int p){
	dfssz(p,0);
	p=dfsrt(p,0,sz[p]);
	vis[p]=1;
	mncnt[0]=0;
	for(edge nx:e[p])
		if(!vis[nx.ter]){
			dfsq(nx.ter,0,nx.wei,1);
			dfsm(nx.ter,0,nx.wei,1,1);
		}
	dfsm(p,0,0,0,0);
	for(edge nx:e[p])
		if(!vis[nx.ter])
			dfz(nx.ter);
}

int main(){
	freopen("test.in","r",stdin);
	scanf("%d%d",&n,&k);
	for(int i=1,ts,tt,tw;i<n;i++){
		scanf("%d%d%d",&ts,&tt,&tw);
		++ts,++tt;
		e[ts].push_back({tt,tw});
		e[tt].push_back({ts,tw});
	}
	memset(mncnt,0x3f,sizeof(mncnt));
	ans=INF;
	dfz(1);
	if(ans<INF)printf("%d\n",ans);
	else puts("-1");
	return 0;
}

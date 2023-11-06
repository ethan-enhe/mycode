#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pi;
const int MXN=1e4+5;
const int NR=5e6+5;
vector<pi> e[MXN];
int n,m,ans;
bool vis[MXN];
int sz[MXN],mn[NR];
void calsz(int p,int fa){
	sz[p]=1;
	for(int i=0,nx;i<(int)e[p].size();i++){
		nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		calsz(nx,p);
		sz[p]+=sz[nx];
	}
}
int calrt(int p,int fa,int tot){
	bool f=(tot<=(sz[p]<<1));
	for(int tmp,nx,i=0;i<(int)e[p].size();i++){
		nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		f&=(tot>=(sz[nx]<<1));
		tmp=calrt(nx,p,tot);
		if(~tmp)return tmp;
	}
	return f?p:-1;
}
void qdfs(int p,int fa,int dpth,int dis){
	if(dis>m || dpth>=ans)return;
	ans=min(ans,dpth+mn[m-dis]);
	for(size_t i=0;i<e[p].size();i++){
		pi nx=e[p][i];
		if(vis[nx.fi] || nx.fi==fa)continue;
		qdfs(nx.fi,p,dpth+1,dis+nx.se);
	}
}
void mdfs(int p,int fa,int dis,int op){
	if(dis>m)return;
	mod(dis,op);
	for(size_t i=0;i<e[p].size();i++){
		pi nx=e[p][i];
		if(vis[nx.fi] || nx.fi==fa)continue;
		mdfs(nx.fi,p,dis+nx.se,op);
	}
}
void dfz(int p){
	calsz(p,0);
	p=calrt(p,0,sz[p]);
	vis[p]=1;
	mod(0,1);
	for(size_t i=0;i<e[p].size();i++){
		pi nx=e[p][i];
		if(vis[nx.fi])continue;
		qdfs(nx.fi,0,nx.se);
		mdfs(nx.fi,0,nx.se,1);
	}
	mdfs(p,0,0,-1);
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i].fi;
		if(vis[nx])continue;
		dfz(nx);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int ts,tt,tw;
		scanf("%d%d%d",&ts,&tt,&tw);
		ts++,tt++;
		e[ts].pb(mp(tt,tw));
		e[tt].pb(mp(ts,tw));
	}
	dfz(1);
	printf("%d\n",ans);
	return 0;
}

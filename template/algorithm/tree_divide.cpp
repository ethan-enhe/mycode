//P3806 【模板】点分治1
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
typedef pair<int,int> pi;
const int MXN=1e4+5;
const int MXM=105;
const int MXD=1e7+5;

int n,m;
vector<pi> e[MXN];
int q[MXM];

int sz[MXN];
bool vis[MXN],dapp[MXD];
inline void dfssz(int p,int fa){
	sz[p]=1;
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		dfssz(nx,p);
		sz[p]+=sz[nx];
	}
}
inline int dfsrt(int p,int fa,int tot){
	bool f=(sz[p]<<1)>=tot;
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		int r=dfsrt(nx,p,tot);
		if(r)return r;
		f&=(sz[nx]<<1)<=tot;
	}
	return f?p:0;
}
inline void dfsm(int p,int fa,int dpth,bool tp){
	if(dpth>=MXD)return;
	dapp[dpth]=tp;
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		dfsm(nx,p,dpth+e[p][i].se,tp);
	}
}
inline void dfsq(int p,int fa,int dpth){
	if(dpth>=MXD)return;
	for(int i=1;i<=m;i++)
		if(dpth<=q[i] && dapp[q[i]-dpth])
			q[i]=0;
	
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		dfsq(nx,p,dpth+e[p][i].se);
	}
}
inline void dfz(int p){
	dfssz(p,0),p=dfsrt(p,0,sz[p]);
	vis[p]=dapp[0]=1;
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i].fi;
		if(vis[nx])continue;
		dfsq(nx,0,e[p][i].se);
		dfsm(nx,0,e[p][i].se,1);
	}
	dfsm(p,0,0,0);
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i].fi;
		if(vis[nx])continue;
		dfz(nx);
	}
}


int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,ts,tt,tw;i<n;i++){
		scanf("%d%d%d",&ts,&tt,&tw);
		e[ts].pb(mp(tt,tw));
		e[tt].pb(mp(ts,tw));
	}
	for(int i=1;i<=m;i++)scanf("%d",q+i);
	dapp[0]=1;
	dfz(1);
	for(int i=1;i<=m;i++)puts(q[i]?"NAY":"AYE");
	return 0;
}

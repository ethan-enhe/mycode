#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const ll MXN=1e4+5;
const ll MXM=105;
const ll NR=1e7;

ll n,m,que[MXM];bool ans[MXM];
vector<pi> e[MXN];


bool vis[MXN],cnt[NR];
ll sz[MXN];
void dfssz(ll p,ll fa){
	sz[p]=1;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		dfssz(nx,p);
		sz[p]+=sz[nx];
	}
}
ll dfsrt(ll p,ll fa,ll tot){
	bool isrt=(sz[p]<<1)>=tot;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		ll tmp=dfsrt(nx,p,tot);
		if(tmp)return tmp;
	}
	return isrt?p:0;
}
void dfsmark(ll p,ll fa,ll dpth,bool tp){
	if(dpth>=NR)return;
	cnt[dpth]=tp;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		dfsmark(nx,p,dpth+e[p][i].se,tp);
	}
}
void dfsq(ll p,ll fa,ll dpth){
	if(dpth>=NR)return;
	for(int i=1;i<=m;i++)
		ans[i]|=dpth<=que[i] && cnt[que[i]-dpth];
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		dfsq(nx,p,dpth+e[p][i].se);
	}
}
void dfz(ll p){
	dfssz(p,0);
	p=dfsrt(p,0,sz[p]);
	vis[p]=cnt[0]=1;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i].fi;
		if(vis[nx])continue;
		dfsq(nx,0,e[p][i].se);
		dfsmark(nx,0,e[p][i].se,1);
	}
	dfsmark(p,0,0,0);
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i].fi;
		if(vis[nx])continue;
		dfz(nx);
	}
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<n;i++){
		ll ts,tt,tw;
		scanf("%lld%lld%lld",&ts,&tt,&tw);
		e[ts].pb(mp(tt,tw));
		e[tt].pb(mp(ts,tw));
	}
	for(int i=1;i<=m;i++)scanf("%lld",que+i);
	dfz(1);
	for(int i=1;i<=m;i++)printf(ans[i]?"AYE\n":"NAY\n");
	return 0;
}


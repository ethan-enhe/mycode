#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const ll MXN=1e5+5;

ll n,col[MXN],ans[MXN];
vector<ll> e[MXN];


bool vis[MXN];
ll sz[MXN];
void dfssz(ll p,ll fa){
	sz[p]=1;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i];
		if(vis[nx] || nx==fa)continue;
		dfssz(nx,p);
		sz[p]+=sz[nx];
	}
}
ll dfsrt(ll p,ll fa,ll tot){
	bool isrt=(sz[p]<<1)>=tot;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i];
		if(vis[nx] || nx==fa)continue;
		ll tmp=dfsrt(nx,p,tot);
		if(tmp)return tmp;
	}
	return isrt?p:0;
}
ll dfsq(ll p,ll fa,ll cnt){
	ll res=cnt;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i];
		if(vis[nx] || nx==fa)continue;
		res+=dfsq(nx,p,cnt+(col[nx]!=col[p]));
	}
	return res;
}
void dfscal(ll p,ll fa,ll cnt,ll sz,ll tot){
	ans[p]+=cnt*sz+tot;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i];
		if(vis[nx] || nx==fa)continue;
		dfscal(nx,p,cnt+(col[nx]!=col[p]),sz,tot);
	}
}
void dfz(ll p){
	dfssz(p,0);
	p=dfsrt(p,0,sz[p]);
	dfssz(p,0);
	vis[p]=1;
	ll tot=dfsq(p,0,1);
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i];
		if(vis[nx])continue;
		ll tmp=dfsq(nx,0,1+(col[nx]!=col[p]));
		dfscal(nx,0,(col[nx]!=col[p]),sz[p]-sz[nx],tot-tmp-1);
		if(p==2)cout<<nx<<" "<<sz[p]-sz[nx]<<endl;
	}
	ans[p]+=tot;
	/*
	cout<<p<<endl;
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	cout<<endl<<"---\n";
	*/
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i];
		if(vis[nx])continue;
		dfz(nx);
	}
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",col+i);
	for(int i=1;i<n;i++){
		ll ts,tt;
		scanf("%lld%lld",&ts,&tt);
		e[ts].pb(tt);
		e[tt].pb(ts);
	}
	dfz(1);
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	return 0;
}


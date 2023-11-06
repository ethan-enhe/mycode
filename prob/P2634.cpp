#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const ll MXN=2e4+5;
inline ll mod3(ll x){return x<3?x:x-3;}

ll n,ans;
vector<pi> e[MXN];


bool vis[MXN];
ll sz[MXN],cnt[3],tcnt[3];
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
void dfsq(ll p,ll fa,ll dpth){
	tcnt[dpth]++;
	ans+=cnt[mod3(3-dpth)];
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i].fi;
		if(vis[nx] || nx==fa)continue;
		dfsq(nx,p,mod3(dpth+e[p][i].se));
	}
}
void dfz(ll p){
	dfssz(p,0);
	p=dfsrt(p,0,sz[p]);
	vis[p]=1;
	cnt[0]=1,cnt[1]=cnt[2]=0;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i].fi;
		if(vis[nx])continue;
		tcnt[0]=tcnt[1]=tcnt[2]=0;
		dfsq(nx,0,e[p][i].se);
		cnt[0]+=tcnt[0];
		cnt[1]+=tcnt[1];
		cnt[2]+=tcnt[2];
	}
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i].fi;
		if(vis[nx])continue;
		dfz(nx);
	}
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		ll ts,tt,tw;
		scanf("%lld%lld%lld",&ts,&tt,&tw);
		tw%=3;
		e[ts].pb(mp(tt,tw));
		e[tt].pb(mp(ts,tw));
	}
	dfz(1);
	ll a=(ans<<1)+n,b=n*n;
	ll tmp=__gcd(a,b);
	printf("%lld/%lld",a/tmp,b/tmp);
	return 0;
}

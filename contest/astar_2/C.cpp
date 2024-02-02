#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const ll P=1e8+7;
const ll MXN=1e6+5;



ll n,m,A;
ll dfn[MXN],sz[MXN],dpth[MXN];
vector<ll> g[MXN];
ll qpow(ll x,ll y){
	ll r=1;
	y=(y+P-1)%(P-1);
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}


ll sum[MXN];
void mdf(ll x,ll y){
	for(;x<=n;x+=x&(-x))
		sum[x]=(sum[x]+y)%P;
	//cerr<<"!!!";
}
ll pre(ll x){
	ll r=0;
	for(;x;x-=x&(-x))
		r=(r+sum[x])%P;
	return r;
}
ll dfnc=0;
void init(ll p){
	dfn[p]=++dfnc;
	sz[p]=1;
	for(ll nx:g[p]){
		dpth[nx]=dpth[p]+1;
		init(nx);
		sz[p]+=sz[nx];
	}
}
int main(){
	freopen("test.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>A;
	for(ll i=2;i<=n;i++){
		ll f;
		cin>>f;
		g[f].push_back(i);
	}
	init(1);
	while(m--){
		ll a,b,c;
		cin>>a>>b;
		if(a==2){
			ll ans=(pre(dfn[b])*qpow(A,dpth[b])%P+P)%P;
			cout<<ans<<'\n';
		}
		else{
			cin>>c;
			swap(b,c);
			ll delt=qpow(A,b-dpth[c]);
			//cerr<<dfn[c]<<endl;
			mdf(dfn[c],delt);
		//cerr<<m<<endl;
			mdf(dfn[c]+sz[c],-delt);
		}
	}
	return 0;
}

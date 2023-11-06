#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;

const ll INF=1e18;
const ll P=998244353;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=1e6+5;

ll n,m,cnt,sz,col[MXN];
vector<ll> g[MXN];
inline bool mark(ll p){
	cnt+=col[p],sz++;
	for(ll nx:g[p]){
		if(~col[nx]){if(col[nx]==col[p])return 1;}
		else{
			col[nx]=!col[p];
			if(mark(nx))return 1;
		}
	}
	return 0;
}
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)col[i]=-1,g[i].clear();
	while(m--){
		ll ts,tt;
		scanf("%lld%lld",&ts,&tt);
		g[ts].pb(tt);
		g[tt].pb(ts);
	}
	ll ans=1;
	for(int i=1;i<=n;i++)
		if(col[i]==-1){
			col[i]=cnt=sz=0;
			if(mark(i)){
				puts("0");
				return;
			}
			ans=ans*(qpow(2,cnt)+qpow(2,sz-cnt))%P;
		}
	printf("%lld\n",ans);
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

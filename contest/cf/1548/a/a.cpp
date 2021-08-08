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
const ll P=1e9+7;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=1e6+5;

ll n,m,k;
ll arr[MXN],ans;
inline void mod(ll x,ll d){
	ans-=arr[x]==0;
	arr[x]+=d;
	ans+=arr[x]==0;
}
inline void solve(){
	scanf("%lld%lld",&n,&m);ans=n;
	for(ll i=1,ts,tt;i<=m;i++){
		scanf("%lld%lld",&ts,&tt);
		mod(min(ts,tt),1);
	}
	scanf("%lld",&k);
	while(k--){
		ll op,x,y;
		scanf("%lld",&op);
		if(op==3)printf("%lld\n",ans);
		else{
			scanf("%lld%lld",&x,&y);
			mod(min(x,y),3-op*2);
		}
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

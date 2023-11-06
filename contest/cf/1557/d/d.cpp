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


const ll MXN=8e6+5;
const ll MXR=1e9;

ll n,m,k;
ll arr[MXN];

struct rg{ll l,r;};
vector<rg> col[MXN];


typedef ll arrn[MXN];
arrn v,t,ls,rs;
ll nodec,rt;
inline void addt(ll &p,ll k){
	if(!p)p=++nodec;
	v[p]=max(v[p],t[p]=k);
}
inline void pushd(ll p){
	addt(ls[p],t[p]);
	addt(rs[p],t[p]);
}
inline void pushu(ll p){v[p]=max(v[ls[p]],v[rs[p]]);}
inline void mod(ll &p,ll l,ll r,ll ml,ll mr,ll mv){
	if(!p)p=++nodec;
	if(ml<=l && r<=mr){
		addt(p,mv);
		return;
	}
	pushd(p);
	ll mid=(l+r)>>1;
	if(ml<=mid)mod(ls[p],l,mid,ml,mr,mv);
	if(mr>mid)mod(rs[p],mid+1,r,ml,mr,mv);
	pushu(p);
}
inline ll que(ll p,ll l,ll r,ll ml,ll mr){
	if(!p || (ml<=l && r<=mr))return v[p];
	pushd(p);
	ll mid=(l+r)>>1,ans=-INF;
	if(ml<=mid)ans=que(ls[p],l,mid,ml,mr);
	if(mr>mid)ans=max(ans,que(rs[p],mid+1,r,ml,mr));
	return ans;
}

inline void solve(){
	scanf("%lld%lld",&n,&m);
	while(m--){
		ll a,b,c;
		scanf("%lld%lld%lld",&a,&b,&c);
		col[a].push_back({b,c});
	}
	col[++n].push_back({1,MXR});
	for(int i=1;i<=n;i++){
		for(rg j:col[i])
			arr[i]=max(arr[i],que(rt,1,MXR,j.l,j.r));
		arr[i]++;
		for(rg j:col[i])
			mod(rt,1,MXR,j.l,j.r,arr[i]);
	}
	printf("%lld",arr[n]);

    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

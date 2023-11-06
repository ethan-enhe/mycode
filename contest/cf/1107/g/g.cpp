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


const ll MXN=3e5+5;
const ll LG=20;



ll n,m,ans;
ll t[MXN],d[MXN],c[MXN];
struct st{
	ll mxi[MXN][LG],*arr;
	inline void init(ll *tmp,ll len){
		arr=tmp;
		for(int i=len;~i;i--){
			mxi[i][0]=i;
			for(int j=0;i+(1<<j)<=len;j++){
				if(arr[mxi[i+(1<<j)][j]]>arr[mxi[i][j]])
					mxi[i][j+1]=mxi[i+(1<<j)][j];
				else mxi[i][j+1]=mxi[i][j];
			}
		}
	}
	inline ll gmx(ll l,ll r){
		ll h=log2(r-l+1);
		if(arr[mxi[r-(1<<h)+1][h]]>arr[mxi[l][h]])return mxi[r-(1<<h)+1][h];
		else return mxi[l][h];
	}
}sc,_sc,mxd;
inline void dfs(ll l,ll r){
	if(l==r){
		ans=max(ans,c[l]-c[l-1]);
		return;
	}
	ll mid=mxd.gmx(l,r-1),tmp=c[sc.gmx(mid+1,r)]+t[_sc.gmx(l-1,mid-1)]-d[mid]*d[mid];
	ans=max(ans,tmp);
	dfs(l,mid),dfs(mid+1,r);
}
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",t+i,c+i);
	for(int i=1;i<=n;i++){
		d[i]=t[i+1]-t[i];
		c[i]=c[i-1]+m-c[i];
		t[i]=-c[i];
	}
	mxd.init(d,n-1);
	sc.init(c,n);
	_sc.init(t,n);
	dfs(1,n);
	printf("%lld",ans);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

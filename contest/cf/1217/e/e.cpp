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


const ll MXN=8e5+5;
const ll MXD=10;

ll n,m,k;
struct mts{
	ll mn[MXD][2];
	inline mts(){memset(mn,0x3f,sizeof(mn));}
	inline mts operator + (const mts &b)const{
		mts res;
		for(int i=0;i<MXD;i++){
			if(mn[i][0]<b.mn[i][0]){
				res.mn[i][0]=mn[i][0];
				res.mn[i][1]=min(mn[i][1],b.mn[i][0]);
			}
			else{
				res.mn[i][0]=b.mn[i][0];
				res.mn[i][1]=min(mn[i][0],b.mn[i][1]);
			}
		}
		return res;
	}
	inline void set(ll x){
		ll tx=x;
		for(int i=0;i<MXD;i++){
			mn[i][0]=tx%10?x:INF;
			tx/=10;
		}
	}
}v[MXN];

#define ls (p<<1)
#define rs (p<<1|1)
inline void mod(ll p,ll l,ll r,ll mi,ll mv){
	if(l==r){
		v[p].set(mv);
		return;
	}
	ll mid=(l+r)>>1;
	if(mi<=mid)mod(ls,l,mid,mi,mv);
	else mod(rs,mid+1,r,mi,mv);
	v[p]=v[ls]+v[rs];
}
inline mts que(ll p,ll l,ll r,ll ql,ll qr){
	if(ql<=l && r<=qr)return v[p];
	ll mid=(l+r)>>1;mts res;
	if(ql<=mid)res=que(ls,l,mid,ql,qr);
	if(qr>mid)res=res+que(rs,mid+1,r,ql,qr);
	return res;
}
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		ll tmp;
		scanf("%lld",&tmp);
		mod(1,1,n,i,tmp);
	}
	while(m--){
		ll op,a,b;
		scanf("%lld%lld%lld",&op,&a,&b);
		if(op==1)mod(1,1,n,a,b);
		else{
			mts tmp=que(1,1,n,a,b);ll res=INF;
			for(ll i=0;i<MXD;i++)
				res=min(res,tmp.mn[i][0]+tmp.mn[i][1]);
			printf("%lld\n",res==INF?-1:res);
		}
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	solve();
	return 0;
}

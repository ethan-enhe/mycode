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

ll n,tx,ty;
char str[MXN];
ll suf[MXN][2],pre[MXN][2];
inline bool cant(ll t,ll x,ll y){return (x+y-t)&1 || abs(x)+abs(y)>t;}
inline bool chk(ll len){
	for(ll i=1;i+len-1<=n;i++){
		ll nx=tx-pre[i-1][0]-suf[i+len][0],ny=ty-pre[i-1][1]-suf[i+len][1];
		if(!cant(len,nx,ny))return 1;
	}
	return 0;
}


inline void solve(){
	scanf("%lld %s",&n,str+1);
	scanf("%lld%lld",&tx,&ty);
	if(cant(n,tx,ty)){
		puts("-1");
		return;
	}
	for(ll i=1;i<=n;i++){
		pre[i][0]=pre[i-1][0];
		pre[i][1]=pre[i-1][1];

		if(str[i]=='U')pre[i][1]++;
		if(str[i]=='D')pre[i][1]--;
		if(str[i]=='R')pre[i][0]++;
		if(str[i]=='L')pre[i][0]--;
	}
	for(ll i=n;i;i--){
		suf[i][0]=suf[i+1][0];
		suf[i][1]=suf[i+1][1];

		if(str[i]=='U')suf[i][1]++;
		if(str[i]=='D')suf[i][1]--;
		if(str[i]=='R')suf[i][0]++;
		if(str[i]=='L')suf[i][0]--;
	}
	ll l=0,r=n;
	while(l<r){
		ll mid=(l+r)>>1;
		if(chk(mid))r=mid;
		else l=mid+1;
	}
	printf("%lld",l);
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

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
struct tarr{
	ll d[MXN];
	inline void mod(ll x,ll y){for(;x<MXN;x+=x&(-x))d[x]+=y;}
	inline ll pre(ll x){ll r=0;for(;x;x-=x&(-x))r+=d[x];return r;}
}forw,backw;




ll n,m,k,sarr,sdiv;
inline void solve(){
	scanf("%lld",&n);
	for(ll i=1,tmp;i<=n;i++){
		scanf("%lld",&tmp);
		sarr+=tmp;
		sdiv+=backw.pre(tmp);
		sdiv+=forw.pre(MXN-1)*tmp*(MXN/tmp);
		//cout<<forw.pre(MXN-1)<<endl;
		for(ll j=tmp-1;j<MXN;j+=tmp)
			sdiv-=forw.pre(j)*tmp;
		for(ll j=tmp;j<MXN;j+=tmp)
			backw.mod(j,tmp);
		forw.mod(tmp,1);
		//cout<<sdiv<<endl;
		printf("%lld ",sarr*(i-1)-sdiv);
	}
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}


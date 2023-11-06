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


const ll MXN=1e5+5;

ll n,m,k;
ll fac[MXN],ifac[MXN];
inline ll c(ll x,ll y){
	if(y>x || y<0)return 0;
	return fac[x]*ifac[y]%P*ifac[x-y]%P;
}
inline void solve(){
	scanf("%lld%lld",&n,&m);
	m--;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			k=(k+c(i+m-1,m)*c(n-j+m,m))%P;
	printf("%lld",k);
    
}
int main(){
	fac[0]=ifac[0]=1;
	for(int i=1;i<MXN;i++){
		fac[i]=fac[i-1]*i%P;
		ifac[i]=qpow(fac[i],P-2);
	}

	
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

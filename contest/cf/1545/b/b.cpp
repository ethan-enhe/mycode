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


const ll MXN=5e5+5;

ll n,m,k;
ll fac[MXN],ifac[MXN];
char arr[MXN];
inline ll c(ll x,ll y){
	if(y>x || y<0)return 0;
	return fac[x]*ifac[x-y]%P*ifac[y]%P;
}
inline void solve(){
	scanf("%lld %s",&n,arr+1);
	int c1=0,co=0;
	for(int i=1,tc=0;i<=n;i++){
		if(arr[i]=='0'){
			co+=tc&1;
			tc=0;
		}
		else c1++,tc++;
	}

	printf("%lld\n",c(n-c1+((c1-co)>>1),n-c1));
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	fac[0]=1;
	for(ll i=1;i<MXN;i++)fac[i]=fac[i-1]*i%P;
	ifac[MXN-1]=qpow(fac[MXN-1],P-2);
	for(ll i=MXN-1;i;i--)ifac[i-1]=ifac[i]*i%P;

	ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

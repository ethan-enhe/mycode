#include<bits/stdc++.h>
using namespace std;

//{{{ Def
#define fastio ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define fileio \
	freopen("test.in","r",stdin)

#define il inline
#define fi first
#define se second
#define pb push_back
#define dbg(x) cerr<<#x<<"="<<(x)<<endl;
#define inv(x) qpow(x,P-2)

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll,ll> pi;
typedef vector<ll> vi;
//}}}
//{{{ Const
const char nl='\n';
const db EPS=1e-9;
const ull B=131;
const ll INF=1e18;
ll P=1e9+7;
//}}}
//{{{ Func
il ll qpow(ll x,ll y){
    ll r=1;
    while(y){
        if(y&1)r=r*x%P;
        x=x*x%P,y>>=1;
    }
    return r;
}
il ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
il ll mod(ll x){
	if(x>=P)return x-P;
	if(x<0)return x+P;
	return x;
}
il void madd(ll &x,ll y){x=mod(x+y);}
il void add(ll &x,ll y){x=x+y;}
il void cmx(ll &x,ll y){x=max(x,y);}
il void cmn(ll &x,ll y){x=min(x,y);}
//}}}
//{{{ Algo
//{{{ COMB
namespace comb{
	ll *fac,*ifac;
	il void init(ll sz){
		fac=(ll*)realloc(fac,sizeof(ll)*(sz+1));
		ifac=(ll*)realloc(ifac,sizeof(ll)*(sz+1));
		fac[0]=1;
		for(ll i=1;i<=sz;i++)fac[i]=fac[i-1]*i%P;
		ifac[sz]=inv(fac[sz]);
		for(ll i=sz;i;i--)ifac[i-1]=ifac[i]*i%P;
	}
	il ll c(ll x,ll y){
		if(y>x || y<0)return 0;
		return fac[x]*ifac[y]%P*ifac[x-y]%P;
	}
}
//}}}
//{{{ BIT
template<void (*f)(ll&,ll)>
struct tarr{
	ll *v,sz;
	il tarr(){v=NULL,sz=0;}
	il ~tarr(){free(v);}
	il void set(ll x=0){fill(v,v+sz,x);}
	il void rsz(ll x){v=(ll*)realloc(v,sizeof(ll)*((sz=x)+1));}
	il void mod(ll x,ll y){for(;x<=sz;x+=x&(-x))f(v[x],y);}
	il ll pre(ll x){ll r=0;for(;x;x^=x&(-x))f(r,v[x]);return r;}
};
//}}}
//}}}



const ll MXN=10+5;
ll n,m;
//前i次，有j次多余的，分成k个块
ll dp[MXN*MXN][MXN*MXN][MXN];

il void solve(){
	cin>>n>>P;
	memset(dp,0,sizeof(dp));
	dp[0][0][n]=1;
	for(ll i=0;i<=n*n;i++){
		ll cnt=0;
		for(ll j=0;j<=min(i,n*(n-1)/2);j++)
			for(int k=1;k<=n;k++){
				cerr<<i<<" "<<j<<" "<<k<<" "<<dp[i][j][k]<<endl;
				cnt+=dp[i][j][k];
				for(int l=1;l<=j && l<k;l++)
					madd(dp[i+1][j-l][k-l],dp[i][j][k]);
				madd(dp[i+1][j+1][k],dp[i][j][k]);
			}
		if(i)cout<<cnt<<" ";

	}
	cout<<endl;

	
}


int main(){
#ifndef ONLINE_JUDGE
	fileio;
#endif
	fastio;
	ll t;cin>>t;while(t--)
	solve();

	return 0;
}


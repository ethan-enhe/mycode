#include<bits/stdc++.h>
using namespace std;

//{{{ Def
#define il inline
#define fi first
#define se second
#define pb push_back
#define rsz resize
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
const ll INF=1e18,P=1e9+7;
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
il void add(ll &x,ll y){x=mod(x+y);}
template<class T>il void cmx(T &x,T y){x=max(x,y);}
template<class T>il void cmn(T &x,T y){x=min(x,y);}
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
struct tarr{
	ll *v,sz;
	il void rsz(ll x){v=(ll*)realloc(v,sizeof(ll)*((sz=x)+1));}
	il void clr(){for(int i=1;i<=sz;i++)v[i]=0;}
	il void mod(ll x,ll y){for(;x<=sz;x+=x&(-x))v[x]+=y;}
	il ll sum(ll x){ll r=0;for(;x;x^=x&(-x))r+=v[x];return r;}
};
//}}}
//}}}



const ll MXN=5e5+5;
ll n,m;
ll arr[MXN];

il void solve(){
	
}


int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	//ll t;cin>>t;while(t--)
	solve();

	return 0;
}

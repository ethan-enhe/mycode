#include<bits/stdc++.h>
using namespace std;

//{{{ Def
#define fastio ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define fileio \
	freopen(".in","r",stdin),\
	freopen(".out","w",stdout)

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



const ll MXN=1e7+5,MXP=5e6;
ll n,m,ans;
ll phi[MXN],pri[MXP],pw[MXN],inv[MXN],pric;

il void solve(){
	cin>>n>>m;
	//ll t0=clock();
	inv[1]=phi[1]=1;
	for(ll i=2;i<=n;i++){
		if(!phi[i]){
			phi[i]=i-1;
			pri[++pric]=i;
			pw[i]=qpow(i,m);
			inv[i]=qpow(i,P-2);
		}
		ans=(ans+(pw[i]-1)*inv[i-1]%P*phi[i])%P;
		for(ll j=1;i*pri[j]<=n;j++){
			pw[i*pri[j]]=pw[i]*pw[pri[j]]%P;
			inv[i*pri[j]]=inv[i]*inv[pri[j]]%P;
			if(i%pri[j])phi[i*pri[j]]=phi[i]*phi[pri[j]];
			else{
				phi[i*pri[j]]=phi[i]*pri[j];
				break;
			}
		}
	}
	cout<<(ans+m)%P;
//	cerr<<endl<<double(clock()-t0)/CLOCKS_PER_SEC;

	
}


int main(){
#ifndef ONLINE_JUDGE
	//fileio;
#endif
	fastio;
	//ll t;cin>>t;while(t--)
	solve();

	return 0;
}


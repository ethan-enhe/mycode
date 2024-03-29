#include<bits/stdc++.h>
using namespace std;

//{{{ Def
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



const ll MXN=5e5+5;
ll n,m,totv,validc,ans;
string str,buf;
string split[MXN];
pi res[MXN];

il pi cal(string &x){
	//mod!!!
	ll res=0,tot=1,curv=0,curd=1;
	for(size_t i=x.size()-1;i;i--){
		if(x[i]=='*'){
			tot=tot*curv%P;
			curv=0;
			curd=1;
		}
		else{
			curv=(curv+curd*(x[i]-'0'))%P;
			curd=curd*10%P;
			if(x[i-1]!='*')res=(res+curv*tot)%P;
		}
	}
	tot=1,curv=0;
	for(size_t i=0;i<x.size()-1;i++){
		if(x[i]=='*'){
			tot=tot*curv%P;
			curv=0;
		}
		else{
			curv=(curv*10+(x[i]-'0'))%P;
			if(x[i+1]!='*')res=(res+curv*tot)%P;
		}
	}
	curv=(curv*10+(x[x.size()-1]-'0'))%P;
	return pi(tot*curv%P,res);
}
il void solve(){
	cin>>str;
	for(char x:str){
		if(x=='+')split[++n]=buf,buf="";
		else buf+=x;
	}
	split[1]=buf+split[1];
	for(int i=1;i<=n;i++){
		res[i]=cal(split[i]);
		totv=(totv+res[i].fi)%P;
		validc=(validc+split[i].size()-1)%P;
	}
	for(int i=1;i<=n;i++)
		ans=(ans+(totv-res[i].fi)*(split[i].size()-1)+res[i].se+res[i].fi*(validc-split[i].size()+1))%P;
	cout<<ans;
}


int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	//ll t;cin>>t;while(t--)
	solve();

	return 0;
}


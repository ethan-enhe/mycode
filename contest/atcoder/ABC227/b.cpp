#include<bits/stdc++.h>
using namespace std;

//{{{ Def
#define fi first
#define se second
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll,ll> pi;
typedef vector<ll> vi;
typedef vector<pi> vpi;
//}}}
const char nl='\n';
const ld EPS=1e-9;
const ull B=131;
const ll INF=1e18;
ll P=1e9+7;
//{{{ Func
inline pi operator + (const pi &x,const pi &y){return pi(x.fi+y.fi,x.se+y.se);}
inline pi operator - (const pi &x,const pi &y){return pi(x.fi-y.fi,x.se-y.se);}
inline pi operator * (const pi &x,const ll &y){return pi(x.fi*y,x.se*y);}
inline ll qpow(ll x,ll y){
    ll r=1;
    while(y){
        if(y&1)r=r*x%P;
        x=x*x%P,y>>=1;
    }
    return r;
}
inline ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
inline ll exgcd(ll x,ll y,ll &rx,ll &ry){
	if(!y){
		rx=1,ry=0;
		return x;
	}
	ll g=exgcd(y,x%y,rx,ry);
	swap(rx,ry);
	ry-=rx*(x/y);
	return g;
}
inline ll mod(ll x){
	if(abs(x)>=(P<<1))return x%P;
	if(x>=P)return x-P;
	if(x<=-P)return x+P;
	return x;
}
inline void madd(ll &x,ll y){x=mod(x+y);}
inline void add(ll &x,ll y){x=x+y;}
inline void umx(ll &x,ll y){x=max(x,y);}
inline void umn(ll &x,ll y){x=min(x,y);}
//}}}

const ll MXN=1000;
ll n,m;
ll arr[MXN];

inline bool chk(int x){
	for(int a=1;a<=MXN;a++)
		for(int b=1;b<=MXN;b++){
			if(4*a*b+3*a+3*b==x)
				return 0;
		}
	return 1;

}
inline void solve(){
	cin>>n;
	ll ans=0;
	for(int i=1;i<=n;i++){
		ll tmp;
		cin>>tmp;
		ans+=chk(tmp);
	}
	cout<<ans;

	
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
#endif
	//ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

	//ll t;cin>>t;while(t--)
	solve();

	return 0;
}


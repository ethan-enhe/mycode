#include<bits/stdc++.h>
#include <cstdio>
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
const ll INF=1e18,P=1e9+7;
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

const ll MXN=1e3+5;
ll n,m;
ll tmp[MXN];
ll arr[MXN][MXN],brr[MXN][MXN];

inline void mod(ll x,ll y,ll z){
	z%=P;
	madd(brr[x][y],z);
	for(ll i=1;i<=n;i++)madd(arr[i][y],z);
	for(ll i=1;i<=m;i++)madd(arr[x][i],z);
	madd(arr[x][y],-z);
}
inline void prt(){
	ll s=0;
	for(int i=1;i<=n;i++,cerr<<endl)
		for(int j=1;j<=m;j++){
			cerr<<arr[i][j]<<" ";
			madd(s,arr[i][j]);
		}
	cerr<<s<<endl;
}
inline void solve(){
	scanf("%lld%lld",&n,&m);
	ll sum=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%lld",&arr[i][j]);
			madd(sum,arr[i][j]);
		}
	mod(1,1,-sum*qpow(n+m-1,P-2));
	for(int i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			madd(tmp[i],arr[i][j]);
	for(int i=1;i<=n;i++){
		mod(i,1,-tmp[i]*qpow(m-1,P-2));
		tmp[i]=0;
	}
	for(int i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			madd(tmp[j],arr[i][j]);
	for(int i=1;i<=m;i++)
		mod(1,i,-tmp[i]*qpow(n-1,P-2));
	for(int i=2;i<=n;i++)
		for(int j=2;j<=m;j++){
			madd(brr[i][j],arr[i][j]);
			madd(brr[i][1],-arr[i][j]);
			madd(brr[1][j],-arr[i][j]);
			madd(brr[1][1],arr[i][j]);
			madd(arr[1][1],-arr[i][j]);
			madd(arr[i][1],arr[i][j]);
			madd(arr[1][j],arr[i][j]);
		}
	bool f=1;
	for(int i=1;i<=n;i++)
		if(arr[i][1]%P)
			f=0;
	for(int i=1;i<=m;i++)
		if(arr[1][i]%P)
			f=0;
	if(f){
		puts("1");
		for(int i=1;i<=n;i++,putchar('\n'))
			for(int j=1;j<=m;j++)
				printf("%lld ",(P-brr[i][j])%P);
	}
	else puts("-1");
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


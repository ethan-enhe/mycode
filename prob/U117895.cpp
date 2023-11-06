#include<bits/stdc++.h>
#include <cstdio>
#include <queue>
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

const ll MXN=1e6+5;
ll n,m,lb,rb;
ll en[MXN];
pi arr[MXN];

priority_queue<ll> q;
inline bool inter(ll a,ll b,ll c,ll d){
	if(a>c)swap(a,c),swap(b,d);
	return b>=c;
}
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&arr[i].fi,&arr[i].se);
	scanf("%lld%lld",&lb,&rb);
	sort(arr+1,arr+1+n);
	ll ans=INF;
	arr[++n]={INF,0};
	for(int i=1;i<=m;i++)q.push(0);
	for(int i=1;i<=n;i++){
		en[i]=max(-q.top(),arr[i].fi)+arr[i].se;q.pop();
		q.push(-en[i]);
		en[i]=-q.top();
	}
	for(int i=1;i<=n;i++)
		if(lb<=arr[i].fi && rb>=arr[i].fi)
			ans=min(ans,max(0ll,en[i-1]-arr[i].fi));
	for(int i=n;i;i--)
		if(arr[i].fi<=rb){
			ans=min(ans,max(0ll,en[i]-rb));
			break;
		}
	printf("%lld",ans);


	
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


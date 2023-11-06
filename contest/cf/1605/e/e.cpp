#include<bits/stdc++.h>
#include <queue>
#include <vector>
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

const ll MXN=2e6+5,MXQ=1e6+5;
ll n,m;
ll arr[MXN],brr[MXN],ans[MXN];
pi op[MXN];


struct delt{
	ll st,end,init,k;
	inline bool operator < (const delt &b) const{return end>b.end;}
};
vector<delt> ask[MXN];
priority_queue<delt> q;
inline void ins(ll l,ll r,ll a,ll b){
	if(l>r || l>MXQ)return;
	ask[l].push_back({l,r+1,a,b});
}
inline ll cal(pi x,ll y){
	ll r=x.fi*y+x.se;
	if(r<0)r=-r;
	return r;
}
inline void solve(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
		scanf("%lld",arr+i);
	for(ll i=1;i<=n;i++){
		scanf("%lld",brr+i);
		if(i==1)brr[i]=0;
		op[i]={0,brr[i]-arr[i]};
	}
	op[1].fi=1;
	for(ll i=1;i<=n;i++){
		for(ll j=i<<1;j<=n;j+=i)
			op[j]=op[j]-op[i];
		if(!op[i].fi)
			ins(1,MXQ,abs(op[i].se),0);
		else{
			if(op[i].fi<0){
				op[i].fi=-op[i].fi;
				op[i].se=-op[i].se;
			}
			ll low=max(1ll,(op[i].fi-op[i].se-1)/op[i].fi);
			ins(low,MXQ,cal(op[i],low),op[i].fi);
			if(low>1)ins(1,low-1,cal(op[i],1),-op[i].fi);
		}
	}
	ll curva=0,curk=0;
	for(ll i=1;i<=MXQ;i++){
		for(delt &j:ask[i]){
			curva+=j.init;
			curk+=j.k;
			q.push(j);
		}
		while(!q.empty() && q.top().end<=i){
			delt p=q.top();q.pop();
			curk-=p.k;
			curva-=p.init+p.k*(i-p.st);
		}
		ans[i]=curva;
		curva+=curk;
	}
	scanf("%lld",&m);
	while(m--){
		ll x;
		scanf("%lld",&x);
		printf("%lld\n",ans[x]);
	}
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


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


const ll MXN=1e6+5;

ll n,m,k;
char str[MXN];
int mn=10;
inline void dfs(int num,int ina,int inb){
	if(num==11)return;
	if(inb>ina+5-(num>>1) || ina>inb+5-((num-1)>>1)){
		mn=min(num-1,mn);
		return;
	}
	if(str[num]=='1'){
		if(num&1)dfs(num+1,ina+1,inb);
		else dfs(num+1,ina,inb+1);
	}
	else if(str[num]=='0')dfs(num+1,ina,inb);
	else{
		if(num&1)dfs(num+1,ina+1,inb);
		else dfs(num+1,ina,inb+1);
		dfs(num+1,ina,inb);
	}
}
inline void solve(){
	cin>>(str+1);
	mn=10;
	dfs(1,0,0);
	cout<<mn<<endl;
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

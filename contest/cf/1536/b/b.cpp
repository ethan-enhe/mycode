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
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=1e3+5;

ll n,m,k;
ll pre[MXN];

char str[MXN],res[MXN];
inline bool match(ll len){
	for(int i=1;i+len-1<=n;i++){
		bool f=1;
		for(int j=1;j<=len;j++)
			if(str[i+j-1]!=res[j]){
				f=0;
				break;
			}
		if(f)return 1;
	}
	return 0;
}
inline bool dfs(int dep,int goal){
	if(dep>goal){
		res[dep]=0;
		if(!match(goal))return cout<<(res+1)<<endl,1;
		return 0;
	}
	for(int i=0;i<26;i++){
		res[dep]=i+'a';
		if(dfs(dep+1,goal))return 1;
	}
	return 0;
}
inline void solve(){
	scanf("%lld %s",&n,str+1);
	for(int i=1;i<=n;i++)
		if(dfs(1,i))return;
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

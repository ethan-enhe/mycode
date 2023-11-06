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


const ll MXN=5005;

ll n,m,k;
ll s[MXN],t[MXN];
vector<ll> e[MXN];
bool vis[MXN];
inline bool dfs(int p,int rt){
	vis[p]=1;
	for(ll &nx:e[p]){
		if(nx==rt)return 1;
		if(!vis[nx])if(dfs(nx,rt))return 1;
	}
	return 0;
}
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",s+i,t+i);
		e[s[i]].pb(t[i]);
	}
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(dfs(i,i)){
			puts("2");
			for(int i=1;i<=m;i++)printf("%lld ",1ll+(s[i]<t[i]));
			return;
		}
	}
	puts("1");
	for(int i=1;i<=m;i++)printf("1 ");
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

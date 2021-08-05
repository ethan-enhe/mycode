#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rd scanf
#define pt printf
#define setp(x) setprecision(x)
#define mem(x,y) memset(x,y,sizeof(x))
#define sz(x) (int)x.size()
#define umn(x,y) x=min(x,y)
#define umx(x,y) x=max(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;
typedef queue<ll> qi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

const ll INF=1e18;
const ll P=1e9+7;
const ll MXN=1e6+5;

inline ll mod(const ll &x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(const ll &x,const ll &y){return !y?x:gcd(y,x%y);}
inline void pbin(const ll &x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}



ll n,m,k,cnt[MXN];
vi e[MXN];
void dfs(int p,int fa,int dpth){
	cnt[dpth]++;
	for(int j=0;j<e[p].size();j++){
		int nx=e[p][j];
		if(nx==fa)continue;
		dfs(nx,p,dpth+1);
	}
}
inline void solve(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		int ts,tt;
		scanf("%d%d",&ts,&tt);
		e[ts].pb(tt);
		e[tt].pb(ts);
	}
	dfs(1,0,1);
	ll res=1;
	for(int i=1;i<=n;i++)
		res=res*max(cnt[i],1ll)%998244353;
	printf("%lld",res);
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);

	ll tq=1;
	while(tq--)solve();
	return 0;
}

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
const ll MXN=2e5+5;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


struct edge{
	ll ts,tt,tw;
	edge(ll ts=0,ll tt=0,ll tw=0):ts(ts),tt(tt),tw(tw){}
	bool operator < (const edge &b)const{return tw<b.tw;}
}ne[MXN];

ll n,res,colc,color[MXN];
vector<ll> e[MXN];
void dfs(ll p){
	color[p]=colc;
	for(size_t i=0;i<e[p].size();i++){
		ll nx=e[p][i];
		if(color[nx])continue;
		dfs(nx);
	}
}

ll fa[MXN];
ll find(ll x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		ll x,y,z,w,va;
		scanf("%lld%lld%lld%lld%lld",&va,&x,&y,&z,&w);
		ne[i]=edge(x,z,va);
		e[x].pb(y),e[y].pb(x);
		e[z].pb(w),e[w].pb(z);
	}
	for(int i=1;i<=(n<<1);i++)
		if(!color[i]){
			++colc;
			fa[colc]=colc;
			dfs(i);
		}
	for(int i=1;i<=n;i++)
		ne[i].ts=color[ne[i].ts],ne[i].tt=color[ne[i].tt];
	sort(ne+1,ne+1+n);
	for(int i=1;i<=n;i++)
		if(find(ne[i].ts)!=find(ne[i].tt)){
			fa[fa[ne[i].ts]]=fa[ne[i].tt];
			res+=ne[i].tw;
		}
	printf("%lld",res);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios_base::sync_with_stdio(0);cin.tie(0);
	cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	ll tq=1;
	//cin>>tq;
	while(tq--)solve();
	return 0;
}

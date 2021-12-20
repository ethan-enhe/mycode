#include <bits/stdc++.h>

using namespace std;

//{{{ Def
#define fi first
#define se second
#define pb push_back
#define log(fmt...) fprintf(stderr, fmt)
#define va2d(x, y) x[(y.fi)][(y.se)]

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
const ll INF = 1e18,MXN = 1e6 + 5;
ll n, m,si;
vector<pi> g[MXN];
pi arr[MXN],s,t;
void ae(ll u,ll v,ll w){
	g[u].push_back({v,w});
}
ll dis[MXN];
bool vis[MXN];
priority_queue<pi,vector<pi>,greater<pi>> q;
void dij(){
	memset(dis,0x3f,sizeof(dis));
	for(ll i=1;i<=n;i++)
		if(arr[i]==s){
			q.push({dis[i]=0,si=i});
			break;
		}
	while(!q.empty()){
		ll p=q.top().se;q.pop();
		if(vis[p])continue;
		vis[p]=1;
		for(pi &nx:g[p]){
			ll nd=dis[p]+nx.se;
			if(nd<dis[nx.fi])
				q.push({dis[nx.fi]=nd,nx.fi});
		}
	}
	for(ll i=1;i<=n;i++)
		if(arr[i]==t && i!=si){
			printf("%lld",dis[i]);
			break;
		}
}
void solve() {
    // code
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)
		scanf("%lld",&arr[i].se);
	for(ll i=1;i<=n;i++)
		scanf("%lld",&arr[i].fi);
	s=arr[1],t=arr[n];
	sort(arr+1,arr+1+n);
	for(ll i=n;i;i--){
		ae(n+i,i,0);
		if(i!=n)ae(n+i,n+i+1,arr[i+1].fi-arr[i].fi);
		ae(i,n+1,arr[i].se+arr[1].fi);
		ll ind=lower_bound(arr+1,arr+1+n,pi{m-arr[i].se,-1})-arr;
		ae(i,n+ind,arr[i].se+arr[ind].fi-m);
	}
	dij();
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    // ll t;scanf("%lld",&t);while(t--)
    solve();

    return 0;
}


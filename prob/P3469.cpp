#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1e6+5;
ll n,m;
vector<ll> g[MXN],t[MXN];
void ae(vector<ll> *_g,ll u,ll v){
	_g[u].push_back(v);
	_g[v].push_back(u);
}
ll dfn[MXN],low[MXN],dfnc,sqrc;
stack<ll> stk;
void tj(ll p){
	dfn[p]=low[p]=++dfnc;
	stk.push(p);
	for(ll nx:g[p]){
		if(!dfn[nx]){
			tj(nx);
			low[p]=min(low[nx],low[p]);
			if(low[nx]==dfn[p]){
				ll x;
				++sqrc;
				do{
					x=stk.top();stk.pop();
					ae(t,x,sqrc);
				}while(x!=nx);
				ae(t,p,sqrc);
			}
		}
		else low[p]=min(low[p],dfn[nx]);
	}
}
ll ans[MXN];
ll dfs(ll p,ll fa){
	ll sz=p<=n;
	for(ll nx:t[p])
		if(nx!=fa){
			int tmp=dfs(nx,p);
			sz+=tmp;
			ans[p]+=tmp*(n-tmp);
		}
	ans[p]+=(n-sz)*sz;
	return sz;
}
int main(){
	freopen("test.in","r",stdin);
	scanf("%lld%lld",&n,&m);
	sqrc=n;
	while(m--){
		ll u,v;
		scanf("%lld%lld",&u,&v);
		ae(g,u,v);
	}
	tj(1);
	dfs(1,0);
	for(ll i=1;i<=n;i++)
		printf("%lld\n",ans[i]+n-1);

	return 0;
}

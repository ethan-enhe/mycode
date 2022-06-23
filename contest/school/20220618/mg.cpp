#include<bits/stdc++.h>

using namespace std;
using ll=long long;
const char nl='\n';
const ll MXN=4e5+5;
struct edge{
	ll v,id;
};
vector<edge> g[MXN];
ll n,m;
ll ans[MXN];


namespace tree{
	void main(){
		fill(ans+1,ans+1+n,n);
		for(ll i=1;i<=n;i++)
			if(g[i].size()==1)
				ans[g[i].front().id]--;
	}
}


namespace force{
	//0:不联通，没有1连通块，1：不连通，且有1连通块 2，联通
	bool vis[MXN];
	ll gsz(ll p,ll del){
		if(vis[p])return 0;
		vis[p]=1;
		ll sz=1;
		for(auto &nx:g[p])
			if(nx.id!=del)sz+=gsz(nx.v,del);
		return sz;
	}
	ll connect(ll del){
		fill(vis+1,vis+1+n,0);
		ll res=gsz(1,del);
		if(res==n)return 2;
		if(res==1 || res==n-1)return 1;
		return 0;
	}
	ll dfn[MXN],low[MXN],dfnc,cutc;
	void tj(ll p,ll del,bool isrt=0){
		dfn[p]=low[p]=++dfnc;
		ll sz=0;
		for(auto &nx:g[p])
			if(nx.id!=del){
				if(!dfn[nx.v]){
					tj(nx.v,del);
					low[p]=min(low[p],low[nx.v]);
					if(low[nx.v]==dfn[p])++sz;
				}
				else low[p]=min(low[p],dfn[nx.v]);
			}
		if((!isrt && sz) || (isrt && sz>1))++cutc;
	}
	ll cal(ll del){
		ll con=connect(del);
		if(con<=1)return n-con;
		fill(dfn+1,dfn+1+n,dfnc=cutc=0);
		tj(1,del,1);
		return cutc;
	}
	void main(){
		for(ll i=1;i<=m;i++)
			ans[i]=cal(i);
	}

}



int main(){
	freopen("mg.in","r",stdin);
	freopen("mg.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	if(n==2){
		for(ll i=1;i<=m;i++)
			cout<<0<<nl;
		return 0;
	}
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		g[u].push_back({v,i});
		g[v].push_back({u,i});
	}
	if(m==n-1)tree::main();
	else force::main();
	for(ll i=1;i<=m;i++)
		cout<<ans[i]<<nl;
	return 0;
}

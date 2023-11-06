#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;
const char nl='\n';


const ll MXN=1e5+5,INF=1e17;
ll n,m;
ll ans[MXN],cnt[MXN];
vector<pi> g[MXN];

namespace force{
	ll tot;
	ll dpth[MXN],_fa[MXN];
	void init(ll p,ll fa){
		_fa[p]=fa;
		dpth[p]=dpth[fa]+1;
		for(auto &nx:g[p])
			if(nx.fi!=fa)
				init(nx.fi,p);
	}
	struct path{
		ll s,l,t;
		ll len()const{return dpth[s]+dpth[t]-dpth[l]*2;}
		ll notupd()const{return cnt[s]+cnt[t]-cnt[l]-cnt[_fa[l]];}
		bool operator < (const path &b)const{return len()>b.len();}
	};
	vector<path> paths;
	ll _cnt[MXN];
	bool invalid(ll x){
		return _cnt[x] && _cnt[x]!=cnt[x];
	}
	void dfs(ll p,ll fa,ll lca,ll s,ll inv){
		if(dpth[p]<dpth[lca])lca=p;
		if(!inv && p>=s){
			paths.push_back({s,lca,p});
		}
		for(auto &nx:g[p])
			if(nx.fi!=fa){
				inv-=invalid(nx.se);
				++_cnt[nx.se];
				inv+=invalid(nx.se);

				dfs(nx.fi,p,lca,s,inv);

				inv-=invalid(nx.se);
				--_cnt[nx.se];
				inv+=invalid(nx.se);
			}
	}
	bool upd(ll p,ll fa,ll t,ll len){
		bool f=p==t;
		for(auto &nx:g[p])
			if(nx.fi!=fa)
				f|=upd(nx.fi,p,t,len);
		if(!f && ans[p]>INF)ans[p]=len;
		return f;
	}
	void calcnt(ll p,ll fa){
		tot+=ans[p]>INF;
		cnt[p]+=ans[p]>INF;
		for(auto &nx:g[p])
			if(nx.fi!=fa){
				cnt[nx.fi]=cnt[p];
				calcnt(nx.fi,p);
			}
	}
	void main(){
		init(1,n+1);
		dpth[0]=INF;
		for(ll i=1;i<=n;i++)
			dfs(i,0,0,i,0);
		sort(paths.begin(),paths.end());
		//到根路径上有几个没更新
		copy(dpth+1,dpth+1+n,cnt+1);
		tot=n;//总共几个没更新
		for(auto &i:paths){
			if(i.notupd()!=tot){
				upd(i.s,0,i.t,i.len());
				cnt[1]=0;
				tot=0;
				calcnt(1,0);
			}
		}
	}
}


int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	memset(ans,0x3f,sizeof(ans));
	for(ll i=1,u,v,c;i<n;i++){
		cin>>u>>v>>c;
		++cnt[c];
		g[u].push_back({v,c});
		g[v].push_back({u,c});
	}
	if(n<=1000)force::main();
	while(m--){
		ll x;
		cin>>x;
		cout<<ans[x]<<nl;
	}

	return 0;
}

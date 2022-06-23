#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
const char nl='\n';
const ll MXN=1e5+5,INF=1e18;
ll n,m,s;
vector<ll> g[MXN];
ll last[MXN],cur[MXN];

const ull B=1e9+7;
ull h(ll *x){
	ull r=0;
	for(ll i=1;i<=n;i++)
		r=r*B+x[i];
	return r;
}
map<ull,ll> vis;


mt19937_64 mr(time(0));

int main(){
	freopen("mashiro.in","r",stdin);
	freopen("mashiro.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//for(ll i=1;;i++){
		cin>>n>>m>>s;
		//n=mr()%100000+2;
		//m=mr()%1000000+1;
		for(ll i=1;i<=n;i++)
			g[i].clear();
		vis.clear();
		iota(cur+1,cur+1+n,1);
		while(m--){
			ll u,v;
			cin>>u>>v;
			//u=mr()%n+1;
			//do v=mr()%n+1;while(v==u);

			g[u].push_back(v);
		}
		for(ll i=1;;i++){
			copy(cur+1,cur+1+n,last+1);
			for(ll j=1;j<=n;j++){
				cur[j]=j;
				for(ll k:g[j])
					cur[j]=(i&1)?min(cur[j],last[k]):max(cur[j],last[k]);
			}

			ull ch=h(cur);
			if(vis[ch]){
				cout<<((i&1)?last[s]:cur[s]);
				//cout<<i<<" "<<(i-vis[ch])<<endl;
				break;
			}
			vis[ch]=i;
		}
		/*
		for(ll i=1;i<=n;i++)
			cerr<<cur[i]<<" ";
		cerr<<endl;
		for(ll i=1;i<=n;i++)
			cerr<<last[i]<<" ";
		cerr<<endl;
		*/
	return 0;
}


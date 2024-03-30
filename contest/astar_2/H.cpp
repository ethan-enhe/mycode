#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const ll P=998244353;

ll qpow(ll x,ll y){
	ll r=1;
	y=(y+P-1)%(P-1);
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
const int MXN=2e5+5;
const int B=1500;
const int N_B=MXN/B+5;

int n,q,bigc;
int id[MXN];
bitset<MXN> adj[N_B];
int ans[N_B][N_B];
vector<int> nei[MXN];

int qry(int x,int y){
	if(nei[x].size()>nei[y].size())swap(x,y);
	if(nei[x].size()>B){
		x=id[x];
		y=id[y];
		if(x>y)swap(x,y);
		return ans[x][y];
	}
	else if(nei[y].size()>B){
		int cnt=0;
		for(int i:nei[x])
			cnt+=adj[id[y]][i];
		return cnt;
	}
	else{
		int cnt=0,idy=0;
		for(int i:nei[x]){
			while(idy<(int)nei[y].size()-1 && nei[y][idy+1]<=i)++idy;
			if(idy<(int)nei[y].size() && nei[y][idy]==i)++cnt;
		}
		return cnt;
	}
}


int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		int m;
		cin>>m;
		while(m--){
			int x;
			cin>>x;
			nei[x].push_back(i);
		}
	}


	for(int i=1;i<MXN;i++)
		if(nei[i].size()>B){
			id[i]=++bigc;
			for(int j:nei[i])
				adj[bigc][j]=1;
		}
	for(int i=1;i<=bigc;i++)
		for(int j=i+1;j<=bigc;j++){
			ans[i][j]=(adj[i]&adj[j]).count();
		}
	while(q--){
		int x,y;
		cin>>x>>y;
		ll res=qry(x,y);
		if(res==0)cout<<-1<<'\n';
		else{
			res=n*qpow(res,-1)%P;
			cout<<res<<'\n';
		}
	}
	return 0;
}




#include<bits/stdc++.h>
using namespace std;
const int MXN=2e5+5;
const char nl='\n';
int n,arr[MXN];
vector<int> g[MXN];
bool oncyc[MXN];
int dp[MXN][2];
bool vis[MXN];
void dfs(int p){
	vis[p]=1;
	dp[p][1]=1;
	for(auto nx:g[p]){
		if(oncyc[nx])continue;
		dfs(nx);
		dp[p][1]+=dp[nx][0];
		dp[p][0]+=max(dp[nx][1],dp[nx][0]);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
		g[arr[i]].push_back(i);
	}

	int ans=0;
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			int p=i;
			while(!vis[p]){
				vis[p]=1;
				p=arr[p];
			}
			vector<int> c;
			while(!oncyc[p]){
				oncyc[p]=1;
				c.push_back(p);
				p=arr[p];
			}
			const int INF=1e9;
			int cdp[2][2]={{0,-INF},{-INF,0}};
			for(auto j:c){
				dfs(j);
				//cerr<<j<<" "<<dp[j][0]<<" "<<dp[j][1]<<endl;
				int tmp=cdp[0][0];
				cdp[0][0]=max(cdp[0][0],cdp[0][1])+dp[j][0];
				cdp[0][1]=tmp+dp[j][1];
				tmp=cdp[1][0];
				cdp[1][0]=max(cdp[1][0],cdp[1][1])+dp[j][0];
				cdp[1][1]=tmp+dp[j][1];
			}
			ans+=max(cdp[0][0],cdp[1][1]);
		}
	cout<<ans<<nl;
	return 0;
}



#include<bits/stdc++.h>
using namespace std;
const int MXN=1e6+5;
const int INF=1e9;

vector<int> e[MXN];
bool vis[MXN];
int n,fa[MXN];
int dp[MXN][2];
inline void dfs(int p,int rt,bool f){
	vis[p]=1,dp[p][0]=0,dp[p][1]=-INF;
	for(int nx:e[p])
		if(nx!=rt){
			dfs(nx,rt,f);
			dp[p][0]+=max(dp[nx][0],dp[nx][1]);
			dp[p][1]=max(dp[p][1],dp[nx][0]-max(dp[nx][0],dp[nx][1]));
		}
	if(p==rt || p!=fa[rt] || !f)dp[p][1]+=dp[p][0]+1;
	else dp[p][1]=-INF;
}
inline int solve(int x){
	while(!vis[fa[x]]){
		vis[x]=1;
		x=fa[x];
	}
	int ans=0;
	dfs(x,x,1),ans=max(ans,dp[x][1]);
	dfs(x,x,0),ans=max(ans,dp[x][0]);
	return ans;
}


int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",fa+i);
		e[fa[i]].push_back(i);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			ans+=solve(i);
		}
	printf("%d",ans);
	return 0;
}


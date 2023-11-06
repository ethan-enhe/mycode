#include <bits/stdc++.h>
using namespace std;
const int MXN=305,INF=1e9;
int n,arr[MXN],dp[MXN][MXN][MXN];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",arr+i);
			arr[i]=min(n,arr[i]+i);
		}
		for(int i=1;i<=n+1;i++)
			for(int j=1;j<=n+1;j++)
				for(int k=1;k<=n+1;k++)
					dp[i][j][k]=INF;
		dp[n][n][n+1]=0;
		for(int i=n;i>1;i--)
			for(int j=i;j<=n+1;j++)
				for(int k=i;k<=n+1;k++){
					if(arr[i-1]<j)dp[i-1][j][k]=min(dp[i-1][j][k],dp[i][j][k]);
					else if(arr[i-1]<k)dp[i-1][i-1][j]=min(dp[i-1][i-1][j],dp[i][j][k]);
					else dp[i-1][i-1][i-1]=min(dp[i-1][i-1][i-1],dp[i][j][k]);
					dp[i-1][j][k]=min(dp[i-1][j][k],dp[i][j][k]+1);
				}
		int ans=INF;
		for(int i=2;i<=n+1;i++)
			ans=min(ans,dp[1][1][i]);
		printf("%d\n",ans);
	}
	return 0;
}

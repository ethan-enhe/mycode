#include<bits/stdc++.h>
using namespace std;
const int MXN=3900;
int dp[MXN][2];
int n,b,ans,arr[MXN];
int main(){
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++)scanf("%d",arr+i);
	for(int t=0;t<2;t++){
		memset(dp,~0x3f,sizeof(dp));
		dp[0][t]=0;
		for(int i=1;i<=n;i++){
			for(int j=i;j;j--){
				dp[j][0]=max(dp[j][1],dp[j][0]);
				dp[j][1]=max(dp[j-1][1]+arr[i],dp[j-1][0]);
			}
			dp[0][0]=0,dp[0][1]=-1e9;
		}
		ans=max(ans,dp[b][t]);
	}
	printf("%d",ans);



	return 0;
}

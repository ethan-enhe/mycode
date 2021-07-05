#include<bits/stdc++.h>
using namespace std;
const int P=1e9+7;
const int MXN=205;
int t,n,arr[MXN];
char str[MXN];
bool vld[MXN][MXN];
int dp[MXN][MXN][MXN][3];
inline void add(int &x,int y){if((x+=y)>=P)x-=P;}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",arr+i);
		for(int i=1;i<=n;i++){
			vld[0][i]=1;
			scanf("%s",str+1);
			for(int j=1;j<=n;j++)
				vld[i][j]=str[j]-'0';
		}
		memset(dp,0,sizeof dp);
		dp[0][0][0][0]=1;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				for(int k=0;k<=n;k++){
					add(dp[i+1][j][k][0],dp[i][j][k][0]);
					if(vld[arr[j]][arr[i+1]])add(dp[i+1][j][k][1],dp[i+1][j][k][0]);

					add(dp[i][j+1][k][1],dp[i][j][k][1]);
					if(arr[i]==arr[j+1])add(dp[i][j+1][k][2],dp[i][j][k][1]);

					add(dp[i][j][k+1][2],dp[i][j][k][2]);
					if(arr[i]==arr[k+1])add(dp[i][j][k+1][0],dp[i][j][k][2]);
				}
		int ans=0;
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				add(ans,dp[n][j][k][0]);
		printf("%d\n",ans);
	}
	return 0;
}

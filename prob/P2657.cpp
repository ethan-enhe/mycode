#include<bits/stdc++.h>
using namespace std;
const int MXD=11;
char str[MXD];
int n,dp[MXD][MXD][2][2];
inline int cal(){
	memset(dp,0,sizeof(dp));
	dp[0][0][1][1]=1;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=9;j++)
			for(int k=0;k<=9;k++){
				if(abs(j-k)>=2){
					dp[i+1][k][0][0]+=dp[i][j][0][0];
					if(k<=str[i+1]-'0')dp[i+1][k][k==str[i+1]-'0'][0]+=dp[i][j][1][0];
				}
				dp[i+1][k][0][k==0]+=dp[i][j][0][1];
				if(k<=str[i+1]-'0')dp[i+1][k][k==str[i+1]-'0'][k==0]+=dp[i][j][1][1];
			}
	int ans=0;
	for(int i=0;i<=9;i++)
		ans+=dp[n][i][0][0]+dp[n][i][1][0];
	return ans;
}
int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	int i=n;
	for(;str[i]=='0';i--)str[i]='9';
	str[i]--;
	int tmp=cal();
	scanf("%s",str+1);
	n=strlen(str+1);
	printf("%d",cal()-tmp);

	return 0;
}

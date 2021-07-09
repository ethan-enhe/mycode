#include<bits/stdc++.h>
using namespace std;
const int MXN=11;
char str[MXN];
int dp[MXN][MXN*MXN][MXN*MXN][2];
inline int cal(int sum){
	int n=strlen(str+1);
	memset(dp,0,sizeof(dp));
	dp[0][0][0][1]=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<sum;j++)
			for(int k=0;k<=sum;k++){
				int nxj=j*10%sum,nxk=k;
				for(int l=0;l<=9;l++){
					dp[i+1][nxj][nxk][0]+=dp[i][j][k][0];
					if(l<=str[i+1]-'0')dp[i+1][nxj][nxk][l==str[i+1]-'0']+=dp[i][j][k][1];
					if(++nxj==sum)nxj=0;
					nxk++;
				}
			}
	return dp[n][0][sum][1]+dp[n][0][sum][0];
}
int main(){
	scanf("%s",str+1);
	int tmp=strlen(str+1);
	while(str[tmp]=='0')str[tmp--]='9';
	str[tmp]--;
	int ans=0;
	for(int i=1;i<=90;i++)ans-=cal(i);
	scanf("%s",str+1);
	for(int i=1;i<=90;i++)ans+=cal(i);
	printf("%d",ans);
	return 0;
}

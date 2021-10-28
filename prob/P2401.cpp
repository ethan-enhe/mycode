#include <bits/stdc++.h>
using namespace std;
const int P=2015,MXN=1005;
int n,k,dp[MXN][MXN];
int main(){
	scanf("%d%d",&n,&k);
	dp[1][0]=1;
	for(int i=1;i<n;i++)
		for(int j=0;j<=min(i-1,k);j++){
			dp[i+1][j]=(dp[i+1][j]+dp[i][j]*(1+j))%P;
			dp[i+1][j+1]=(dp[i+1][j+1]+dp[i][j]*(i-j))%P;
		}
	printf("%d",dp[n][k]);
	return 0;
}

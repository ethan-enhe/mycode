#include<bits/stdc++.h>
using namespace std;
const int MXP=35;
const int MXN=305;
int n,p,x[MXN],sx[MXN];
int dp[MXP][MXN],t[MXP][MXN];
inline int w(int l,int r){
	int mid=(l+r)>>1;
	return sx[r]+sx[l-1]-(sx[mid]<<1)+x[mid]*((mid<<1)-l-r+1);
}
int main(){
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++){
		scanf("%d",x+i);
		sx[i]=sx[i-1]+x[i];
		if(i<=p)t[i+1][i]=i-1;
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int j=1;j<=n;j++){
		t[p+1][j]=j-1;
		for(int i=min(j,p);i;i--)
			for(int k=t[i][j-1];k<=t[i+1][j];k++){
				if(dp[i][j]>dp[i-1][k]+w(k+1,j)){
					dp[i][j]=dp[i-1][k]+w(k+1,j);
					t[i][j]=k;
				}
			}
	}
	/*
	for(int i=1;i<=p+1;i++,putchar('\n'))
		for(int j=1;j<=n;j++)
			cerr<<t[i][j]<<" ";
			*/

	printf("%d",dp[p][n]);

	return 0;
}

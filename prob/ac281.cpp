#include<bits/stdc++.h>
using namespace std;
const int MXN=105;
const int MXM=1e5+5;
const int INF=1e9;
int n,m;
int dp[MXM],a[MXN];
int main(){
	while(scanf("%d%d",&n,&m)!=EOF){
		if(!n && !m)return 0;
		for(int i=1;i<=n;i++)scanf("%d",a+i);
		for(int i=1;i<=m;i++)dp[i]=INF;
		int tc=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)dp[j]=dp[j]<=tc?0:(j>=a[i]?dp[j-a[i]]+1:INF);
			scanf("%d",&tc);
		}
		int cnt=0;
		for(int i=1;i<=m;i++)cnt+=dp[i]<=tc;
		printf("%d\n",cnt);
	}
	return 0;
}

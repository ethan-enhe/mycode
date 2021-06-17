#include<bits/stdc++.h>
using namespace std;
//{{{ def
const int MXN=35;
const int MXM=2005;
int n,m,arr[MXN],dp[MXN][MXM];
//}}}
inline bool cmp(int x,int y){return x>y;}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",arr+i);
	sort(arr+1,arr+1+n,cmp);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=m;j++)
			dp[i][j]=min(dp[i-1][j],)





	
	return 0;
}

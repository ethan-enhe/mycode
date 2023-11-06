#include<bits/stdc++.h>
using namespace std;
//dp[i][j]=max(dp[i-1][j],1+dp[i-1][k](k<j,a[k]<a[i]))
//{{{ def
const int MXN=3005;
int n,ans,arr[MXN],brr[MXN],dp[MXN];
//}}}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",arr+i);
	for(int i=1;i<=n;i++)scanf("%d",brr+i);
	for(int i=1;i<=n;i++){
		for(int j=1,mx=0,tmp;j<=n;j++){
		    tmp=dp[j];
			if(brr[i]==arr[j])dp[j]=mx+1;
		    else if(brr[j]<arr[i])mx=max(mx,tmp);
		}
	    //for(int j=1;j<=n;j++)cout<<dp[j]<<" ";
	    //cout<<endl;
	}

	for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
	printf("%d",ans);
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
const int P=998244353;
const int MXN=20;
int n,arr[MXN],dp[1<<MXN];
inline bool chk(int x){
	if(x==(1<<n)-1)return 1;
	for(int i=0,last=-1;i<n;i++)
		if((x>>i)&1){
			if(arr[i]==last)return 0;
			last=arr[i];
		}
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",arr+i);
	dp[(1<<n)-1]=1;
	for(int i=(1<<n)-1;~i;i--)
		if(chk(i))
			for(int j=0;j<n;j++)
				if((i>>j)&1)
					dp[i^(1<<j)]=(dp[i^(1<<j)]+dp[i])%P;
	printf("%d",dp[0]);
	return 0;
}

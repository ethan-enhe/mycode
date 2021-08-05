#include<bits/stdc++.h>
using namespace std;
const int MXN=1e5+5;
int n,m,arr[MXN],t[MXN];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n+1;i++){
		if(i<=n)cin>>arr[i];
		else arr[i]=m;
		t[i]=t[i-1];
		if(i&1)t[i]+=arr[i]-arr[i-1];
	}
	int ans=t[n+1],tmp=0;
	for(int i=n;~i;i--){
		if((i&1)==0){
			ans=max(ans,t[i]+(arr[n+1]-arr[i+1]-tmp)+(arr[i+1]-arr[i]-1));
			tmp+=arr[i+1]-arr[i];
		}
		else
			ans=max(ans,t[i]+(arr[i+1]-arr[i]-1)+(arr[n+1]-arr[i+1]-tmp));
	}
	cout<<ans;
	return 0;
}

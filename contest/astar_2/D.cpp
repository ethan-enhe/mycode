#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const ll MXN=3e3+5;

ll n;
ll arr[MXN];
ll ans[MXN];
ll dfs(ll i){
	if(ans[i]==-1){
		ans[i]=1;
	}
	else if(ans[i]==0){
		ans[i]=-1;
		if(arr[i]==0)ans[i]=0;
		else ans[i]=dfs(arr[i]);
	}
	return ans[i];
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>arr[i];
	}
	ll res=0;
	for(ll i=1;i<=n;i++){
		if(dfs(i)==0)res^=i;
	}
	cout<<res;
	return 0;
}

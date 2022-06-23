#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const char nl='\n';
const ll MXN=105;
ll t,n,m,p[MXN],arr[MXN];
int main(){
	freopen("na.in","r",stdin);
	//freopen("na.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(ll i=1;i<=n;i++){
			ll x;
			cin>>x;
			p[x]=i;
		}
		for(ll i=1;i<=n;i++){
			ll x;
			cin>>x;
			arr[p[x]]=i;
		}
		for(ll i=1;i<=n;i++)
			cout<<arr[i];
		cout<<endl;
	}
	return 0;
}

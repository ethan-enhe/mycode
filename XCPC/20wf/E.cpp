#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll MXN=1e6+5;
ll n,m;
ll dd[MXN];
void md(ll x,ll v){
	dd[x]+=v;
	dd[x+1]-=v;
}
int main(){
	freopen("test.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	while(m--){
		char ch;
		ll l,r;
		cin>>ch>>l>>r;
		if(ch=='R'){
			md(l,1);
			md(r+1,-1);
		}
		else if(ch=='D'){
			md(l,-1);
			md(r+1,1);
		}
		else if(ch=='H'){
			ll mid=(l+r)>>1;
			++dd[l];
			if((l+r)&1){
				dd[mid+1]--;
				dd[mid+2]--;
			}
			else{
				dd[mid+1]-=2;
			}
			++dd[r+2];
		}
		else{
			ll mid=(l+r)>>1;
			--dd[l];
			if((l+r)&1){
				dd[mid+1]++;
				dd[mid+2]++;
			}
			else{
				dd[mid+1]+=2;
			}
			--dd[r+2];
		}
	}
	for(ll i=1;i<=n;i++){
		dd[i]+=dd[i-1];
		//cerr<<dd[i]<<" ";
	}
	for(ll i=1;i<=n;i++)dd[i]+=dd[i-1];
	for(ll i=1;i<=n;i++){
		cout<<dd[i]<<'\n';
	}
	return 0;
}

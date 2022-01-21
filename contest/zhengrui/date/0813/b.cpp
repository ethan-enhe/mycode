#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=2e5+5;
ll n,m,arr[MXN],cnt[MXN];
bool cmp(ll x,ll y){
	if(arr[y]<0)return arr[x]<arr[y];
	if(arr[x]<0)return 1;
	if(cnt[x]==cnt[y])return arr[x]<arr[y];
	if(cnt[x]+7<cnt[y])return 1;
	if(cnt[y]+7<cnt[x])return 0;


	if(cnt[x]>cnt[y]){
		ll tmp=1<<(cnt[x]-cnt[y]),vx=1,vy=(arr[y]+arr[x]-1)/arr[x];
		while(tmp--){
			if(vx>=vy)return 0;
			vx*=arr[x];
		}
		return 1;
	}
	else{
		ll tmp=1<<(cnt[y]-cnt[x]),vx=arr[x]/arr[y],vy=1;
		while(tmp--){
			if(vy>vx)return 1;
			vy*=arr[y];
		}
		return 0;
	}
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",arr+i);
	while(m--){
		ll op,a,b,c;
		scanf("%lld%lld%lld",&op,&a,&b);
		if(op==1){
			for(int i=a;i<=b;i++){
				if(arr[i]<0)arr[i]*=arr[i];
				else if(arr[i]!=0 && arr[i]!=1)cnt[i]++;
			}
		}
		else{
			ll ans=0;
			scanf("%lld",&c);
			for(int i=a;i<=b;i++)
				ans+=cmp(i,c);
			printf("%lld\n",ans);
		}
	}
	return 0;
}

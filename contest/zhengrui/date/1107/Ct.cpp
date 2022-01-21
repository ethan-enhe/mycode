#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=5e5+5,INF=1e16;
struct tri{
	ll x,y,z;
	inline bool valid()const{return x>=0 && y>=0 && z>=0;}
	inline tri cal(ll va)const{
		if(va<0)return {-1,-1,-1};
		tri res=*this;
		ll delt=min(res.z,va/4);
		res.z-=delt,va-=4*delt;

		delt=min(res.y,va/2);
		res.y-=delt,va-=2*delt;
		res.x-=va;
		return res;
	}
	inline bool operator < (const tri &b)const{
		if(!valid())return 1;
		if(!b.valid())return 0;
		if(x==b.x){
			if(y==b.y)return z<b.z;
			return y<b.y;
		}
		return x<b.x;
	}
	inline void prt(){
		printf("1:%lld 2:%lld 4:%lld\n",x,y,z);
	}
}dp[2][MXN];
ll t,n,a,b,c,d,e;
ll arr[MXN];
int main(){
	freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d,&e);
		for(ll i=1;i<=n;i++){
			scanf("%lld",arr+i);
			ll delt=min(arr[i]/20,e);
			e-=delt;
			arr[i]-=delt*20;

			delt=min(arr[i]/20,d/2);
			d-=delt*2;
			arr[i]-=delt*20;
		}
		for(ll i=0;i<=d;i++)
			dp[0][i]={-1,-1,-1};
		dp[0][0]={a,b,c};
		for(int i=0;i<n;i++){
			bool f=i&1;
			for(ll j=0;j<=d;j++)
				dp[!f][j]={-1,-1,-1};
			for(ll j=0;j<=d;j++)
				if(dp[f][j].valid()){
					dp[!f][j]=max(dp[!f][j],dp[f][j].cal(arr[i+1]));
					dp[!f][j+1]=max(dp[!f][j+1],dp[f][j].cal(arr[i+1]-10));
				}
			//for(int j=0;j<=d;j++){
			//	cout<<i+1<<","<<j<<"---- ";
			//	dp[!f][j].prt();
			//}

		}
		bool f=0;
		for(int i=0;i<=d;i++)
			if(dp[n&1][i].valid()){
				f=1;
				break;
			}
		puts(f?"YES":"NO");

	}
	return 0;
}

/*
6 4 5 3 4 4
31 26 56 13 3 37
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=5e5+5,NR=MXN*20,INF=1e16,LIM=1e10;
ll cnt=0;
//{{{struct
struct ele{
	ll x,y,z,w;
	inline bool valid()const{return x>=0;}
	inline ele cal(ll va)const{
		ele res=*this;
		ll delt=min(res.w,va/20);
		res.w-=delt,va-=20*delt;

		delt=min(res.z,va/4);
		res.z-=delt,va-=4*delt;

		delt=min(res.y,va/2);
		res.y-=delt,va-=2*delt;

		res.x-=va;
		return res;
	}
	inline bool operator < (const ele &b)const{
		if(!valid())return 1;
		if(!b.valid())return 0;
		if(x==b.x){
			if(y==b.y){
				if(z==b.z)return w<b.w;
				return z<b.z;
			}
			return y<b.y;
		}
		return x<b.x;
	}
	inline void prt(){
		printf("1:%lld 2:%lld 4:%lld 20:%lld\n",x,y,z,w);
	}
}dp[2][NR];
//}}}
ll t,n,a,b,c,d,e;
ll arr[MXN];
int main(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d,&e);
		for(ll i=1;i<=n;i++){
			scanf("%lld",arr+i);
			arr[i]-=LIM;
			ll delt=max(0ll,min(arr[i]/20,e));
			e-=delt;
			arr[i]-=delt*20;

			delt=max(0ll,min(arr[i]/20,d/2));
			d-=delt*2;
			arr[i]-=delt*20;
			arr[i]+=LIM;
		}
		dp[0][0]={a,b,c,e};
		ll curj=0,nxj;
		for(int i=0;i<n;i++){
			bool f=i&1;
			nxj=min(d,curj+arr[i+1]/10);
			for(int j=0;j<=nxj;j++)
				dp[!f][j]={-1,-1,-1,-1};
			for(int j=0;j<=curj;j++)
				if(dp[f][j].valid()){
					for(int k=0;k*10<=arr[i+1];k++)
					dp[!f][j+k]=max(dp[!f][j+k],dp[f][j].cal(arr[i+1]-k*10));
					cnt++;
				}
			curj=nxj;
			//for(int j=0;j<=nxj;j++){
			//	cerr<<i+1<<" "<<j<<" ";
			//	dp[!f][j].prt();
			//}
		}
		bool f=0;
		for(int i=0;i<=curj;i++)
			if(dp[n&1][i].valid()){
				f=1;
				break;
			}
		puts(f?"YES":"NO");
	}
		cerr<<cnt;
	return 0;
}

/*
6 4 5 3 4 4
31 26 56 13 3 37
*/

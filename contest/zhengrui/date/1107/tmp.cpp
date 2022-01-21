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
	for(int i=0;i<=20;i++)
		for(int j=0;j<=10;j++)
			for(int k=0;k<=5;k++)
				for(int l=0;l<=2;l++)
				if(i+2*j+4*k+10*l>=20){
					bool f=0;
					for(int x=0;x<=i;x++)
						for(int y=0;y<=j;y++)
							for(int z=0;z<=k;z++)
							for(int w=0;w<=l;w++)
								if(x+y*2+z*4+w*10==20)f=1;
					if(!f){
						cout<<i<<" "<<j<<" "<<k<<" "<<l<<endl;

					}
				}
	return 0;
}

/*
6 4 5 3 4 4
31 26 56 13 3 37
*/


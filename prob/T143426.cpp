#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll SZ=4;
ll q,x,l,r,n,m,y;
struct mat{
	ll arr[SZ][SZ];
	inline mat(bool x=0){
		memset(arr,0,sizeof(arr));
		if(x)for(ll i=0;i<SZ;i++)arr[i][i]=1;
	}
	inline mat operator * (const mat &b)const{
		mat res;
		for(ll i=0;i<SZ;i++)
			for(ll j=0;j<SZ;j++)
				for(ll k=0;k<SZ;k++)
					res.arr[i][j]=(res.arr[i][j]+arr[i][k]*b.arr[k][j])%m;
		return res;
	}
}m0,t,tmp;
mat qpow(mat v,ll y){
	mat res(1);
	while(y){
		if(y&1)res=res*v;
		y>>=1,v=v*v;
	}
	return res;
}
pair<ll,ll> exgcd(ll x,ll y){
	if(y==0)return make_pair(1,0);
	pair<ll,ll> tmp=exgcd(y,x%y);
	return make_pair(tmp.second,tmp.first-x/y*tmp.second);
}
int main(){
	m0.arr[0][0]=m0.arr[0][3]=1;
	t.arr[2][0]=1,t.arr[3][1]=1;
	t.arr[0][2]=1,t.arr[2][2]=1;
	t.arr[1][3]=1,t.arr[3][3]=1;

	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld%lld%lld%lld%lld",&x,&l,&r,&n,&m,&y);
		tmp=m0*qpow(t,n-2);
		y=(y-x%m*tmp.arr[0][2])%m;
		pair<ll,ll> ty=exgcd(tmp.arr[0][3],m);ll g=ty.first*tmp.arr[0][3]+ty.second*m;
		if(y%g)puts("0");
		else{
			m/=g,ty.first=y/g*ty.first%m;
			printf("%lld\n",ll(floor((long double)(r-ty.first)/m)-floor((long double)(l-ty.first-1)/m)));
		}
	}
	return 0;
}

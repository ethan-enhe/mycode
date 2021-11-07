#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll SZ=20,P=1e9+7;
ll n,m;
struct mat{
	ll arr[SZ][SZ];
	inline mat(bool f=0){
		memset(arr,0,sizeof(arr));
		for(ll i=0;i<m;i++)
			arr[i][i]=f;
	}
	inline mat operator * (const mat &b)const{
		mat res;
		for(ll i=0;i<m;i++)
			for(ll j=0;j<m;j++)
				for(ll k=0;k<m;k++)
					res.arr[i][j]=(res.arr[i][j]+arr[i][k]*b.arr[k][j])%P;
		return res;
	}
	inline void prt(){
		for(ll i=0;i<m;i++,cout<<endl)
			for(ll j=0;j<m;j++)
				cout<<arr[i][j]<<" ";
	}
}ans;
template<class T>
T qpow(T x,ll y){
	T r(1);
	while(y){
		if(y&1)r=r*x;
		x=x*x,y>>=1;
	}
	return r;
}
int main(){
	ans.arr[0][0]=1;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		ll a,b;
		scanf("%lld%lld",&a,&b);
		mat trans(1);
		for(int j=0;j<m;j++)
			trans.arr[j][(j+b)%m]++;
		ans=ans*qpow(trans,a);
	}
	printf("%lld",(ans.arr[0][0]+P-1)%P);

	return 0;
}

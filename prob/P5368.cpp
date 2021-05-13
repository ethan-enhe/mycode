#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1e5+5;
const ll P=998244353;
ll n,m,arr[MXN],ord[MXN];
ll fac[MXN],inv[MXN];
inline ll qpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%P;
		x=x*x%P;
		y>>=1;
	}
	return res;
}
inline ll c(ll x,ll y){
	if(y>x || y<0)return 0;
	return fac[x]*inv[x-y]%P*inv[y]%P;
}
inline ll bel(ll x){return upper_bound(ord+1,ord+1+n,x)-ord-1;}
int main(){
	freopen("test.in","r",stdin);
	scanf("%lld%lld",&n,&m);
	fac[0]=1;
	for(ll i=1;i<=n;i++){
		scanf("%lld",arr+i);
		ord[i]=arr[i];
		fac[i]=fac[i-1]*i%P;
	}
	inv[n]=qpow(fac[n],P-2);
	for(ll i=n;~i;i--)inv[i-1]=inv[i]*i%P;
	sort(ord+1,ord+1+n);
	for(ll i=1;i<=n;i++){
		ll t1=bel(arr[i]-1),t2=bel((arr[i]<<1)-1);
		ll cnt=bel((arr[i]-1)>>1)+n-t1-1;
		ll dbcnt=bel(arr[i]-1)+n-t2;
		printf("%lld\n",(c(cnt,m)+(arr[i]?c(dbcnt,m-t2+t1):c(cnt,m-1)))%P);
	}
	return 0;
}

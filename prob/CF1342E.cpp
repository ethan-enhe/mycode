#include<bits/stdc++.h>
using namespace std;

char buf[1<<20],*p1=buf,*p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
template<class T>
inline void read(T &x) {
	static bool f=0;static char c;x=0;
	while(c=gc(),c<'0' || c>'9')if(c=='-')f=1;
	while(c>='0' && c<='9')x=(x<<3)+(x<<1)+(c^48),c=gc();
	if(f)x=-x;
}

typedef long long ll;
const ll P=998244353;
const ll MXN=200005;
ll n,k,ans;
ll fac[MXN],ifac[MXN];
inline ll qpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%P;
		x=x*x%P;
		y>>=1;
	}
	return res;
}
inline ll c(ll x,ll y){return (y>=x && x>=0)?fac[y]*ifac[y-x]%P*ifac[x]%P:0;}
int main(){
	read(n),read(k);k=n-k;
	if(k<=0)return printf("0"),0;
	fac[0]=1;
	for(ll i=1;i<=n;i++)fac[i]=fac[i-1]*i%P;
	ifac[n]=qpow(fac[n],P-2);
	for(ll i=n;i;i--)ifac[i-1]=ifac[i]*i%P;
	for(ll i=k;i;i--){
		if((i-k)&1)ans=(ans-c(i,k)*qpow(i,n))%P;
		else ans=(ans+c(i,k)*qpow(i,n))%P;
	}
	ans=(ans+P)%P;
	if(k<n)ans=2*ans*c(k,n)%P;
	printf("%lld",ans);

	return 0;
}

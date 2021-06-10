#include<bits/stdc++.h>
using namespace std;

#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char buf[1<<20],*p1=buf,*p2=buf;
template<class T>
inline void read(T &x){
	bool f=0;x=0;char c;
	while(c=gc(),c<'0' || c>'9')if(c=='-')f=1;
	while(c>='0' && c<='9')x=(x<<3)+(x<<1)+(c^48),c=gc();
	if(f)x=-x;
}

typedef long long ll;
const ll MXPRI=1e5+5;
bool iscom[MXPRI];ll pri[MXPRI],pcnt;

const ll MXPFAC=20;
ll t,l,r,x;
ll pfac[MXPFAC],va[1<<MXPFAC],facc;
inline ll cal(ll l,ll r,ll x){
	ll mxi=sqrt(x)+1;facc=0;
	for(ll j=1,i;pri[j]<=mxi;j++){
		i=pri[j];
		if((x%i)==0){
			x/=i;while((x%i)==0)x/=i;
			pfac[facc++]=i;
		}
	}
	if(x!=1)pfac[facc++]=x;

	ll full=1ll<<facc,res=r-l+1;
	for(ll i=1;i!=full;i++){
		ll lbt=i&(-i);
		va[i]=va[i^lbt]*pfac[(ll)log2(lbt)];
		if(__builtin_popcount(i)&1)res+=(l-1)/va[i]-r/va[i];
		else res+=r/va[i]-(l-1)/va[i];
	}
	return res;
}

int main(){
	
	for(ll i=2;i<MXPRI;i++)
		if(!iscom[i]){
			pri[++pcnt]=i;
			for(ll j=i*i;j<MXPRI;j+=i)
				iscom[j]=1;
		}
	va[0]=1;
	read(t);
	while(t--){
		read(l),read(r),read(x);
		printf("%lld\n",cal(l,r,x));
	}
	return 0;
}

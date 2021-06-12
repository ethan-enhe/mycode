#include<bits/stdc++.h>
using namespace std;

const int BS=1<<20;
char ibuf[BS],*ip1=ibuf,*ip2=ibuf;
char obuf[BS],*op=obuf;
#define gc() (ip1==ip2 && (ip2=(ip1=ibuf)+fread(ibuf,1,BS,stdin),ip1==ip2)?EOF:*ip1++)
#define flsh() (fwrite(obuf,1,op-obuf,stdout),op=obuf)
#define pc(x) (*op++=(x),op==obuf+BS && flsh())
#define isdig(x) ((x)>='0' && (x)<='9')
#define isemp(x) ((x)==' ' || (x)=='\n' || (x)=='\r' || (x)=='\t')
struct flusher{inline ~flusher(){flsh();}}tmp;

template<class T>
inline void read(T &x){
	bool f=0;x=0;char c;
	while(c=gc(),!isdig(c))if(c=='-')f=1;
	while(isdig(c))x=(x<<3)+(x<<1)+(c^48),c=gc();
	if(f)x=-x;
}
inline void read(char *x){
	while(*x=gc(),isemp(*x))if(*x==EOF)return;
	while(*++x=gc(),!isemp(*x) && *x!=EOF);
	*x=0;
}
template<class T>
inline void prt(T x){
	if(x<0)pc('-'),x=-x;
	if(x>9)prt(x/10);
	pc(x%10^48);
}
inline void prt(char *x){while(*x)pc(*x++);}




typedef long long ll;
typedef long long 
const ll P=1e9+7;
const ll MXN=5e4+5;
const ll MXK=205;
ll t,n,a,b;
ll fac[MXN],ifac[MXN],s[MXK];
ll head

inline ll qpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%P;
		x=x*x%P;
		y>>=1;
	}
	return res;
}
inline ll c(ll x,ll y){return (y>x||y<0)?0:fac[x]*ifac[x-y]%P*ifac[y]%P;}
int main(){
	fac[0]=1;
	for(ll i=1;i<MXN;i++)fac[i]=fac[i-1]*i%P;
	ifac[MXN-1]=qpow(ifac[MXN-1],P-2);
	for(ll i=MXN-1;i;i--)fac[i-1]=fac[i]*i%P;
	read(t);
	for(ll i=1;i<=t;i++){
	}



	for(ll i=1;i<MXN;i++)
		for(ll j=1;j<MXK;j++)
			s[i][j]=s[i-1][j-1]+s[i-1][j]*j;



	
	return 0;
}

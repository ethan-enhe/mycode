#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=2.1e6+5;
const ll P=998244353;
const ll MXLG=30;
ll trt[MXLG<<1],*rt=trt+MXLG;
inline ll fix(ll x){return x<0?x+P:x;}
inline ll qpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%P;
		y>>=1,x=x*x%P;
	}
	return res;
}
inline void init(){
	ll tmp=P-1,tcnt=0;
	while(!(tmp&1))tmp>>=1,tcnt++;
	rt[tcnt]=qpow(3,tmp);
	rt[-tcnt]=qpow(rt[tcnt],P-2);
	while(--tcnt){
		rt[tcnt]=rt[tcnt+1]*rt[tcnt+1]%P;
		rt[-tcnt]=rt[-tcnt-1]*rt[-tcnt-1]%P;
	}
}
inline void ntt(ll *f,ll len,ll tp){
	if(len==1)return;
	ll tf[2][len>>1],cw=1,w0=rt[tp*(ll)log2(len)];
	for(int i=0;i<len;i++)tf[i&1][i>>1]=f[i];
	ntt(tf[0],len>>1,tp);
	ntt(tf[1],len>>1,tp);
	for(int i=0;i<len>>1;i++,cw=cw*w0%P){
		f[i]			=(tf[0][i]+tf[1][i]*cw)%P;
		f[i+(len>>1)]	=(tf[0][i]-tf[1][i]*cw)%P;
	}
}
ll n,m,arr[MXN],brr[MXN];
int main(){
	init();
	scanf("%lld%lld",&n,&m);n++,m++;
	for(int i=0;i<n;i++)scanf("%lld",arr+i);
	for(int i=0;i<m;i++)scanf("%lld",brr+i);
	ll tlen=1<<int(log2(n+m-1)+1);
	ntt(arr,tlen,1);
	ntt(brr,tlen,1);
	for(int i=0;i<tlen;i++)arr[i]=arr[i]*brr[i]%P;
	ntt(arr,tlen,-1);
	ll tmp=qpow(tlen,P-2);
	for(int i=0;i<n+m-1;i++)
		printf("%lld ",fix(arr[i]*tmp%P));
	return 0;
}

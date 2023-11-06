#include<bits/stdc++.h>
#define gc() (bl==br && (br=(bl=buf)+fread(buf,1,1<<20,stdin),bl==br)?EOF:*bl++)
using namespace std;
typedef long long ll;

char buf[1<<20],*bl=buf,*br=buf;
template<class T>
inline void read(T &x){
	T f=1;x=0;char c;
	while(c=gc(),c<'0' || c>'9')if(c=='-')f=-1;
	while(c>='0' && c<='9')x=(x<<3)+(x<<1)+(c^48),c=gc();
	x*=f;
}

const ll MXN=5e4+5;

struct que{ll op,l,r,va;}q[MXN],tmp1[MXN],tmp2[MXN];
ll n,m,cnt,pool[MXN],ans[MXN];

struct tarr{
	ll d[MXN];
	inline tarr(){memset(d,0,sizeof(d));}
	inline void mod(ll x,ll v){for(;x<=n;x+=x&(-x))d[x]+=v;}
	inline void reset(ll x){for(;x<=n;x+=x&(-x))d[x]=0;}
	inline ll sum(ll x){ll r=0;for(;x;x^=x&(-x))r+=d[x];return r;}
}diff,diffi;
inline void mod(ll l,ll r,ll v){
	diff.mod(l,v),diff.mod(r+1,-v);
	diffi.mod(l,v*l),diffi.mod(r+1,-v*(r+1));
}
inline void reset(ll l,ll r){
	diff.reset(l),diff.reset(r+1);
	diffi.reset(l),diffi.reset(r+1);
}
inline ll sum(ll l,ll r){return diff.sum(r)*(r+1)+diffi.sum(l-1)-diff.sum(l-1)*l-diffi.sum(r);}

inline void cal(ll l,ll r,ll ql,ll qr){
	if(ql>qr)return;
	if(l==r){
		for(ll i=ql;i<=qr;i++)ans[q[i].op]=l;
		return;
	}
	ll mid=(l+r)>>1,top1=0,top2=0;
	for(ll i=ql,tmp;i<=qr;i++){
		if(q[i].op)(tmp=sum(q[i].l,q[i].r))<q[i].va?(q[i].va-=tmp,tmp2[++top2]=q[i]):tmp1[++top1]=q[i];
		else{
			if(q[i].va<=mid)mod(q[i].l,q[i].r,1),tmp1[++top1]=q[i];
			else tmp2[++top2]=q[i];
		}
	}
	for(ll i=ql;i<=qr;i++)if(!q[i].op && q[i].va<=mid)reset(q[i].l,q[i].r);
	for(ll i=1;i<=top1;i++)q[ql+i-1]=tmp1[i];
	for(ll i=1;i<=top2;i++)q[ql+top1+i-1]=tmp2[i];
	cal(l,mid,ql,ql+top1-1),cal(mid+1,r,ql+top1,qr);
}


int main(){
	memset(ans,-1,sizeof(ans));
	read(n),read(m);
	for(ll i=1;i<=m;i++){
		read(q[i].op),read(q[i].l),read(q[i].r),read(q[i].va)
		if(q[i].op==1){
			q[i].op=0;
			q[i].va=-q[i].va;
			pool[++cnt]=q[i].va;
		}
		else q[i].op=i;
	}
	sort(pool+1,pool+1+cnt);
	for(ll i=1;i<=m;i++)
		if(!q[i].op)
			q[i].va=lower_bound(pool+1,pool+1+cnt,q[i].va)-pool;
	cal(1,cnt,1,m);
	for(ll i=1;i<=m;i++)if(~ans[i])printf("%lld\n",-pool[ans[i]]);
	return 0;
}

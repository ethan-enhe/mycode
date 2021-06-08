#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define gc() (bs==bt && (bt=(bs=buf)+fread(buf,1,1<<20,stdin),bs==bt)?EOF:*bs++)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;

char buf[1<<20],*bs=buf,*bt=buf;
inline ll read(){
	ll tp=1,r=0;char c=gc();
	for(;c<'0' || c>'9';c=gc())if(c=='-')tp=-1;
	for(;c>='0' && c<='9';c=gc())r=r*10+c-'0';
	return r*tp;
}


const ll MXN=3e5+5;
struct que{ll l,r,a;}arr[MXN];
pi q[MXN],tmp1[MXN],tmp2[MXN];
ll n,m,k,ans[MXN];
vector<ll> pos[MXN];

ll dat[MXN];
inline void mod(ll x,ll d){for(;x<=m;x+=(-x)&x)dat[x]+=d;}
inline ll sum(ll x){ll res=0;for(;x;x^=(-x)&x)res+=dat[x];return res;}

inline void modcicle(ll l,ll r,ll a){
	if(l<=r)mod(l,a),mod(r+1,-a);
	else mod(l,a),mod(m+1,-a),mod(1,a),mod(r+1,-a);
}
inline void cal(ll l,ll r,ll ql,ll qr){
	if(ql>qr)return;
	if(l==r){
		for(ll i=ql;i<=qr;i++)ans[q[i].fi]=l;
		return;
	}
	ll mid=(l+r)>>1,top1=0,top2=0;
	for(ll i=l;i<=mid;i++)modcicle(arr[i].l,arr[i].r,arr[i].a);
	for(ll i=ql;i<=qr;i++){
		ll delt=0;
		for(ll j:pos[q[i].fi])if((delt+=sum(j))>=q[i].se)break;
		delt<q[i].se?(q[i].se-=delt,tmp2[++top2]=q[i]):tmp1[++top1]=q[i];
	}
	for(ll i=l;i<=mid;i++)modcicle(arr[i].l,arr[i].r,-arr[i].a);
	for(ll i=1;i<=top1;i++)q[ql+i-1]=tmp1[i];
	for(ll i=1;i<=top2;i++)q[ql+top1+i-1]=tmp2[i];
	cal(l,mid,ql,ql+top1-1),cal(mid+1,r,ql+top1,qr);
}


int main(){
	n=read(),m=read();
	for(ll i=1;i<=m;i++)pos[read()].pb(i);
	for(ll i=1;i<=n;i++)q[i]=mp(i,read());
	k=read();
	for(ll i=1,tl,tr,ta;i<=k;i++){
		tl=read(),tr=read(),ta=read();
		arr[i]=que{tl,tr,ta};
	}
	cal(1,k+1,1,n);
	for(ll i=1;i<=n;i++)ans[i]>k?printf("NIE\n"):printf("%lld\n",ans[i]);
	return 0;
}

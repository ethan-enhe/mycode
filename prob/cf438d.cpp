#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MXN=1e5+5;

#define ls (p<<1)
#define rs (p<<1|1)

ll n,m,arr[MXN];


const ll NR=MXN<<2;
struct node{
	ll su,mx;
    inline node(ll su=0,ll mx=0):su(su),mx(mx){}
    node operator + (const node &y)const{return node(su+y.su,max(mx,y.mx));}
}t[NR];
#define pushu t[p]=t[ls]+t[rs]
inline void build(ll p,ll l,ll r){
	if(l==r){
		t[p]=node(arr[l],arr[l]);
		return;
	}
	ll mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushu;
}
inline void chg(ll p,ll l,ll r,ll mi,ll mx){
	if(l==r){
		t[p]=node(mx,mx);
		return;
	}
	ll mid=(l+r)>>1;
	if(mi<=mid)chg(ls,l,mid,mi,mx);
	else chg(rs,mid+1,r,mi,mx);
	pushu;
}
inline void mod(ll p,ll l,ll r,ll ml,ll mr,ll md){
	if(l==r){
        ll tmp=t[p].su%md;
        t[p]=node(tmp,tmp);
		return;
	}
	ll mid=(l+r)>>1;
	if(ml<=mid && t[ls].mx>=md)mod(ls,l,mid,ml,mr,md);
	if(mr>mid && t[rs].mx>=md)mod(rs,mid+1,r,ml,mr,md);
	pushu;
}
inline node que(ll p,ll l,ll r,ll ql,ll qr){
	if(ql<=l && r<=qr)return t[p];
	ll mid=(l+r)>>1;node res;
	if(ql<=mid)res=res+que(ls,l,mid,ql,qr);
	if(qr>mid)res=res+que(rs,mid+1,r,ql,qr);
	return res;
}

int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",arr+i);
    build(1,1,n);
	while(m--){
		ll op,a,b,c;
		scanf("%lld%lld%lld",&op,&a,&b);
		if(op==1)printf("%lld\n",que(1,1,n,a,b).su);
		else if(op==2){
			scanf("%lld",&c);
			mod(1,1,n,a,b,c);
		}
		else chg(1,1,n,a,b);
	}
	return 0;
}

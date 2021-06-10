//线段树1
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MXN=1e5+5;

#define ls (p<<1)
#define rs (p<<1|1)

const ll NR=MXN<<2;
struct node{
	ll va,tag;
	inline node(ll va=0,ll tag=0):va(va),tag(tag){}
	inline void addt(ll l,ll r,ll k){
		tag+=k;
		va+=(r-l+1)*k;
	}
	inline node operator + (const node &y)const{return node(va+y.va);}
}t[NR];
inline void pushu(ll p){t[p]=t[ls]+t[rs];}
inline void pushd(ll p,ll l,ll r){
	ll mid=(l+r)>>1;
	t[ls].addt(l,mid,t[p].tag);
	t[rs].addt(mid+1,r,t[p].tag);
	t[p]=node(t[p].va);
}
inline void build(ll p,ll l,ll r){
	if(l==r){
		t[p]=node();
		return;
	}
	ll mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushu(p);
}
inline void mod(ll p,ll l,ll r,ll ml,ll mr,ll mx){
	if(ml<=l && r<=mr){
		t[p].addt(l,r,mx);
		return;
	}
	ll mid=(l+r)>>1;
	pushd(p,l,r);
	if(ml<=mid)mod(ls,l,mid,ml,mr,mx);
	if(mr>mid)mod(rs,mid+1,r,ml,mr,mx);
	pushu(p);
}
inline node que(ll p,ll l,ll r,ll ql,ll qr){
	if(ql<=l && r<=qr)return t[p];
	ll mid=(l+r)>>1;node res;
	pushd(p,l,r);
	if(ql<=mid)res=res+que(ls,l,mid,ql,qr);
	if(qr>mid)res=res+que(rs,mid+1,r,ql,qr);
	return res;
}

ll n,m;
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		ll tmp;
		scanf("%lld",&tmp);
		mod(1,1,n,i,i,tmp);
	}
	while(m--){
		ll op,x,y,z;
		scanf("%lld%lld%lld",&op,&x,&y);
		if(op==1){
			scanf("%lld",&z);
			mod(1,1,n,x,y,z);
		}
		else printf("%lld\n",que(1,1,n,x,y).va);
	}
	return 0;
}

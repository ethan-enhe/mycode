#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1e4+5;
const ll INF=3e9;
ll n,w,h;

namespace segt{
	ll nodec,rt;
	struct node{ll mx,tag,ls,rs;}t[MXN*200];
	inline ll nnode(){
		++nodec;
		t[nodec].mx=t[nodec].tag=t[nodec].ls=t[nodec].rs=0;
		return nodec;
	}
	inline void clear(){nodec=rt=0;}
	inline void addt(ll &p,ll va){
		if(!p)p=nnode();
		t[p].tag+=va;
		t[p].mx+=va;
	}
	inline void pushd(ll p){
		if(t[p].tag){
			addt(t[p].ls,t[p].tag);
			addt(t[p].rs,t[p].tag);
			t[p].tag=0;
		}
	}
	inline void pushu(ll p){t[p].mx=max(t[t[p].ls].mx,t[t[p].rs].mx);}
	void mod(ll &p,ll l,ll r,ll ml,ll mr,ll mx){
		if(!p)p=nnode();
		if(ml<=l && r<=mr){
			addt(p,mx);
			return;
		}
		ll mid=(l+r)>>1;
		pushd(p);
		if(ml<=mid)mod(t[p].ls,l,mid,ml,mr,mx);
		if(mr>mid)mod(t[p].rs,mid+1,r,ml,mr,mx);
		pushu(p);
	}
}
using segt::clear;
using segt::mod;
using segt::rt;
using segt::t;


struct seg{
	ll x,yl,yu,tp;
	inline seg(ll x=0,ll yl=0,ll yu=0,ll tp=0):x(x),yl(yl),yu(yu),tp(tp){}
	inline bool operator < (const seg &b)const{return x<b.x;}
}arr[MXN<<1];

int main(){
	ll tq;
	scanf("%lld",&tq);
	while(tq--){
		clear();
		scanf("%lld%lld%lld",&n,&w,&h);
		for(int i=1;i<=n;i++){
			ll x,y,l;
			scanf("%lld%lld%lld",&x,&y,&l);
			arr[i]=seg(x-w,y+1,y+h,l);
			arr[i+n]=seg(x,y+1,y+h,-l);
		}
		ll res=0;
		sort(arr+1,arr+1+(n<<1));
		for(int i=1;i<=n<<1;i++){
			mod(rt,-INF,INF,arr[i].yl,arr[i].yu,arr[i].tp);
			if(i==(n<<1) || arr[i+1].x!=arr[i].x)res=max(res,t[rt].mx);
		}
		printf("%lld\n",res);
	}
	return 0;
}

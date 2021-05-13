//P3377
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const ll MXN=1e5+5;
const ll INF=2e9+5;

namespace segt{
	struct node{
		ll cnt,ls,rs;
		node(){cnt=ls=rs=0;}
	}t[MXN*50];
	ll nodec,rt[MXN];
	inline void push_up(ll p){t[p].cnt=t[t[p].ls].cnt+t[t[p].rs].cnt;}
	inline void mod(ll &p,ll l,ll r,ll mi,ll mx){
		if(!p)p=++nodec;
		if(l==r){
			t[p].cnt+=mx;
			return;
		}
		ll mid=(l+r)>>1;
		if(mi<=mid)mod(t[p].ls,l,mid,mi,mx);
		else mod(t[p].rs,mid+1,r,mi,mx);
		push_up(p);
	}
	inline ll merge(ll pl,ll pr){
		if(!pl || !pr)return pl|pr;
		t[pl].cnt+=t[pr].cnt;
		t[pl].ls=merge(t[pl].ls,t[pr].ls);
		t[pl].rs=merge(t[pl].rs,t[pr].rs);
		return pl;
	}
	inline ll getmin(ll p,ll l,ll r){
		if(!t[p].cnt)return -1;
		if(l==r)return l;
		ll mid=(l+r)>>1;
		if(t[t[p].ls].cnt)return getmin(t[p].ls,l,mid);
		else return getmin(t[p].rs,mid+1,r);
	}
}

namespace dsu{
	ll fa[MXN];
	inline ll find(ll x){return x==fa[x]?x:fa[x]=find(fa[x]);}
	inline void merge(ll x,ll y){fa[find(y)]=find(x);}
}
ll n,m;
int main(){
	freopen("test.in","r",stdin);
	scanf("%lld%lld",&n,&m);
	for(ll i=1,tmp;i<=n;i++){
		dsu::fa[i]=i;
		scanf("%lld",&tmp);
		segt::mod(segt::rt[i],-INF,INF,tmp,1);
	}
	while(m--){
		ll a,b,c;
		scanf("%lld%lld",&a,&b);
		if(a==1){
			scanf("%lld",&c);
			segt::merge(segt::rt[dsu::find(b)],segt::rt[dsu::find(c)]);
			dsu::merge(b,c);
		}
		else{
			ll res=segt::getmin(segt::rt[dsu::find(b)],-INF,INF);
			printf("%lld\n",res);
			if(res!=-1)segt::mod(segt::rt[dsu::find(b)],-INF,INF,res,-1);
		}
	}

	return 0;
}

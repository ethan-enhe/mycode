#include<bits/stdc++.h>
#define sq(x) ((x)*(x))
using namespace std;
typedef long long ll;
const ll INF=1e18,MXN=500+5,MXSZ=MXN*MXN;
ll n;
char str[MXN];

struct p{ll x,y;}arr[MXSZ];
struct node{ll l,r,u,d,ls,rs;}t[MXSZ];
inline ll dis(p x,p y){return sq(x.x-y.x)+sq(x.y-y.y);}


inline bool cmpx(p x,p y){return x.x<y.x;}
inline bool cmpy(p x,p y){return x.y<y.y;}
inline void upd(ll x,ll y){
	t[x].l=min(t[x].l,t[y].l);
	t[x].r=max(t[x].r,t[y].r);
	t[x].u=min(t[x].u,t[y].u);
	t[x].d=max(t[x].d,t[y].d);
}
inline void pushu(ll p){
	t[p].l=t[p].r=arr[p].y,t[p].u=t[p].d=arr[p].x;
	if(t[p].ls)upd(p,t[p].ls);
	if(t[p].rs)upd(p,t[p].rs);
}
inline ll build(ll l,ll r){
	if(l>r)return 0;
	ll mid=(l+r)>>1;
	double avx=0,avy=0,vax=0,vay=0;

	for(ll i=l;i<=r;i++)avx+=arr[i].x,avy+=arr[i].y;
	avx/=(r-l+1),avy/=(r-l+1);
	for(ll i=l;i<=r;i++)vax+=sq(avx-arr[i].x),vay+=sq(avy-arr[i].y);

	if(vax>=vay)nth_element(arr+l,arr+mid,arr+r+1,cmpx);
	else nth_element(arr+l,arr+mid,arr+r+1,cmpy);
	t[mid].ls=build(l,mid-1),t[mid].rs=build(mid+1,r);
	pushu(mid);
	return mid;
}
inline ll mndis(ll x,ll y){
	ll res=0;
	if(t[y].l>arr[x].y)res+=sq(t[y].l-arr[x].y);
	if(t[y].r<arr[x].y)res+=sq(t[y].r-arr[x].y);
	if(t[y].u>arr[x].x)res+=sq(t[y].u-arr[x].x);
	if(t[y].d<arr[x].x)res+=sq(t[y].d-arr[x].x);
	return res;
}
ll res=INF;
inline void que(ll l,ll r,ll qi){
	if(l>r)return;
	ll mid=(l+r)>>1;
	if(mid!=qi)res=min(res,dis(arr[qi],arr[mid]));
	if(t[mid].ls && mndis(qi,t[mid].ls)<res)que(l,mid-1,qi);
	if(t[mid].rs && mndis(qi,t[mid].rs)<res)que(mid+1,r,qi);
}

int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
		scanf("%lld%lld",&arr[i].x,&arr[i].y);

	build(1,n);
	for(ll i=1;i<=n;i++)
		que(1,n,i);
	printf("%.4f",sqrt(res));
	return 0;
}

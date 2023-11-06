#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1e5+5;
ll n,pool[MXN<<1],unq,res;
struct seg{
	ll x,ylow,yup,tp;
	inline seg(ll x=0,ll ylow=0,ll yup=0,ll tp=0):x(x),ylow(ylow),yup(yup),tp(tp){}
	inline bool operator < (const seg &b)const{return x<b.x;}
}arr[MXN<<1];
struct node{ll cov,sum;}t[MXN<<4];
#define ls p<<1
#define rs p<<1|1
inline void mod(ll p,ll l,ll r,ll ml,ll mr,ll mx){
	if(pool[l]>=ml && pool[r+1]<=mr){
		t[p].cov+=mx;
		t[p].sum=t[p].cov?pool[r+1]-pool[l]:t[ls].sum+t[rs].sum;
		return;
	}
	ll mid=(l+r)>>1;
	if(ml<pool[mid+1])mod(ls,l,mid,ml,mr,mx);
	if(mr>pool[mid+1])mod(rs,mid+1,r,ml,mr,mx);
	if(!t[p].cov)t[p].sum=t[ls].sum+t[rs].sum;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		ll x1,y1,x2,y2;
		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		pool[i]=y1,pool[i+n]=y2;
		arr[i]=seg(x1,y1,y2,1),arr[i+n]=seg(x2,y1,y2,-1);
	}
	sort(arr+1,arr+1+(n<<1));
	sort(pool+1,pool+1+(n<<1));
	unq=unique(pool+1,pool+1+(n<<1))-pool-1;
	for(int i=1;i<=n<<1;i++){
		mod(1,1,unq-1,arr[i].ylow,arr[i].yup,arr[i].tp);
		res+=t[1].sum*(arr[i+1].x-arr[i].x);
	}
	printf("%lld",res);
	return 0;
}

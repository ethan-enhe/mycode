#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=2e5+5;
ll n,useless,pool[MXN],ans[MXN],cnt;
struct que{ll op,t,l,r;}arr[MXN],tmp[MXN];

ll dat[MXN];
inline void mod(ll x,ll v){for(;x<=cnt;x+=x&(-x))dat[x]+=v;}
inline ll sum(ll x){ll res=0;for(;x;x^=x&(-x))res+=dat[x];return res;}
inline void reset(ll x){for(;x<=cnt;x+=x&(-x))dat[x]=0;}

inline bool cmp(const que &x,const que &y){return x.t<y.t;}

inline void cdq(ll l,ll r){
	if(l==r)return;
	ll mid=(l+r)>>1,indl=l;
	cdq(l,mid),cdq(mid+1,r);

	for(ll i=mid+1;i<=r;i++){
		while(indl<=mid && arr[indl].t<=arr[i].t){
			if(arr[indl].op==-2)mod(arr[indl].l,pool[arr[indl].l]);
			else if(arr[indl].op==-1)mod(arr[indl].l,-pool[arr[indl].l]);
			indl++;
		}
		if(arr[i].op>0)
			ans[arr[i].op]+=sum(arr[i].r)-sum(arr[i].l);
	}
	while(--indl>=l)
		if(arr[indl].op<0)
			reset(arr[indl].l);
	merge(arr+l,arr+mid+1,arr+mid+1,arr+r+1,tmp+l,cmp);
	for(int i=l;i<=r;i++)arr[i]=tmp[i];
}

int main(){
	memset(ans,-1,sizeof(ans));
	scanf("%lld%lld%lld",&n,&useless,&useless);
	for(ll i=1;i<=n;i++){
		scanf("%lld%lld%lld",&arr[i].op,&arr[i].t,&arr[i].l);
		arr[i].op-=3;
		if(arr[i].op==0){
			arr[i].l--;
			arr[i].op+=i;
			ans[i]=0;
			scanf("%lld",&arr[i].r);
			pool[++cnt]=arr[i].r;
		}
		pool[++cnt]=arr[i].l;
	}
	sort(pool+1,pool+1+cnt);
	cnt=unique(pool+1,pool+1+cnt)-pool-1;
	for(ll i=1;i<=n;i++){
		arr[i].l=lower_bound(pool+1,pool+1+cnt,arr[i].l)-pool;
		if(arr[i].op>0)
			arr[i].r=lower_bound(pool+1,pool+1+cnt,arr[i].r)-pool;
	}
	cdq(1,n);
	for(ll i=1;i<=n;i++)
		if(ans[i]!=-1)
			printf("%lld\n",ans[i]);
	return 0;
}

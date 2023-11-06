#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int INF=1e9;
const int BHEI=10;
const int BMOD=(1<<BHEI)-1;
const int MXN=2e5+BMOD+10;

#define bid(x) (((x)+BMOD)>>BHEI)
#define bst(x) (((x)<<BHEI)-BMOD)
#define ben(x) ((x)<<BHEI)

int n,m,ori[MXN];
long long ans;
pair<int,int> arr[MXN];

inline int leq(int l,int r,int x){
	if(l>r)return 0;
	int lid=bid(l),rid=bid(r),res=0;
	if(lid==rid){
		for(int i=bst(lid);i<=ben(lid);i++)res+=(arr[i].se>=l && arr[i].se<=r && arr[i].fi<=x);
		return res;
	}
	for(int i=bst(lid);i<=ben(lid);i++)res+=(arr[i].se>=l && arr[i].fi<=x);
	for(int i=bst(rid);i<=ben(rid);i++)res+=(arr[i].se<=r && arr[i].fi<=x);
	for(int i=lid+1;i<rid;i++)res+=upper_bound(arr+bst(i),arr+ben(i)+1,mp(x,INF))-arr-bst(i);
	return res;
}
inline void swp(int l,int r){
	int lid=bid(l),rid=bid(r),lp,rp,tmp;
	for(int i=bst(lid);i<=ben(lid);i++)
		if(arr[i].se==l){lp=i;break;}
	for(int i=bst(rid);i<=ben(rid);i++)
		if(arr[i].se==r){rp=i;break;}
	tmp=arr[lp].fi;arr[lp].fi=arr[rp].fi;
	while(lp>bst(lid) && arr[lp].fi<arr[lp-1].fi){swap(arr[lp],arr[lp-1]);lp--;}
	while(lp<ben(lid) && arr[lp].fi>arr[lp+1].fi){swap(arr[lp],arr[lp+1]);lp++;}
	arr[rp].fi=tmp;
	while(rp>bst(rid) && arr[rp].fi<arr[rp-1].fi){swap(arr[rp],arr[rp-1]);rp--;}
	while(rp<ben(rid) && arr[rp].fi>arr[rp+1].fi){swap(arr[rp],arr[rp+1]);rp++;}
	swap(ori[l],ori[r]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)arr[i]=mp(ori[i]=i,i);
	for(int i=n+1;i<=n+BMOD;i++)arr[i]=mp(INF,-1);
	while(m--){
		int l,r;
		scanf("%d%d",&l,&r);
		if(l>r)swap(l,r);
		ans+=(ori[l]<ori[r])-(ori[l]>ori[r])+((leq(l+1,r-1,ori[r])-leq(l+1,r-1,ori[l]))<<1);
		swp(l,r);
		printf("%lld\n",ans);
	}
	return 0;
}

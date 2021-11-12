#include <bits/stdc++.h>
using namespace std;
const int MXN=1e5+5,BSZ=548,Q=25000,MXQ=Q+5;
int n,m,q,arr[MXN],pool[MXN];
struct que{
	int l,r,id;
	inline bool operator < (const que &y)const{
		if(l/BSZ!=y.l/BSZ)return l<y.l;
		return l/BSZ&1?r>y.r:r<y.r;
	}
}ask[MXQ*3];
bitset<MXN> res[MXQ],cur;
int sz[MXQ],cnt[MXN];
inline void ins(int x){cur[x+(++cnt[x])]=1;}
inline void del(int x){cur[x+(cnt[x]--)]=0;}
inline void solve(int q){
	for(int i=1;i<=q;i++){
		res[i].set(),sz[i]=0;
		for(int j=0;j<3;j++){
			int l,r;
			scanf("%d%d",&l,&r);
			ask[i+j*q]={l,r,i};
			sz[i]+=r-l+1;
		}
	}
	q*=3;
	sort(ask+1,ask+1+q);
	int il=1,ir=0;
	for(int i=1;i<=q;i++){
		while(ir<ask[i].r)ins(arr[++ir]);
		while(il>ask[i].l)ins(arr[--il]);
		while(ir>ask[i].r)del(arr[ir--]);
		while(il<ask[i].l)del(arr[il++]);
		res[ask[i].id]&=cur;
	}
	while(il<=ir)del(arr[il++]);
	q/=3;
	for(int i=1;i<=q;i++)
		printf("%d\n",sz[i]-(int)res[i].count()*3);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",arr+i);
		pool[i]=arr[i];
	}
	sort(pool+1,pool+1+n);
	for(int i=1;i<=n;i++)
		arr[i]=lower_bound(pool+1,pool+1+n,arr[i])-pool-1;
	while(m){
		int delt=min(m,Q);
		solve(delt);
		m-=delt;
	}
	return 0;
}

//P3810 【模板】三维偏序（陌上花开）
#include<bits/stdc++.h>
using namespace std;
const int MXN=2e5+5;

int n,k,ans[MXN],cnt[MXN];
struct que{bool tp;int i,a,b,c;}arr[MXN];
inline bool cmpa(que x,que y){return x.a==y.a?x.tp>y.tp:x.a<y.a;}
inline bool cmpb(que x,que y){return x.b==y.b?x.tp>y.tp:x.b<y.b;}

int d[MXN];
inline void mod(int x,int y){for(;x<=k;x+=x&(-x))d[x]+=y;}
inline int sum(int x){int r=0;for(;x;x^=x&(-x))r+=d[x];return r;}

inline void cdq(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1,ind=l;
	cdq(l,mid),cdq(mid+1,r);
	for(int i=mid+1;i<=r;i++)
		if(!arr[i].tp){
			while(ind<=mid && arr[ind].b<=arr[i].b)
				if(arr[ind++].tp)mod(arr[ind-1].c,1);
			ans[arr[i].i]+=sum(arr[i].c);
		}
	while(--ind>=l)
		if(arr[ind].tp)mod(arr[ind].c,-1);
	inplace_merge(arr+l,arr+mid+1,arr+r+1,cmpb);
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&arr[i].a,&arr[i].b,&arr[i].c);
		arr[i].i=i,arr[i+n]=arr[i],arr[i].tp=1;
	}
	sort(arr+1,arr+1+(n<<1),cmpa);
	cdq(1,n<<1);
	for(int i=1;i<=n;i++)cnt[ans[i]]++;
	for(int i=1;i<=n;i++)printf("%d\n",cnt[i]);
	return 0;
}



//陌上花开（三维偏序）
#include<bits/stdc++.h>
using namespace std;
const int MXN=2e5+5;

struct que{int id,tp,x,y,z;}arr[MXN],tmp[MXN];
inline bool cmpx(que a,que b){return a.x==b.x?a.tp>b.tp:a.x<b.x;}
inline bool cmpy(que a,que b){return a.y==b.y?a.tp>b.tp:a.y<b.y;}

int n,k,c[MXN],ans[MXN],cnt[MXN];
inline void mod(int x,int y){for(;x<=k;x+=x&(-x))c[x]+=y;}
inline int sum(int x){int res=0;for(;x;x-=x&(-x))res+=c[x];return res;}

void cdq(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1,ind=l;
	cdq(l,mid);
	cdq(mid+1,r);
	for(int i=mid+1;i<=r;i++){
		while(ind<=mid && arr[ind].y<=arr[i].y){
			if(arr[ind].tp)mod(arr[ind].z,1);
			ind++;
		}
		if(!arr[i].tp)ans[arr[i].id]+=sum(arr[i].z);
	}
	while(--ind>=l)
		if(arr[ind].tp)
			mod(arr[ind].z,-1);
	merge(arr+l,arr+mid+1,arr+mid+1,arr+r+1,tmp+l,cmpy);
	for(int i=l;i<=r;i++)
		arr[i]=tmp[i];
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&arr[i].x,&arr[i].y,&arr[i].z);
		arr[i].id=i;
		arr[i+n]=arr[i];
		arr[i].tp=1;
	}
	sort(arr+1,arr+1+(n<<1),cmpx);
	cdq(1,n<<1);
	for(int i=1;i<=n;i++)cnt[ans[i]-1]++;
	for(int i=0;i<n;i++)printf("%d\n",cnt[i]);

	return 0;
}

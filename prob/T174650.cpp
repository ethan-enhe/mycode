#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pi;

const int MXN=2e5+5;
const int NR=1e6+5;
int n,k,mx,fa[MXN],cnt[NR];long long res=0;
pi tmp[MXN],arr[MXN];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&tmp[i].fi);
		cnt[tmp[i].fi]++;
		tmp[i].se=i;
		mx=max(mx,tmp[i].fi);
		fa[i]=i;fa[i+k]=i+k;
	}
	for(int i=mx;i;i--)
		cnt[i]+=cnt[i+1];
	for(int i=1;i<=n;i++)
		arr[cnt[tmp[i].fi]--]=tmp[i];
	for(int i=1;i<=n;i++){
		int tmp=find(max(arr[i].se,k));
		fa[tmp]=tmp+1;
		res+=(long long)arr[i].fi*(tmp+1);
	}
	printf("%lld",res);
	return 0;
}

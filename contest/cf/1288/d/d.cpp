#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int INF=1e9;
const int MXN=3e5+5;
const int MXM=8;

int n,m;
int arr[MXN][MXM];
inline int maxi_mn(int tp){
	int ans=-INF;
	for(int i=1;i<=n;i++){
		int tmn=INF;
		for(int j=0;j<m;j++)
			if((tp>>j)&1)
				tmn=min(tmn,arr[i][j]);
		ans=max(ans,tmn);
	}
	return ans;
}
int res[1<<MXM],id[1<<MXM],ALL;
inline void solve(){
	scanf("%d%d",&n,&m);
	ALL=(1<<m)-1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&arr[i][j]);
	int ans=-INF;
	for(int i=0;i<=ALL;i++)res[i]=maxi_mn(i);
	for(int i=0;i<=ALL;i++)ans=max(ans,min(res[i],res[ALL^i]));
	for(int i=1;i<=n;i++){
		int stat=0;
		for(int j=0;j<m;j++)
			if(arr[i][j]>=ans)
				stat|=1<<j;
		id[ALL^stat]=i;
	}
	for(int i=1;i<=ALL;i++)
		for(int j=0;j<m;j++)
			if((i>>j)&1)
				id[i]=max(id[i],id[i^(1<<j)]);
	for(int i=1;i<=n;i++){
		int stat=0;
		for(int j=0;j<m;j++)
			if(arr[i][j]>=ans)
				stat|=1<<j;
		if(id[stat]){
			printf("%d %d\n",i,id[stat]);
			return;
		}
	}
}
/*

2 8
0 0 0 1 1 0 1 1
1 1 1 0 1 1 0 0
 */
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	solve();
	return 0;
}

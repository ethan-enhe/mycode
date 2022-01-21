#include<bits/stdc++.h>
using namespace std;
const int MXN=2e5+5;
const int INF=1e9;
int n,q,cnt;
bool isbst[MXN];
int va[MXN],mn[MXN],mx[MXN],fa[MXN],ls[MXN],rs[MXN];
inline void pushu(int x){
	mn[x]=min(va[x],min(mn[ls[x]],mn[rs[x]]));
	mx[x]=max(va[x],max(mx[ls[x]],mx[rs[x]]));
	isbst[x]=isbst[ls[x]] && isbst[rs[x]] && mn[rs[x]]>=va[x] && mx[ls[x]]<=va[x];
}
inline void mod(int x,int y){
	va[x]=y;
	while(x){
		bool last=isbst[x];
		cnt-=isbst[x];
		pushu(x);
		cnt+=isbst[x];
		if(!last && !isbst[x])break;
		x=fa[x];
	}
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d%d",ls+i,rs+i);
		fa[ls[i]]=fa[rs[i]]=i;
		isbst[i]=1;
	}
	mn[0]=INF,mx[0]=-INF;
	isbst[0]=1;cnt=n;
	for(int i=1,tmp;i<=n;i++){
		scanf("%d",&tmp);
		mod(i,tmp);
	}
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
		mod(x,y);
		printf("%d\n",cnt);
	}


	return 0;
}

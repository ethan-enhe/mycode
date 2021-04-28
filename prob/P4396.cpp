#include<bits/stdc++.h>
using namespace std;
const int MXN=1e5+5;
const int BHEI=10;
struct tarr{
	int s[MXN],upp;
	inline void mod(int x,int y){for(;x<MXN;x+=x&(-x))s[x]+=y;}
	inline int pre(int x){int res=0;for(;x;x^=x&(-x))res+=s[x];return res;}
	inline int sum(int l,int r){return pre(r)-pre(l-1);}
}cnt,app;
struct que{
	int l,r,a,b,id;
	inline bool operator < (const que &y){
		int bx=l>>BHEI,by=y.l>>BHEI;
		return bx==by?bx&1?r>y.r:r<y.r:bx<by;
	}
}ask[MXN];

int n,m,arr[MXN];
int ocnt[MXN],ans[2][MXN];
int lind=1,rind;
inline void add(int x){
	if(!(ocnt[x]++))app.mod(x,1);
	cnt.mod(x,1);
}
inline void del(int x){
	if(!(--ocnt[x]))app.mod(x,-1);
	cnt.mod(x,-1);
}
int main(){
	freopen("test.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",arr+i);
	for(int i=1;i<=m;i++)scanf("%d%d%d%d",&ask[i].l,&ask[i].r,&ask[i].a,&ask[i].b),ask[i].id=i;
	sort(ask+1,ask+1+m);
	for(int i=1;i<=m;i++){
		while(rind<ask[i].r)add(arr[++rind]);
		while(lind>ask[i].l)add(arr[--lind]);
		while(rind>ask[i].r)del(arr[rind--]);
		while(lind<ask[i].l)del(arr[lind++]);
		ans[0][ask[i].id]=cnt.sum(ask[i].a,ask[i].b);
		ans[1][ask[i].id]=app.sum(ask[i].a,ask[i].b);
	}
	for(int i=1;i<=m;i++)printf("%d %d\n",ans[0][i],ans[1][i]);
	return 0;
}


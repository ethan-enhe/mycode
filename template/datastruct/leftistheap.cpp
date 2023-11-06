#include<bits/stdc++.h>
using namespace std;
const int MXN=1e6+5;
struct node{int va,d,ls,rs;}t[MXN];
int nodec,rt,n;
inline int merge(int x,int y){
	if(!x || !y)return x|y;
	if(t[y].va<t[x].va)swap(x,y);
	t[x].rs=merge(t[x].rs,y);
	if(t[t[x].rs].d>t[t[x].ls].d)swap(t[x].ls,t[x].rs);
	t[x].d=t[t[x].rs].d+1;
	return x;
}
int main(){
	scanf("%d",&n);
	while(n--){
		int op,x;
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&x);
			t[++nodec].va=x;
			rt=merge(rt,nodec);
		}
		else if(op==2)printf("%d\n",t[rt].va);
		else rt=merge(t[rt].ls,t[rt].rs);
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
const int MXN=1e5+5;
struct node{int va,sz,rnd,ls,rs;}t[MXN];
int nodec,rt;
inline int nnode(int x){
	t[++nodec]=node{x,1,rand(),0,0};
	return nodec;
}
inline void pushu(int p){if(p)t[p].cnt=t[t[p].ls].cnt+1+t[t[p].rs].cnt;}
int merge(int lr,int rr){
	int p;
	if(!lr || !rr)return lr|rr;
	if(t[lr].rnd<t[rr].rnd)p=lr,t[lr].rs=merge(t[lr].rs,rr);
	else p=rr,t[rr].ls=merge(lr,t[rr].ls);
	return pushu(p),p;
}
void split(int p,int &lr,int &rr,int va){
	if(!p){
		lr=rr=0;
		return;
	}
	if(t[p].va<=va)lr=p,split(t[p].rs,t[p].rs,rr,va);
	else rr=p,split(t[p].ls,lr,t[p].ls,va);
	pushu(lr);
	pushu(rr);
}
void splitrk(int p,int &lr,int &rr,int k){
	if(!p){
		lr=rr=0;
		return;
	}
	int tmp=t[t[p].ls].cnt+1;
	if(tmp<=k)lr=p,splitrk(t[p].rs,t[p].rs,rr,k-tmp);
	else rr=p,splitrk(t[p].ls,lr,t[p].ls,k);
	pushu(lr);
	pushu(rr);
}
inline int grk(int va){
	int x,y,z;
	split(rt,x,y,va-1);
	z=t[x].cnt+1;
	rt=merge(x,y);
	return z;
}
inline int gva(int k){
	int x,y,z;
	splitrk(rt,y,z,k);
	splitrk(y,x,y,k-1);
	k=t[y].va;
	y=merge(x,y);
	rt=merge(y,z);
	return k;
}
inline void del(int x){
	int a,b,c;
	split(rt,b,c,x);
	split(rt,a,b,x-1);
	rt=merge(a,merge(merge(t[b].ls,t[b].rs),c));
}
int main(){
	srand(65536);
	int t,op,x;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&op,&x);
		if(op==1)ins(x);
		else if(op==2)del(x);
		else if(op==3)printf("%d\n",grk(x));
		else if(op==4)printf("%d\n",gva(x));
		else if(op==5)printf("%d\n",gva(grk(x)-1));
		else printf("%d\n",gva(grk(x+1)));
	}

	return 0;
}

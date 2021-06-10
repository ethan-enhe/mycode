//普通平衡树
#include<bits/stdc++.h>
using namespace std;
const int MXN=1e5+5;
struct node{
	int va,cnt,rnd,ls,rs;
	node(){va=cnt=ls=rs=0;}
}t[MXN];
int rt,nodec;
inline int newnode(int va){
	++nodec;
	t[nodec].va=va;
	t[nodec].cnt=1;
	t[nodec].rnd=rand();
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
inline int getrk(int va){
	int x,y,z;
	split(rt,x,y,va-1);
	z=t[x].cnt+1;
	rt=merge(x,y);
	return z;
}
inline int getva(int k){
	int x,y,z;
	splitrk(rt,y,z,k);
	splitrk(y,x,y,k-1);
	k=t[y].va;
	y=merge(x,y);
	rt=merge(y,z);
	return k;
}
int n;
int main(){
	srand(time(NULL));
	scanf("%d",&n);
	while(n--){
		int op,va,x,y,z;
		scanf("%d%d",&op,&va);
		if(op==1){
			split(rt,x,y,va);
			x=merge(x,newnode(va));
			rt=merge(x,y);
		}
		else if(op==2){
			split(rt,y,z,va);
			split(y,x,y,va-1);
			y=merge(t[y].ls,t[y].rs);
			y=merge(x,y);
			rt=merge(y,z);
		}
		else if(op==3)printf("%d\n",getrk(va));
		else if(op==4)printf("%d\n",getva(va));
		else if(op==5)printf("%d\n",getva(getrk(va)-1));
		else printf("%d\n",getva(getrk(va+1)));
	}
	return 0;
}

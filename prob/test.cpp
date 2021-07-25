#include<bits/stdc++.h>
using namespace std;
const int MXN=1e5+5;
struct node{
	int v,sz,rnd,ls,rs;
}t[MXN];
int nodec;
inline int nnode(int x){
	t[++nodec]=node{x,1,rand(),0,0};
	return nodec;
}
inline void pushu(int p){t[p].sz=t[t[p].ls].sz+t[t[p].rs].sz+1;}
inline int merge(int rx,int ry){
	if(!rx || !ry)return rx|ry;
	int p;
	if(t[rx].rnd>t[ry].rnd)t[p=rx].rs=merge(t[rx].rs,ry);
	else t[p=ry].ls=merge(rx,t[ry].ls);
	return pushu(p),p;
}
inline void split(int p,int va,int &rx,int &ry){
	if(!p){rx=ry=0;return;}
	if(t[p].v<=va)split(t[rx=p].rs,va,t[p].rs,ry);
	else split(t[ry=p].ls,va,rx,t[p].ls);
	pushu(p);
}
inline void splitrk(int p,int rk,int &rx,int &ry){
	if(!p){rx=ry=0;return;}
	int tsz=t[t[p].ls].sz+1;
	if(rk>=tsz)splitrk(t[rx=p].rs,rk-tsz,t[p].rs,ry);
	else splitrk(t[ry=p].ls,rk,rx,t[p].ls);
	pushu(p);
}

int rt;
inline void ins(int x){
	int a,b=nnode(x),c;
	split(rt,x,a,c);
	rt=merge(a,merge(b,c));
}
inline void del(int x){
	int a,b,c;
	split(rt,x-1,a,b);
	split(b,x,b,c);
	rt=merge(a,merge(merge(t[b].ls,t[b].rs),c));
}
inline int grk(int x){
	int a,b,r;
	split(rt,x-1,a,b);
	r=t[a].sz+1;
	rt=merge(a,b);
	return r;
}
inline int gva(int rk){
	int a,b,c,r;
	splitrk(rt,rk,b,c);
	splitrk(b,rk-1,a,b);
	r=t[b].v;
	rt=merge(merge(a,b),c);
	return r;
}

int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		int op,x;
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

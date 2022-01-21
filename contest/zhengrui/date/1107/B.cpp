#include<bits/stdc++.h>
using namespace std;
const int MXN=5e5+5;
struct node{
	int va,sz,rnd,ls,rs;bool revt;
	node(int va=0,int sz=0,int rnd=0,int ls=0,int rs=0,bool revt=0):
		va(va),sz(sz),rnd(rnd),ls(ls),rs(rs),revt(revt){}
}t[MXN];
int n,m,nodec,rt;
inline int nnode(int va){
	t[++nodec]=node(va,1,rand());
	return nodec;
}
inline void pushu(int p){if(p)t[p].sz=1+t[t[p].ls].sz+t[t[p].rs].sz;}
inline void pushd(int p){
	if(p && t[p].revt){
		t[p].revt=0;
		t[t[p].ls].revt^=1;
		t[t[p].rs].revt^=1;
		swap(t[p].ls,t[p].rs);
	}
}
void splitrk(int p,int &lr,int &rr,int rk){
	if(!p){
		lr=rr=0;
		return;
	}
	pushd(p);
	int tsz=t[t[p].ls].sz+1;
	if(tsz<=rk)splitrk(t[lr=p].rs,t[p].rs,rr,rk-tsz);
	else splitrk(t[rr=p].ls,lr,t[p].ls,rk);
	pushu(lr),pushu(rr);
}
int merge(int lr,int rr){
	if(!lr || !rr)return lr|rr;
	pushd(lr),pushd(rr);
	int res;
	if(t[lr].rnd<t[rr].rnd)t[res=lr].rs=merge(t[lr].rs,rr);
	else t[res=rr].ls=merge(lr,t[rr].ls);
	return pushu(res),res;
}
void prt(int p){
	if(!p)return;
	pushd(p);
	prt(t[p].ls);
	putchar(t[p].va);
	prt(t[p].rs);
}
inline void flip(int l,int r){
	int a,b,c;
	splitrk(rt,b,c,r);
	splitrk(b,a,b,l-1);
	t[b].revt=1;
	b=merge(a,b);
	rt=merge(b,c);
}

char str[MXN];
int main(){
	srand(65536);
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	for(int i=1;i<=n;i++)rt=merge(rt,nnode(int(str[i])));
	while(m--){
		int r;
		scanf("%d",&r);
		flip(1,r);
	}
	prt(rt);
	return 0;
}


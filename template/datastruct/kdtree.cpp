//P4148 简单题
#include<bits/stdc++.h>
#define sq(x) (x)*(x)
using namespace std;
const double rate=0.75;
const int MXN=2e5+5;
struct p{int x,y,v;}c[MXN];
typedef int arrn[MXN];
int rt,nodec,flatc;
int n,ql,qr,qd,qu;
arrn ls,rs,L,R,D,U,dim,sz,sum,t;
inline void upd(int x,int y){
	sz[x]+=sz[y],sum[x]+=sum[y];
	L[x]=min(L[x],L[y]);
	R[x]=max(R[x],R[y]);
	D[x]=min(D[x],D[y]);
	U[x]=max(U[x],U[y]);
}
inline void pushu(int p){
	sum[p]=c[p].v,sz[p]=1;
	L[p]=R[p]=c[p].x;
	D[p]=U[p]=c[p].y;
	if(ls[p])upd(p,ls[p]);
	if(rs[p])upd(p,rs[p]);
}

inline bool cmpx(int x,int y){return c[x].x<c[y].x;}
inline bool cmpy(int x,int y){return c[x].y<c[y].y;}
inline int build(int l,int r){
	if(l>r)return 0;
	double avx=0,avy=0,vax=0,vay=0;
	for(int i=l;i<=r;i++)avx+=c[t[i]].x,avy+=c[t[i]].y;
	avx/=(r-l+1),avy/=(r-l+1);
	for(int i=l;i<=r;i++)vax+=sq(avx-c[t[i]].x),vay+=sq(avy-c[t[i]].y);

	int mid=(l+r)>>1;
	if(vax>vay)dim[t[mid]]=1,nth_element(t+l,t+mid,t+r+1,cmpx);
	else dim[t[mid]]=0,nth_element(t+l,t+mid,t+r+1,cmpy);
	ls[t[mid]]=build(l,mid-1),rs[t[mid]]=build(mid+1,r);
	return pushu(t[mid]),t[mid];
}
inline void flat(int p){
	if(!p)return;
	flat(ls[p]);
	t[++flatc]=p;
	flat(rs[p]);
}
inline void rebuild(int &p){
	flatc=0;
	flat(p);
	p=build(1,flatc);
}
inline bool balance(int p){return rate*sz[p]>=max(sz[ls[p]],sz[rs[p]]);}
inline void ins(int &p,int x){
	if(!p){
		pushu(p=x);
		return;
	}
	if(dim[p]){
		if(c[x].x<=c[p].x)ins(ls[p],x);
		else ins(rs[p],x);
	}
	else{
		if(c[x].y<=c[p].y)ins(ls[p],x);
		else ins(rs[p],x);
	}
	pushu(p);
	if(!balance(p))rebuild(p);
}
inline int que(int p){
	if(!p || ql>R[p] || qr<L[p] || qd>U[p] || qu<D[p])return 0;
	if(ql<=L[p] && qr>=R[p] && qd<=D[p] && qu>=U[p])return sum[p];
	int res=que(ls[p])+que(rs[p]);
	if(ql<=c[p].x && qr>=c[p].x && qd<=c[p].y && qu>=c[p].y)res+=c[p].v;
	return res;
}

int main(){
	scanf("%*d");
	int last=0,op;
	while(scanf("%d",&op)!=EOF){
		if(op==1){
			++nodec;
			scanf("%d%d%d",&c[nodec].x,&c[nodec].y,&c[nodec].v);
			c[nodec].x^=last,c[nodec].y^=last,c[nodec].v^=last;
			ins(rt,nodec);
		}
		else if(op==2){
			scanf("%d%d%d%d",&ql,&qd,&qr,&qu);
			ql^=last,qr^=last,qu^=last,qd^=last;
			printf("%d\n",last=que(rt));
		}
		else break;
	}
	return 0;
}

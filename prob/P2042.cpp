#include<bits/stdc++.h>
using namespace std;
const int MXN=5e5+5;
const int NOCOVER=1001;
const int INF=2e9;

#define max3(a,b,c) max(max(a,b),c)

struct node{
	int ls,rs,rnd,sz,va,sum,mxsum,mxpre,mxsuf,cov;
	bool rtag;
	inline node(){rnd=rand();}
	inline void set(int x){
		ls=rs=0,sz=1;
		va=sum=mxsum=x;
		mxpre=mxsuf=max(0,x);
		cov=NOCOVER,rtag=0;
	}
}t[MXN];

int n,m,pool[MXN],top,rt;
char str[20];
inline int nnode(int x){
	t[pool[top]].set(x);
	return pool[top--];
}
inline void addt(int p,bool rtag,int cover){
	if(!p)return;
	if(rtag){
		t[p].rtag^=1;
		swap(t[p].mxpre,t[p].mxsuf);
		swap(t[p].ls,t[p].rs);
	}
	if(cover!=NOCOVER){
		t[p].va=t[p].cov=cover;
		t[p].sum=cover*t[p].sz;
		t[p].mxpre=t[p].mxsuf=max(0,cover);
		t[p].mxsum=max(t[p].sum,cover);
	}
}
inline void pushd(int p){
	addt(t[p].ls,t[p].rtag,t[p].cov);
	addt(t[p].rs,t[p].rtag,t[p].cov);
	t[p].rtag=0,t[p].cov=NOCOVER;
}
inline void pushu(int p){
	if(!p)return;
	t[p].sz=t[t[p].ls].sz+t[t[p].rs].sz+1;
	t[p].sum=t[t[p].ls].sum+t[t[p].rs].sum+t[p].va;
	t[p].mxsum=max3(t[t[p].ls].mxsum,t[t[p].rs].mxsum,t[t[p].ls].mxsuf+t[t[p].rs].mxpre+t[p].va);
	t[p].mxpre=max(t[t[p].ls].mxpre,t[t[p].ls].sum+t[t[p].rs].mxpre+t[p].va);
	t[p].mxsuf=max(t[t[p].rs].mxsuf,t[t[p].rs].sum+t[t[p].ls].mxsuf+t[p].va);
}
inline int merge(int pl,int pr){
	if(!pl || !pr)return pl|pr;
	pushd(pl),pushd(pr);int p;
	if(t[pl].rnd>t[pr].rnd)t[p=pl].rs=merge(t[pl].rs,pr);
	else t[p=pr].ls=merge(pl,t[pr].ls);
	return pushu(p),p;
}
inline void split(int p,int &pl,int &pr,int rk){
	if(!p){pl=pr=0;return;}
	pushd(p);int tsz=t[t[p].ls].sz+1;
	if(rk>=tsz)split(t[pl=p].rs,t[p].rs,pr,rk-tsz);
	else split(t[pr=p].ls,pl,t[p].ls,rk);
	pushu(pl),pushu(pr);
}
inline void del(int p){
	if(!p)return;
	pool[++top]=p;
	del(t[p].ls),del(t[p].rs);
}
int main(){
	srand(65536);
	for(int i=MXN-1;i;i--)pool[++top]=i;
	t[0].sz=0,t[0].mxsum=-INF;

	scanf("%d%d",&n,&m);
	for(int i=1,tmp;i<=n;i++){
		scanf("%d",&tmp);
		rt=merge(rt,nnode(tmp));
	}
	for(int i=1,a,b,c,ra,rb,rc;i<=m;i++){
		scanf(" %s",str);
		if(str[0]=='I'){
			scanf("%d%d",&a,&b);
			split(rt,ra,rb,a);
			while(b--){
				scanf("%d",&c);
				ra=merge(ra,nnode(c));
			}
			rt=merge(ra,rb);
		}
		else if(str[0]=='D'){
			scanf("%d%d",&a,&b);
			split(rt,ra,rb,a-1);
			split(rb,rb,rc,b);
			del(rb);
			rt=merge(ra,rc);
		}
		else if(str[0]=='M' && str[2]=='K'){
			scanf("%d%d%d",&a,&b,&c);
			split(rt,ra,rb,a-1);
			split(rb,rb,rc,b);
			addt(rb,0,c);
			rt=merge(ra,merge(rb,rc));
		}
		else if(str[0]=='R'){
			scanf("%d%d",&a,&b);
			split(rt,ra,rb,a-1);
			split(rb,rb,rc,b);
			addt(rb,1,NOCOVER);
			rt=merge(ra,merge(rb,rc));
		}
		else if(str[0]=='G'){
			scanf("%d%d",&a,&b);
			split(rt,ra,rb,a-1);
			split(rb,rb,rc,b);
			printf("%d\n",t[rb].sum);
			rt=merge(ra,merge(rb,rc));
		}
		else printf("%d\n",t[rt].mxsum);
	}
	return 0;
}

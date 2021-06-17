//树套树 用法见 https://www.luogu.com.cn/record/51646520
#include<bits/stdc++.h>
using namespace std;

#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char buf[1<<20],*p1=buf,*p2=buf;
template<class T>
inline void read(T &x){
	T f=1;x=0;char c;
	while(c=gc(),x<'0' || c>'9')if(c=='-')f=-1;
	while(c>='0' && c<='9')x=(x<<3)+(x<<1)+(c^48),c=gc();
	x*=f;
}


const int MXN=2e4+5;
const int LG=30;
namespace treap{
	struct node{int va,sz,rnd,ls,rs;}t[MXN*LG];int nodec;
	inline int nnode(int va){return t[++nodec]=node{va,1,rand()},nodec;}
	inline void pushu(int p){t[p].sz=t[t[p].ls].sz+t[t[p].rs].sz+1;}
	inline int merge(int lp,int rp){
		if(!lp || !rp)return lp|rp;
		if(t[lp].rnd>t[rp].rnd)return t[lp].rs=merge(t[lp].rs,rp),pushu(lp),lp;
		else return t[rp].ls=merge(lp,t[rp].ls),pushu(rp),rp;
	}
	inline void split(int p,int &lp,int &rp,int va){
		if(!p){lp=rp=0;return;}
		if(t[p].va<=va)split(t[lp=p].rs,t[p].rs,rp,va),pushu(lp);
		else split(t[rp=p].ls,lp,t[p].ls,va),pushu(rp);
	}
	//va为正代表插入，负代表删除
	inline void mod(int &rt,int va){
		int x,y,z;
		if(va>0)split(rt,x,y,va),rt=merge(merge(x,nnode(va)),y);
		else va=-va,split(rt,y,z,va),split(y,x,y,va-1),rt=merge(merge(x,merge(t[y].ls,t[y].rs)),z);
	}
	inline int qrange(int &rt,int l,int r){
		int x,y,z,res;
		split(rt,y,z,r);
		split(y,x,y,l-1);
		res=t[y].sz;
		rt=merge(merge(x,y),z);
		return res;
	}
}
namespace segt{
	struct node{int rt,ls,rs;}t[MXN*LG];int nodec,rt,mxva,mnva;
	//注：mx 是值，mv 是下标，mv>0 表示插入，否则为删除
	inline void mod(int &p,int l,int r,int mx,const vector<int> &mv){
		if(!p)p=++nodec;
		for(size_t i=0;i<mv.size();i++)treap::mod(t[p].rt,mv[i]);
		if(l==r)return;
		int mid=(l+r)>>1;
		if(mx<=mid)mod(t[p].ls,l,mid,mx,mv);
		else mod(t[p].rs,mid+1,r,mx,mv);
	}
	//ql,qr 是值域，qvl,qvr 是下标
	inline int que(int p,int l,int r,int ql,int qr,int qvl,int qvr){
		if(!p)return 0;
		if(ql<=l && r<=qr)return treap::qrange(t[p].rt,qvl,qvr);
		int mid=(l+r)>>1,res=0;
		if(ql<=mid)res=que(t[p].ls,l,mid,ql,qr,qvl,qvr);
		if(qr>mid)res+=que(t[p].rs,mid+1,r,ql,qr,qvl,qvr);
		return res;
	}
	inline int que(int xl,int xr,int yl,int yr){
		if(xl>xr || yl>yr)return 0;
		return que(rt,mnva,mxva,yl,yr,xl,xr);
	}
	inline void mod(const vector<int> &mx,int my){mod(rt,mnva,mxva,my,mx);}
}


int main(){
	srand(time(NULL));
	segt::mnva=1,segt::mxva=1e9;

	return 0;
}

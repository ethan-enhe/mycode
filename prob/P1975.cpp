//树套树
#include<bits/stdc++.h>
using namespace std;

#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char buf[1<<20],*p1=buf,*p2=buf;
template<class T>
inline void read(T &x){
	bool f=0;x=0;char c;
	while(c=gc(),c<'0' || c>'9')if(c=='-')f=1;
	while(c>='0' && c<='9')x=(x<<3)+(x<<1)+(c^48),c=gc();
	if(f)x=-x;
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

int n,m,arr[MXN],pool[MXN],rt,ans;
namespace bit{
	int dat[MXN];
	inline void mod(const vector<int> &mv,int mx){
		for(;mx<=n;mx+=mx&(-mx))
			for(size_t i=0;i<mv.size();i++)
				treap::mod(dat[mx],mv[i]);
	}
	inline int que(int qr,int qvl,int qvr){
		int res=0;
		for(;qr;qr^=qr&(-qr))
			res+=treap::qrange(dat[qr],qvl,qvr);
		return res;
	}
	inline int que(int xl,int xr,int yl,int yr){
		if(xl>xr || yl>yr)return 0;
		return que(yr,xl,xr)-que(yl-1,xl,xr);
	}
}


int main(){
	srand(time(NULL));
	read(n);
	for(int i=1;i<=n;i++)
		read(arr[i]),pool[i]=arr[i];
	sort(pool+1,pool+1+n);
	for(int i=1;i<=n;i++){
		bit::mod({i},arr[i]=(lower_bound(pool+1,pool+1+n,arr[i])-pool));
		ans+=bit::que(1,i-1,arr[i]+1,n);
	}
	printf("%d\n",ans);
	read(m);
	while(m--){
		int x,y;
		read(x),read(y);
		if(x>y)swap(x,y);
		if(arr[x]<arr[y]){
			ans+=bit::que(x+1,y-1,arr[x]+1,arr[y]-1)*2
				+bit::que(x+1,y-1,arr[x],arr[x])
				+bit::que(x+1,y-1,arr[y],arr[y])+1;
			bit::mod({-x,y},arr[x]);
			bit::mod({-y,x},arr[y]);
			swap(arr[x],arr[y]);
		}
		else if(arr[x]>arr[y]){
			bit::mod({-x,y},arr[x]);
			bit::mod({-y,x},arr[y]);
			swap(arr[x],arr[y]);
			ans-=bit::que(x+1,y-1,arr[x]+1,arr[y]-1)*2
				+bit::que(x+1,y-1,arr[x],arr[x])
				+bit::que(x+1,y-1,arr[y],arr[y])+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}


#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
#define pb push_back

using namespace std;

#define gc() (bl==br && (br=(bl=buf)+fread(buf,1,1<<20,stdin),bl==br)?EOF:*bl++)
char buf[1<<20],*bl=buf,*br=buf;
template<class T>
inline void read(T &x){
	T f=1;x=0;char c;
	while(c=gc(),(c<'0' || c>'9'))if(c=='-')f=-1;
	while(c>='0' && c<='9')x=(x<<3)+(x<<1)+(c^48),c=gc();
	x*=f;
}

typedef pair<int,int> pi;
const int MXN=1e5+5;

int n,c[MXN],pool[MXN],ans[MXN];
vector<int> e[MXN];

int rt[MXN],nodec;
struct node{
	int ls,rs,va;
	node(int ls=0,int rs=0,int va=0):ls(ls),rs(rs),va(va){}
}t[MXN*40];
inline void pu(int p){t[p].va=max(t[t[p].ls].va,t[t[p].rs].va);}
inline void mod(int &p,int l,int r,int mx,int mv){
	if(!p)p=++nodec;
	if(l==r){
		t[p].va+=mv;
		return;
	}
	int mid=(l+r)>>1;
	if(mx<=mid)mod(t[p].ls,l,mid,mx,mv);
	else mod(t[p].rs,mid+1,r,mx,mv);
	pu(p);
}
inline int merge(int lp,int rp,int l,int r){
	if(!lp || !rp)return lp|rp;
	if(l==r){
		t[lp].va+=t[rp].va;
		return lp;
	}
	int mid=(l+r)>>1;
	t[lp].ls=merge(t[lp].ls,t[rp].ls,l,mid);
	t[lp].rs=merge(t[lp].rs,t[rp].rs,mid+1,r);
	return pu(lp),lp;
}


inline void dfs(int p,int fa){
	for(int nx:e[p]){
		if(nx==fa)continue;
		dfs(nx,p);
		rt[p]=merge(rt[p],rt[nx],1,n);
	}
	ans[p]=t[rt[p]].va;
}

int main(){
	read(n);
	for(int i=1;i<=n;i++)read(c[i]),pool[i]=c[i];
	for(int i=1,ts,tt;i<n;i++){
		read(ts),read(tt);
		e[ts].pb(tt);
		e[tt].pb(ts);
	}
	sort(pool+1,pool+1+n);
	for(int i=1;i<=n;i++){
		c[i]=lower_bound(pool+1,pool+1+n,c[i])-pool;
		mod(rt[i],1,n,c[i],1);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);

	return 0;
}

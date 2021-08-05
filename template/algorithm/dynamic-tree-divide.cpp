#include<bits/stdc++.h>
using namespace std;
const int MXN=1e5+5;
const int LG=17;
int n,m,va[MXN];
vector<int> te[MXN],e[MXN];
int anc[MXN][LG+1],dpth[MXN];
inline void init_lca(int p){
	for(int i=1;i<=LG;i++)anc[p][i]=anc[anc[p][i-1]][i-1];
	for(int nx:te[p])
		if(nx!=anc[p][0]){
			dpth[nx]=dpth[p]+1;
			anc[nx][0]=p;
			init_lca(nx);
		}
}
inline int get_dis(int x,int y){
	if(dpth[x]<dpth[y])swap(x,y);
	int res=dpth[x]+dpth[y],tmp=dpth[x]-dpth[y];
	for(int i=LG;~i;i--)
		if((tmp>>i)&1)
			x=anc[x][i];
	if(x==y)return res-(dpth[x]<<1);

	for(int i=LG;~i;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return res-(dpth[x]<<1)+2;
}
//build
vector<int> c[MXN],_c[MXN];
inline void mod(vector<int> &d,int x,int y){
	for(++x;x<(int)d.size();x+=x&(-x)){
		//if(x>=d.size() || x<0)cout<<"@@",exit(0);
		d[x]+=y;
	}
}
inline int pre(const vector<int> &d,int x){
	int r=0;
	for(x=min(x+1,(int)d.size()-1);x;x^=x&(-x)){
		//if(x>=d.size() || x<0)cout<<"!!",exit(0);
		r+=d[x];
	}
	return r;
}



int sz[MXN],nfa[MXN];bool vis[MXN];
inline void dfs_sz(int p,int fa){
	sz[p]=1;
	for(int nx:te[p])
		if(nx!=fa && !vis[nx]){
			dfs_sz(nx,p);
			sz[p]+=sz[nx];
		}
}

inline int dfs_rt(int p,int fa,int tot){
	bool f=(sz[p]<<1)>=tot;
	for(int nx:te[p])
		if(nx!=fa && !vis[nx]){
			int tmp=dfs_rt(nx,p,tot);
			if(tmp)return tmp;
			f&=(sz[nx]<<1)<=tot;
		}
	return f?p:0;
}
inline int bld(int p){
	dfs_sz(p,0);
	vis[p=dfs_rt(p,0,sz[p])]=1;
	c[p].resize(sz[p]+2);
	_c[p].resize(sz[p]+2);

	for(int nx:te[p])
		if(!vis[nx]){
			int tmp=bld(nx);
			e[p].push_back(tmp);
			nfa[tmp]=p;
		}
	return p;
}
inline void mod(int x,int y){
	for(int i=x;i;i=nfa[i])mod(c[i],get_dis(i,x),)
	mod(c[x],0,y);
	for(int i=x;nfa[i];i=nfa[i]){
		int tmp=get_dis(nfa[i],x);
		mod(c[nfa[i]],tmp,y);
		mod(_c[i],tmp,y);
	}
}
inline int que(int x,int y){
	int res=pre(c[x],y);
	for(int i=x;nfa[i];i=nfa[i]){
		int tmp=get_dis(x,nfa[i]);
		if(y>=tmp)res+=pre(c[nfa[i]],y-tmp)-pre(_c[i],y-tmp);
	}
	return res;
}


int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",va+i);
	for(int i=1,ts,tt;i<n;i++){
		scanf("%d%d",&ts,&tt);
		te[ts].push_back(tt);
		te[tt].push_back(ts);
	}
	init_lca(1);
	bld(1);
	for(int i=1;i<=n;i++)
		mod(i,va[i]);
	int last=0;
	while(m--){
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		x^=last,y^=last;
		if(x>n || x<0)cout<<"??",exit(0);
		if(op)mod(x,y-va[x]),va[x]=y;
		else printf("%d\n",last=que(x,y));
	}

	return 0;
}

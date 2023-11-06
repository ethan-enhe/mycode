#include <bits/stdc++.h>
#include <vector>
using namespace std;

typedef multiset<int> si;
const int MXN=2e5+5;
int n,m,q,k;
vector<int> g[MXN];
si kni[MXN];
int plc[MXN],frc[MXN];
//{{{ segt
#define ls p<<1
#define rs p<<1|1
#define fa p>>1
si merge(si x,si y){
	si z;
	for(int i:x){
		z.insert(i);
		if(z.size()>k)z.erase(z.begin());
	}
	for(int i:y){
		z.insert(i);
		if(z.size()>k)z.erase(z.begin());
	}
	return z;
}
int ind[MXN];
void build(int p,int l,int r){
	if(l==r){
		ind[l]=p;
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void upd(int p){
	while((p=fa))
		kni[p]=merge(kni[ls],kni[rs]);
}
si que(int p,int l,int r,int ql,int qr){
	if(ql<=l && r<=qr)return kni[p];
	int mid=(l+r)>>1;si res;
	if(ql<=mid)res=merge(res,que(ls,l,mid,ql,qr));
	if(qr>mid)res=merge(res,que(rs,mid+1,r,ql,qr));
	return res;
}
#undef fa
//}}}
//{{{ chain
int sz[MXN],son[MXN],top[MXN],dfn[MXN],dpth[MXN],fa[MXN],dfnc;
void init(int p){
	sz[p]=1;
	for(int nx:g[p])
		if(nx!=fa[p]){
			dpth[nx]=dpth[p]+1;
			fa[nx]=p;
			init(nx);
			sz[p]+=sz[nx];
			if(sz[nx]>sz[son[p]])
				son[p]=nx;
		}
}
void dfs(int p){
	if(!top[p])top[p]=p;
	dfn[p]=++dfnc;
	if(son[p]){
		top[son[p]]=top[p];
		dfs(son[p]);
		for(int nx:g[p])
			if(nx!=fa[p] && nx!=son[p])
				dfs(nx);
	}
}
si que(int x,int y){
	si res;
	while(top[x]!=top[y]){
		if(dpth[top[y]]>dpth[top[x]])swap(x,y);
		res=merge(res,que(1,1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dpth[y]>dpth[x])swap(x,y);
	res=merge(res,que(1,1,n,dfn[y],dfn[x]));
	return res;
}
//}}}
void del(int x){
	kni[ind[dfn[plc[x]]]].erase(frc[x]);
	upd(ind[dfn[plc[x]]]);
}
void ins(int x){
	kni[ind[dfn[plc[x]]]].insert(frc[x]);
	upd(ind[dfn[plc[x]]]);
}



int main() {
#ifndef ONLINE_JUDGE
     freopen("test.in","r",stdin);
    // freopen(".out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	init(1);
	dfs(1);
	build(1,1,n);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",frc+i,plc+i);
		kni[ind[dfn[plc[i]]]].insert(frc[i]);
	}
	scanf("%d%d",&q,&k);
	for(int i=1;i<=n;i++)
		upd(ind[i]);

	while(q--){
		int tp,x,y;
		scanf("%d%d%d",&tp,&x,&y);
		if(tp==1){
			si res=que(x,y);
			if(res.empty())puts("-1");
			else{
				for(auto i=res.rbegin();i!=res.rend();i++)
					printf("%d ",*i);
				putchar('\n');
			}
		}
		else{
			del(x);
			(tp?plc[x]:frc[x])=y;
			ins(x);
		}

	}
    return 0;
}

/*
5  
1 2  
1 3  
2 4  
2 5  
4  
10 1  
6 1  
14 5  
7 3  
5 3  
1 2 3  
1 5 3  
1 4 4  
2 1 4  
1 2 3
*/

#include <bits/stdc++.h>
using namespace std;
const int MXN=1e5+5,LG=17;
int n,m,s;
vector<int> g[MXN];
int anc[MXN][LG+1],dpth[MXN],sz[MXN];
void dfs(int p,int f){
	anc[p][0]=f,dpth[p]=dpth[f]+1,sz[p]=1;
	for(int i=0;anc[p][i];i++)
		anc[p][i+1]=anc[anc[p][i]][i];
	for(int nx:g[p])
		if(nx^f)
			dfs(nx,p);
	sz[f]+=sz[p];
}
inline int jmp(int p,int d){
	for(int i=LG;~i;i--)
		if((d>>i)&1)
			p=anc[p][i];
	return p;
}
inline int lca(int x,int y){
	x=jmp(x,dpth[x]-dpth[y]);
	if(x==y)return x;
	for(int i=LG;~i;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}
int main(){
	scanf("%d",&n);
	for (int i=1; i<n; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,0);
	scanf("%d",&m);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x==y)printf("%d\n",n);
		else{
			if(dpth[y]>dpth[x])swap(x,y);
			int l=lca(x,y),d=dpth[x]+dpth[y]-(dpth[l]<<1);
			if(d&1)
				puts("0");
			else{
				d=(d>>1)-1;
				int tx=jmp(x,d);
				if(anc[tx][0]==l){
					int ty=jmp(y,d);
					printf("%d\n",n-sz[tx]-sz[ty]);
				}
				else printf("%d\n",sz[anc[tx][0]]-sz[tx]);
			}
		}

	}
	return 0;
}


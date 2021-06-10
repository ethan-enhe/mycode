//【模板】2-SAT 问题
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MXN=2e6+5;

vector<int> e[MXN];
int n,m;
bool inst[MXN];
int dfn[MXN],low[MXN],dfnc;
int col[MXN],colc,st[MXN],top;
inline int id(int x,bool y){return x+(y?n:0);}
void dfs(int p){
	dfn[p]=low[p]=++dfnc;
	st[++top]=p;inst[p]=1;
	for(int i=0;i<(int)e[p].size();i++){
		int nx=e[p][i];
		if(!dfn[nx]){
			dfs(nx);
			low[p]=min(low[p],low[nx]);
		}
		else if(inst[nx])low[p]=min(low[p],dfn[nx]);
	}
	if(dfn[p]==low[p]){
		int x;++colc;
		do{
			x=st[top--];
			inst[x]=0;
			col[x]=colc;
		}while(x!=p);
	}
}


int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int x,y,z,w;
		scanf("%d%d%d%d",&x,&y,&z,&w);
		e[id(x,y)].pb(id(z,!w));
		e[id(z,w)].pb(id(x,!y));
	}
	for(int i=1;i<=n<<1;i++)
		if(!dfn[i])
			dfs(i);
	for(int i=1;i<=n;i++)
		if(col[id(i,0)]==col[id(i,1)])
			return printf("IMPOSSIBLE"),0;
	printf("POSSIBLE\n");
	for(int i=1;i<=n;i++)
		printf("%d ",col[id(i,0)]<col[id(i,1)]);
	return 0;
}

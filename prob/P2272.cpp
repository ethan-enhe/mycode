#include <bits/stdc++.h>
using namespace std;
const int MXN=1e5+5;
int n,m,P;
vector<int> g[MXN];
set<int> d[MXN];
int dfn[MXN],low[MXN],dfnc;
bool instk[MXN];
stack<int> stk;
int sz[MXN],col[MXN],sccc;
void tj(int p){
	dfn[p]=low[p]=++dfnc;
	stk.push(p),instk[p]=1;
	for(int nx:g[p]){
		if(!dfn[nx]){
			tj(nx);
			low[p]=min(low[p],low[nx]);
		}
		else if(instk[nx])low[p]=min(low[p],dfn[nx]);
	}
	if(dfn[p]==low[p]){
		int x;
		++sccc;
		do{
			instk[x=stk.top()]=0;stk.pop();
			col[x]=sccc;
			++sz[sccc];
		}while(x!=p);
	}
}
#define fi first
#define se second
typedef pair<int,int> pi;
void add(pi &x,pi y){
	if(y.fi>x.fi)
		x=y;
	else if(y.fi==x.fi)
		x.se=(x.se+y.se)%P;
}
pi dp[MXN],ans;
pi cal(int p){
	if(!dp[p].fi){
		for(int nx:d[p])
			add(dp[p],cal(nx));
		dp[p].fi+=sz[p];
	}
	return dp[p];
}

int main(){
	scanf("%d%d%d",&n,&m,&P);
	while(m--){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tj(i);
	for(int i=1;i<=n;i++)
		for(int j:g[i])
			if(col[i]!=col[j])
				d[col[i]].insert(col[j]);
	fill(dp+1,dp+1+n,pi{0,1});
	for(int i=1;i<=sccc;i++)
		add(ans,cal(i));
	printf("%d\n%d",ans.fi,ans.se);

	return 0;
}

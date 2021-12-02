#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int MXN=5e5+5,LG=19;
int n,q,rt;
int fa[MXN][LG+1],d[MXN],h[MXN],top[MXN];
vector<int> anc[MXN],son[MXN],g[MXN];
typedef unsigned int ui;
ui s;
inline ui get(ui x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}

void dfs(int p){
	son[p].push_back(0);
	for(int nx:g[p]){
		d[nx]=d[p]+1;
		dfs(nx);
		if(h[nx]>h[son[p][0]])
			son[p][0]=nx;
	}
	h[p]=h[son[p][0]]+1;
}
void dfs2(int p){
	if(top[p]==p){
		anc[p].push_back(p);
#define nxfa fa[anc[p][anc[p].size()-1]][0]
#define nxson son[son[p][son[p].size()-1]][0]
		while(nxson)son[p].push_back(nxson);
		while(nxfa && (int)anc[p].size()<=h[p])anc[p].push_back(nxfa);
		//cerr<<p<<" "<<son[p].size()<<" "<<anc[p].size()<<" "<<h[p]<<endl;
	}
	for(int i=1;(1<<i)<=d[p];i++)
		fa[p][i]=fa[fa[p][i-1]][i-1];
	for(int nx:g[p]){
		top[nx]=(son[p][0]==nx?top[p]:nx);
		dfs2(nx);
	}
}
int que(int x,int y){
	if(!y)return x;
	int lg=log2(y);
	y-=d[x];
	x=top[fa[x][lg]];
	y+=d[x];
	if(y>=0)x=anc[x][y];
	else x=son[x][-y-1];
	return x;
}

int main(){
	scanf("%d%d%d",&n,&q,&s);
	for(int i=1;i<=n;i++){
		scanf("%d",&fa[i][0]);
		if(!fa[i][0])rt=i;
		g[fa[i][0]].push_back(i);
	}
	d[rt]=1;
	dfs(rt);
	top[rt]=rt;
	son[0].push_back(0);
	dfs2(rt);
	int last=0;long long ans=0;
	for(int i=1;i<=q;i++){
		int cx=(get(s)^last)%n+1;
		int cy=(get(s)^last)%d[cx];
		last=que(cx,cy);
		ans^=(long long)i*last;
	}
	printf("%lld",ans);
	return 0;
}

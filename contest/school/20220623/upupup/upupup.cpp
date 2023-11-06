#include<bits/stdc++.h>
using namespace std;
const int MXN=3e5+5,LG=20;

int fa[MXN][LG],dpth[MXN],dfn[MXN],dfnc;
vector<int> g[MXN];

void addson(int x,int y){
	//cerr<<x<<"->"<<y<<endl;
	fa[y][0]=x,dpth[y]=dpth[x]+1;
	g[x].push_back(y);
	for(int i=1;i<LG;i++)
		fa[y][i]=fa[fa[y][i-1]][i-1];
}
int lca(int x,int y){
	if(dpth[x]<dpth[y])swap(x,y);
	int tmp=dpth[x]-dpth[y];
	for(int i=0;i<LG;i++)
		if((tmp>>i)&1)
			x=fa[x][i];
	if(x==y)return x;
	for(int i=LG-1;~i;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
void dfs(int p){
	dfn[p]=++dfnc;
	for(int nx:g[p])
		dfs(nx);
}



int n,m;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("upupup.in","r",stdin);
	freopen("upupup.out","w",stdout);
	cin>>n;
	for(int i=1,c,l,x;i<=n;i++){
		cin>>c;
		if(c){
			cin>>l;
			while(--c){
				cin>>x;
				l=lca(l,x);
			}
			addson(l,i);
		}
		else addson(0,i);
	}
	dfs(0);
	cin>>m;
	while(m--){
		int c;
		cin>>c;
		vector<int> q(c);
		for(int &x:q)cin>>x;
		sort(q.begin(),q.end(),[](int x,int y){return dfn[x]<dfn[y];});
		int last=0,ans=0;
		for(int &x:q){
			ans+=dpth[x]-dpth[lca(x,last)];
			last=x;
		}
		cout<<ans<<'\n';
	}

	return 0;
}

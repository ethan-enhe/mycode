#include<bits/stdc++.h>
using namespace std;
const int MXN=1e6+5;
vector<int> e[MXN];
inline void ae(int ts,int tt){
	e[ts].push_back(tt);
	e[tt].push_back(ts);
}
int n,col[MXN];
inline void dfs(int p){
	for(int nx:e[p])
		if(col[nx]==-1){
			col[nx]=!col[p];
			dfs(nx);
		}
}
int main(){
	scanf("%d",&n);
	for(int i=1,ts,tt;i<=n;i++){
		scanf("%d%d",&ts,&tt);
		ae(ts,tt);
		ae(i<<1,(i<<1)-1);
	}
	memset(col,-1,sizeof(col));
	for(int i=1;i<=(n<<1);i++){
		if(col[i]==-1)col[i]=1,dfs(i);
		putchar('X'+col[i]);
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MXN=100;
int n,ans,cnt;
bool vis[MXN];
bool ok[MXN][MXN];
inline void mrk(int x){
	vis[x]=1;
	for(int nx=1;nx<=n;nx++)
		if(ok[x][nx] && !vis[nx])
			mrk(nx);
}
inline void dfs(int x,int y){
	if(y==x)
		y=1,x++;
	if(x==n+1){
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
			if(!vis[i]){
				mrk(i);
				ans++;
			}
		cnt++;
		return;
	}
	ok[x][y]=ok[y][x]=0;
	dfs(x,y+1);
	ok[x][y]=ok[y][x]=1;
	dfs(x,y+1);
}
int main(){
	cin>>n;
	dfs(1,1);
	printf("%.10lf",(double)ans/cnt);


	return 0;
}

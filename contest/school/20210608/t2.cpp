#include<bits/stdc++.h>
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

const int MXN=25;
int t,n,m,k,ans;
bool vis[MXN][MXN];

inline bool chk4(int x,int y){return vis[x][y]||vis[x+1][y]||vis[x][y+1]||vis[x+1][y+1];}
inline void mark4(int x,int y,bool z){vis[x][y]=vis[x+1][y]=vis[x][y+1]=vis[x+1][y+1]=z;}
inline void dfs(int x,int y,int cnt){
	while(y==m && x!=n)y=1,x++;
	if(x==n){
		ans=max(ans,cnt);
		return;
	}
	dfs(x,y+1,cnt);
	if(!chk4(x,y)){
		mark4(x,y,1);
		if(!chk4(x+2,y)){
			mark4(x+2,y,1);
			dfs(x,y+1,cnt+1);
			mark4(x+2,y,0);
		}
		if(!chk4(x,y+2)){
			mark4(x,y+2,1);
			dfs(x,y+1,cnt+1);
			mark4(x,y+2,0);
		}
		mark4(x,y,0);
	}
}

int main(){
	read(t);
	while(t--){
		memset(vis,0,sizeof(vis));
		read(n),read(m),read(k);
		ans=0;
		while(k--){
			int tx,ty;
			read(tx),read(ty);
			vis[tx][ty]=1;
		}
		for(int i=1;i<=n;i++)vis[i][m+1]=1;
		for(int i=1;i<=m;i++)vis[n+1][i]=1;
		dfs(1,1,0);
		printf("%d\n",ans);

	}
	return 0;
}

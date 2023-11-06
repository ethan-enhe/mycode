#include<bits/stdc++.h>
using namespace std;
const int MXN=305;
const int go[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
bool obs[MXN][MXN][4];
int n,m,Q,k1,k2,sx,sy,dis[MXN][MXN];

struct node{int x,y;};
queue<node> q;
inline void bfs(){
	memset(dis,-1,sizeof(dis));
	q.push({sx,sy});
	dis[sx][sy]=1;
	while(!q.empty()){
		node p=q.front();q.pop();
		for(int i=0;i<4;i++)
			if(!obs[p.x][p.y][i]){
				node nx={p.x+go[i][0],p.y+go[i][1]};
				if(nx.x<=n && nx.x>0 && nx.y<=m && nx.y>0 && dis[nx.x][nx.y]==-1){
					dis[nx.x][nx.y]=dis[p.x][p.y]+1;
					q.push(nx);
				}
			}
	}
}
int cnt[MXN*MXN];
bool vis[MXN][MXN];
inline bool chk(int qx,int qy){
	memset(cnt,0,sizeof(cnt));
	memset(vis,0,sizeof(vis));
	q.push({qx,qy});
	vis[qx][qy]=1;
	while(!q.empty()){
		node p=q.front();q.pop();
		for(int i=0;i<4;i++)
			if(!obs[p.x][p.y][i]){
				node nx={p.x+go[i][0],p.y+go[i][1]};
				if(nx.x<=n && nx.x>0 && nx.y<=m && nx.y>0 && dis[nx.x][nx.y]==dis[p.x][p.y]-1){
					cnt[dis[p.x][p.y]]++;
					if(!vis[nx.x][nx.y]){
						vis[nx.x][nx.y]=1;
						q.push(nx);
					}
				}
			}
	}
	for(int i=2;i<=dis[qx][qy];i++)
		if(cnt[i]<=1)return 1;
	return 0;
}
inline void sub5(){

	scanf("%d%d%d",&sx,&sy,&Q);
	while(Q--){
		int tx,ty;
		scanf("%d%d",&tx,&ty);
		printf("%d\n",(tx==sx) || (ty==sy));
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&k1,&k2);
	if(!k1 && !k2){
		sub5();
		return 0;
	}
	for(int i=1,tx,ty;i<=k1;i++){
		scanf("%d%d",&tx,&ty);
		obs[tx][ty][0]=obs[tx][ty+1][2]=1;
	}
	for(int i=1,tx,ty;i<=k2;i++){
		scanf("%d%d",&tx,&ty);
		obs[tx][ty][1]=obs[tx+1][ty][3]=1;
	}
	scanf("%d%d%d",&sx,&sy,&Q);
	bfs();
	/*
	for(int i=1;i<=n;i++,cout<<endl)
		for(int j=1;j<=m;j++)
			cout<<dis[i][j]<<" ";
			*/
	while(Q--){
		int tx,ty;
		scanf("%d%d",&tx,&ty);
		printf("%d\n",(int)chk(tx,ty));
	}




	return 0;
}

#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int INF=1e8;
const int MXN=1.5e5+5;

struct edge{
	int ter,cap,cost,opp;
	edge(int ter,int cap,int cost,int opp):ter(ter),cap(cap),cost(cost),opp(opp){}
};
vector<edge> e[MXN];
inline void ae(int ts,int tt,int cap,int cost){
	e[ts].pb(edge(tt,cap,cost,e[tt].size()));
	e[tt].pb(edge(ts,0,-cost,e[ts].size()-1));
}

queue<int> q;
bool vis[MXN];
int dis[MXN],cure[MXN];
inline bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	q.push(1);
	while(!q.empty()){
		int p=q.front();q.pop();
		vis[p]=0;
		for(int i=0;i<(int)e[p].size();i++){
			if(e[p][i].cap){
				int nx=e[p][i].ter,nw=dis[p]+e[p][i].cost;
				if(dis[nx]>nw){
					dis[nx]=nw;
					if(!vis[nx]){
						vis[nx]=1;
						q.push(nx);
					}
				}
			}
		}
	}
	return dis[2]<INF;
}
int dfs(int p,int fli){
	if(p==2)return fli;
	vis[p]=1;
	int flo=0,delt;
	for(int &i=cure[p];i<(int)e[p].size();i++){
		edge &nx=e[p][i];
		if(nx.cap && !vis[nx.ter] && dis[nx.ter]==dis[p]+nx.cost){
			delt=dfs(nx.ter,min(fli-flo,nx.cap));
			if(delt){
				flo+=delt;
				nx.cap-=delt;
				e[nx.ter][nx.opp].cap+=delt;
				if(flo==fli)break;
			}
			else dis[nx.ter]=-1;
		}
	}
	vis[p]=0;
	return flo;
}

int main(){
	int res=0;
	while(spfa()){
		memset(cure,0,sizeof(cure));
		res+=dis[2]*dfs(1,INF);
	}
	printf("%d",res);
	return 0;
}

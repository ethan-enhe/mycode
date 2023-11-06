#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
struct edge{
	int ter,cap,cost,opp;
	inline edge(int ter,int cap,int cost,int opp):ter(ter),cap(cap),cost(cost),opp(opp){}
};
template<const int MXN>
struct mcmf{
	queue<int> q;
	bool vis[MXN];
	vector<edge> e[MXN];
	int fs,ft,dis[MXN],cure[MXN];

	inline mcmf(){memset(vis,0,sizeof(vis));}
	inline void adde(int ts,int tt,int tcap,int tcost=0){
		e[ts].push_back(edge(tt,tcap,tcost,e[tt].size()));
		e[tt].push_back(edge(ts,0,-tcost,e[ts].size()-1));
	}
	inline bool spfa(){
		memset(dis,0x3f,sizeof(dis));
		dis[fs]=0;q.push(fs);
		while(!q.empty()){
			int p=q.front();q.pop();
			vis[p]=0;
			for(int i=0;i<(int)e[p].size();i++){
				edge &nx=e[p][i];int nd=dis[p]+nx.cost;
				if(dis[nx.ter]<=nd || !nx.cap)continue;
				dis[nx.ter]=nd;
				if(!vis[nx.ter]){
					vis[nx.ter]=1;
					q.push(nx.ter);
				}
			}
		}
		return dis[ft]<INF;
	}
	inline int dinic(int p,int fin){
		if(p==ft)return fin;
		vis[p]=1;
		int fout=0;
		for(int &i=cure[p];i<(int)e[p].size();i++){
			edge &nx=e[p][i];
			if(dis[nx.ter]!=dis[p]+nx.cost || vis[nx.ter] || !nx.cap)continue;
			int delt=dinic(nx.ter,min(fin-fout,nx.cap));
			if(delt){
				nx.cap-=delt;
				e[nx.ter][nx.opp].cap+=delt;
				fout+=delt;
				if(fin==fout)break;
			}
			else dis[nx.ter]=-INF;
		}
		return vis[p]=0,fout;
	}
	inline pair<int,int> run(int ts,int tt){
		fs=ts,ft=tt;
		pair<int,int> res;
		while(spfa()){
			memset(cure,0,sizeof(cure));
			int tmp=dinic(fs,INF);
			res.first+=tmp,res.second+=tmp*dis[ft];
		}
		return res;
	}
};
const int go[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
const int MXN=305;
int n,m,sz,k;
char str[MXN][MXN];
mcmf<(MXN*MXN<<1)> f;
inline int id(int x,int y,bool f){
	int res=(x-1)*m+y+2;
	return res+(f?sz:0);
}
inline pair<int,int> gcoor(int id){
	id-=2;
	if(id>sz)id-=sz;
	return make_pair((id-1)/m+1,(id-1)%m+1);
}
inline void dfsprt(int x,int y,int num){
	if(str[x][y]=='S'){
		printf("%d\n%d %d\n",num,x,y);
		return;
	}
	int tid=id(x,y,0);
	for(edge &nx:f.e[tid])
		if(nx.cap==1){
			pair<int,int> tmp=gcoor(nx.ter);
			dfsprt(tmp.first,tmp.second,num+1);
			printf("%d %d\n",x,y);
			return;
		}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	sz=n*m;
	for(int i=1;i<=n;i++)
		scanf("%s",str[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(str[i][j]!='X'){
				f.adde(id(i,j,0),id(i,j,1),1);
				for(int l=0;l<4;l++){
					int ni=i+go[l][0],nj=j+go[l][1];
					if(ni>0 && ni<=n && nj>0 && nj<=m && str[ni][nj]!='X')
						f.adde(id(i,j,1),id(ni,nj,0),1);
				}
			}
			if(str[i][j]=='S')f.adde(1,id(i,j,0),1);
			if(str[i][j]=='T')f.adde(id(i,j,1),2,1);
		}
	f.run(1,2);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(str[i][j]=='T')
				dfsprt(i,j,1);

	return 0;
}

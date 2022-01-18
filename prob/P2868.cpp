#include<bits/stdc++.h>
using namespace std;
const int MXN=1005;
const double EPS=1e-7;
int n,m,arr[MXN];
struct edge{int v,t;};
vector<edge> g[MXN];

int len[MXN];
double dis[MXN];
queue<int> q;
bool chk(double x){
	while(!q.empty())q.pop();
	for(int i=1;i<=n;i++){
		dis[i]=len[i]=0;
		q.push(i);
	}
	while(!q.empty()){
		int p=q.front();q.pop();
		for(edge &nx:g[p]){
			double nd=dis[p]+x*nx.t-arr[nx.v];
			if(dis[nx.v]>nd+EPS){
				dis[nx.v]=nd+EPS;
				if((len[nx.v]=len[p]+1)>n+10)
					return 1;
				q.push(nx.v);
			}
		}
	}
	return 0;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",arr+i);
	while(m--){
		int u,v,t;
		scanf("%d%d%d",&u,&v,&t);
		g[u].push_back({v,t});
	}
	double l=0,r=MXN;
	for(int i=1;i<=18;i++){
		double mid=(l+r)/2;
		if(chk(mid))l=mid;
		else r=mid;
	}
	printf("%.2f",l);
	return 0;
}

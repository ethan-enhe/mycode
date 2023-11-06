#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
typedef pair<int,int> pi;

const int MXN=5e4+5;
const int MXM=1e5+5;
bool inq[MXN];
int n,m,dis[MXN];
queue<int> q;
vector<pi> e[MXN];
struct edge{int ts,tt,ta,tb;}arr[MXM];
inline bool cmp(const edge &a,const edge &b){return a.ta<b.ta;}

inline int spfa(const edge &x){
	e[x.ts].pb(mp(x.tt,x.tb));
	e[x.tt].pb(mp(x.ts,x.tb));
	inq[x.ts]=inq[x.tt]=1;
	q.push(x.ts),q.push(x.tt);
	while(!q.empty()){
		int p=q.front();q.pop();
		inq[p]=0;
		for(int i=0;i<(int)e[p].size();i++){
			int np=e[p][i].fi,nd=max(dis[p],e[p][i].se);
			if(dis[np]>nd){
				dis[np]=nd;
				if(!inq[np])
					inq[np]=1,q.push(np);
			}
		}
	}
	return dis[n];
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d%d",&arr[i].ts,&arr[i].tt,&arr[i].ta,&arr[i].tb);
	sort(arr+1,arr+1+m,cmp);

	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	int ans=1e9;
	for(int i=1;i<=m;i++)
		ans=min(ans,arr[i].ta+spfa(arr[i]));
	printf("%d",ans>MXM?-1:ans);
	return 0;
}

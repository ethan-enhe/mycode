#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
constexpr ll MXN=605,INF=1e6;
ll t,n,m,arr[MXN][MXN],brr[MXN][MXN];
ll dis[MXN],len[MXN];
queue<ll> q;
vector<pi> g[MXN];
// y<=x+z
void lim(ll x,ll y,ll z){g[x].push_back({y,z});}

int main(int argc, char *argv[]){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		//偶数行，奇数列shift
		for(int i=2;i<=n;i++)
			for(int j=2;j<=m;j++){
				scanf("%lld",&arr[i][j]);
				brr[i][j]=arr[i][j]-brr[i-1][j]-brr[i][j-1]-brr[i-1][j-1];
				ll s=i,t=n+j;
				if((i+j)&1)swap(s,t);
				lim(s,t,brr[i][j]);
				lim(t,s,INF-brr[i][j]);
			}
		for(int i=1;i<=n;i++,putchar('\n'))
			for(int j=1;j<=m;j++){
				ll line=(j^i^1)&1?-1:1,col=(i^j)&1?-1:1;
				printf("%5lld",brr[i][j]);
				// printf("%2lld,%2lld ",line,col);
			}
		memset(dis,0x3f,sizeof(dis));
		dis[0]=0;q.push(0);
		bool f=1;
		while(!q.empty()){
			ll p=q.front();q.pop();
			for(pi &nx:g[p]){
				ll nd=dis[p]+nx.second;
				if(dis[nx.first]>nd){
					if((len[nx.first]=len[p]+1)>n+m){
						f=0;
						break;
					}
					dis[nx.first]=nd;
					q.push(nx.first);
				}
			}
		}
		if(!f){
			while(!q.empty())q.pop();
			puts("NO");
			continue;
		}
	}
	
	return 0;
}

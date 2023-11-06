#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1e18,MXN=500+5,MXSZ=MXN*MXN;
struct p{ll x,y;}arr[MXSZ];
struct node{ll l,r,u,d,ls,rs;}t[MXSZ];
ll n,m,cnt;
char str[MXN];
inline ll sq(ll x){return x*x;}
inline ll dis(ll x,ll y){return sq(arr[x].x-arr[y].x)+sq(arr[x].y-arr[y].y);}
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++){
		scanf("%s",str+1);
		for(ll j=1;j<=m;j++)
			if(str[j]=='1')
				arr[++cnt]={i,j};
	}
	ll ans=0;
	for(ll i=1;i<=cnt;i++){
		ll tmp=INF;
		for(ll j=1;j<=cnt;j++)
			if(j!=i)
				tmp=min(tmp,dis(i,j));
		ans+=tmp;
	}
	printf("%lld",ans);


	return 0;
}

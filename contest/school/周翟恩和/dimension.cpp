#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=int;
using pi=pair<ll,ll>;
const ll MXL=12,MXN=10;
const ll SZ=2e7,LG=30;
const ll P=1e9+7;
ll n,m,k,p;
ll tot,ltot,rtot;

ll rt[MXN][MXN][MXN],arr[MXN][MXN][MXN];
struct node{
	ll cnt,son[2];
}t[SZ];
ll nodec;

void ins(ll &p,ll x){
	if(!p)p=++nodec;
	for(ll i=LG-1,u=p;~i;i--){
		ll &v=t[u].son[(x>>i)&1];
		if(!v)v=++nodec;
		++t[u=v].cnt;
	}
}
ll getlower(ll p,ll x,ll y){
	ll ans=0;
	for(ll i=LG-1;~i;i--){
		bool f=(x>>i)&1;
		if((y>>i)&1)ans+=t[t[p].son[f]].cnt,p=t[p].son[!f];
		else p=t[p].son[f];
	}
	return ans+t[p].cnt;
}

void dfs(ll x,ll y,ll z,ll v,ll step){
	v^=arr[x][y][z];
	if(!step){
		ins(rt[x][y][z],v);
		return;
	}
	if(x!=n)dfs(x+1,y,z,v,step-1);
	if(y!=m)dfs(x,y+1,z,v,step-1);
	if(z!=k)dfs(x,y,z+1,v,step-1);
}
ll ans;
void qry(ll x,ll y,ll z,ll v,ll step){
	if(!step){
		ans=(ans+getlower(rt[x][y][z],v,p))%P;
		return;
	}
	v^=arr[x][y][z];
	if(x!=1)qry(x-1,y,z,v,step-1);
	if(y!=1)qry(x,y-1,z,v,step-1);
	if(z!=1)qry(x,y,z-1,v,step-1);
}


int main(){
	freopen("dimension.in","r",stdin);
	freopen("dimension.out","w",stdout);
	//cerr<<(sizeof(t)>>20);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>k>>p;
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			for(ll l=1;l<=k;l++)
				cin>>arr[i][j][l];
	tot=n+m+k-3;
	ltot=min(tot,MXL);
	rtot=tot-ltot;
	dfs(1,1,1,0,ltot);
	qry(n,m,k,0,rtot);
	cout<<ans;

	return 0;
}

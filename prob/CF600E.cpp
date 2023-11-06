#include <bits/stdc++.h>
typedef long long ll;
const ll MXN=1e5+5;
ll n,arr[MXN],ans[MXN];

std::vector<ll> g[MXN];
ll sz[MXN],son[MXN];
void isz(ll p,ll fa){
	sz[p]=1;
	for(ll nx:g[p])
		if(nx!=fa){
			isz(nx,p);
			sz[p]+=sz[nx];
			if(sz[nx]>sz[son[p]])son[p]=nx;
		}
}

ll cnt[MXN],stk[MXN],mx,sum,top;
void ins(ll x){
	++cnt[stk[++top]=x];
	if(cnt[x]>mx){
		mx=cnt[x];
		sum=x;
	}
	else if(cnt[x]==mx)sum+=x;
}
void clr(){
	while(top)
		cnt[stk[top--]]=0;
	mx=sum=0;
}
void inss(ll p,ll fa){
	ins(arr[p]);
	for(ll nx:g[p])
		if(nx!=fa)
			inss(nx,p);
}

void dfs(ll p,ll fa){
	if(son[p]){
		for(ll nx:g[p])
			if(nx!=fa && nx!=son[p]){
				dfs(nx,p);
				clr();
			}
		dfs(son[p],p);
		for(ll nx:g[p])
			if(nx!=fa && nx!=son[p])
				inss(nx,p);
	}
	ins(arr[p]);
	ans[p]=sum;
}

int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
		scanf("%lld",arr+i);
	for(ll i=1,u,v;i<n;i++){
		scanf("%lld%lld",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	isz(1,0);
	dfs(1,0);
	for(int i=1;i<=n;i++)
		printf("%lld ",ans[i]);


	return 0;
}

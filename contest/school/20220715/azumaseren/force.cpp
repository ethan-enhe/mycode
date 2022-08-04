#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll MXN=105,P=1e9+7;
bool g[MXN][MXN],f[MXN][MXN],h[MXN][MXN];
ll n,m,cnt;
bool chk(){
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++)
			h[i][j]=f[i][j]=g[i][j];
	}
	for(ll k=m+1;k<=n;k++)
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=n;j++){
				f[i][j]|=f[i][k]&f[k][j];
			}
	for(ll k=1;k<=n;k++)
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=n;j++){
				h[i][j]|=h[i][k]&h[k][j];
			}
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++)
			if(f[i][j]!=h[i][j]){
				return 0;
			}
	return 1;

}
void dfs(ll i,ll j){
	if(j>=i)j=1,++i;
	if(i==n+1){
		cnt+=chk();
		return;
	}
	g[i][j]=g[j][i]=0;
	dfs(i,j+1);
	g[i][j]=g[j][i]=1;
	dfs(i,j+1);
}
int main(){
	cin>>n>>m;
	for(ll i=1;i<=n;i++)
		g[i][i]=1;
	dfs(1,1);
	cout<<cnt;
	return 0;
}


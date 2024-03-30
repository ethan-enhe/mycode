#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const ll MXN=3e3+5;
const ll INF=1e9;
char str[MXN][MXN];
ll sum[MXN][MXN];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n,m;
	cin>>n>>m;
	ll x=-1,y=-1;
	for(ll i=1;i<=n;i++){
		cin>>(str[i]+1);
		for(ll j=1;j<=m;j++)
			if(str[i][j]=='S')x=i,y=j;
		str[i][0]=str[i][m+1]='#';
	}
	for(ll j=0;j<=m+1;j++)
		str[0][j]=str[n+1][j]='#';

	bool ans=0;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			sum[i][j]=sum[i][j-1]+(str[i][j]=='#');
		}
	}
	for(ll j=1;j<=m;j++){
		if(y==j)continue;
		ll up=x,down=x;
		int mxup=INF,mxdown=0;
		while(str[up][j]!='#' && str[up][y]!='#'){
			if(sum[up][j]==sum[up][y])mxup=up;
			--up;
		}
		while(str[down][j]!='#' && str[down][y]!='#'){
			if(sum[down][j]==sum[down][y])mxdown=down;
			++down;
		}
		if(mxdown>mxup){
			ans=1;
		}
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			sum[i][j]=sum[i-1][j]+(str[i][j]=='#');
		}
	}
	for(ll j=1;j<=n;j++){
		if(x==j)continue;
		ll up=y,down=y;
		int mxup=INF,mxdown=0;
		while(str[j][up]!='#' && str[x][up]!='#'){
			if(sum[j][up]==sum[x][up])mxup=up;
			--up;
		}
		while(str[j][down]!='#' && str[x][down]!='#'){
			if(sum[j][down]==sum[x][down])mxdown=down;
			++down;
		}
		//{w;		cerr<<j<<" "<<down<<" "<<mxup<<endl;
		if(mxdown>mxup){
			ans=1;
		}
	}
	cout<<(ans?"Yes":"No");
	return 0;
}

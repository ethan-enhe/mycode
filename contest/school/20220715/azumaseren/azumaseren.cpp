#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll MXN=105,P=1e9+7;
ll dp[MXN][MXN],f[3][MXN][MXN];
ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
int main(){
	f[0][0][0]=1;
	for(ll i=1;i<MXN;i++){
			//if(i==4)break;
		for(ll j=0;j<=i;j++){
			dp[i][j]=qpow(2,i*(i-1)>>1);
			for(ll k=1;k<=j;k++)
				dp[i][j]=(dp[i][j]-f[2][i-1][j-1])%P;
			for(ll x=i;x<MXN;x++)
				for(ll y=j;y<=x;y++){
					f[1][x][y]=(f[1][x][y]+f[0][x-i][y-j]*dp[i][j])%P;
					f[2][x][y]=(f[2][x][y]+f[1][x-i][y-j]*dp[i][j])%P;
					f[2][x][y]=(f[2][x][y]+f[2][x-i][y-j]*dp[i][j])%P;
				}
			//cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
		}
	}
	ll x,y;
	cin>>x>>y;
	cout<<dp[x][y];
	return 0;
}

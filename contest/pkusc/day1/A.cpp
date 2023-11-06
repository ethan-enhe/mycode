#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const ll P=998244353;
const ll MXN=1200,MXM=105;

ll n,m,w[MXM];
// 表示为 dp[i][j]=nxw[i][m+1]+\sum_k dp[i][k]*nxw[i][k-j]
ll nxw[MXN][MXM];
ll dp[MXN][MXN];

ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}

ll mod(ll x){return x<P?x:x-P;};

// 把自己那项消掉
void del_self(ll *x){
	ll c=qpow(mod(1+P-x[0]),P-2);
	for(ll i=1;i<=m+1;i++)
		x[i]=x[i]*c%P;
	x[0]=0;
}


ll getw(ll x,ll y){
	assert(abs(y-x)<=m);
	if(y)return w[m+y-x];
	else{
		ll r=0;
		for(ll i=-m;i<=y-x;i++)
			r=mod(r+w[m+i]);
		return r;
	}
}

ll tmp[MXN];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(ll i=-m,x;i<=m;i++){
		cin>>x;
		w[i+m]=x*qpow(100000000,P-2)%P;
	}

	for(ll i=0;i<=n;i++){
		for(ll j=0;j<=m;j++)
			nxw[i][j]=getw(i,i+j);
		nxw[i][m+1]=1;
		for(ll j=max(0ll,i-m);j<i;j++)
			tmp[j]=getw(i,j);
		for(ll j=max(0ll,i-m);j<i;j++){
			nxw[i][m+1]=(nxw[i][m+1]+nxw[j][m+1]*tmp[j])%P;
			for(ll k=0;k<=m;k++){
				if(j+k>=i)
					nxw[i][j+k-i]=(nxw[i][j+k-i]+nxw[j][k]*tmp[j])%P;
				else tmp[j+k]=(tmp[j+k]+nxw[j][k]*tmp[j])%P;
			}
		}
		del_self(nxw[i]);
	}
	for(ll i=n-1;~i;i--){
		for(ll j=i+1;j<MXN;j++)
			dp[i][j]=dp[j][i];
		for(ll j=i;~j;j--){
			for(ll k=1;k<=m;k++)
				dp[i][j]=(dp[i][j]+dp[i][j+k]*nxw[j][k])%P;
			dp[i][j]=(dp[i][j]+nxw[j][m+1])%P;
		}
	}
	cout<<dp[0][0];

	return 0;
}

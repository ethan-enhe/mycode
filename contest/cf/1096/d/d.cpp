#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;

const ll INF=1e18;
const ll P=1e9+7;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=1e6+5;

ll n,m,k;
ll arr[MXN],dp[MXN][4];
char str[MXN];
inline void solve(){
	scanf("%lld %s",&n,str+1);
	for(int i=1;i<=n;i++)scanf("%lld",arr+i);
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<4;j++){
			int nj=j+(str[i+1]=="hard"[j]);
			if(nj<4)dp[i+1][nj]=min(dp[i+1][nj],dp[i][j]);
			dp[i+1][j]=min(dp[i+1][j],dp[i][j]+arr[i+1]);
		}
	printf("%lld",min(min(dp[n][0],dp[n][1]),min(dp[n][2],dp[n][3])));
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

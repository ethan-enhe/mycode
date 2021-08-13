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
const ll P=998244353;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=1e3+5;

ll n,m,k;
ll dp[MXN][MXN<<1][4];
#define gd(x,y) (((x)>>(y))&1)
inline void solve(){
	dp[0][0][0]=1;
	scanf("%lld%lld",&n,&k);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=k;j++)
			for(int l=0;l<4;l++)
				if(dp[i][j][l]){
					for(int nx=0;nx<4;nx++){
						ll nj=j;
						if(!i)nj+=1+(gd(nx,0)!=gd(nx,1));
						else{
							if(gd(nx,0)==gd(nx,1)){
								if(gd(nx,0)!=gd(l,0) && gd(nx,1)!=gd(l,1))
									nj++;
							}
							else nj+=(gd(nx,0)!=gd(l,0))+(gd(nx,1)!=gd(l,1));
						}
						dp[i+1][nj][nx]=mod(dp[i+1][nj][nx]+dp[i][j][l]);
					}
				}
	ll ans=0;
	for(int i=0;i<4;i++)
		ans=mod(ans+dp[n][k][i]);
	printf("%lld\n",ans);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

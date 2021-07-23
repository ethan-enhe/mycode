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
char s[MXN],t[MXN];
ll dp[MXN];
inline void solve(){
	cin>>(s+1)>>(t+1);
	n=strlen(s+1),m=strlen(t+1);
	s[n+1]=1,t[m+1]=0;
	for(int i=1;i<=n;i++){
		dp[i]=s[i]==t[1];
		dp[i]=max(dp[i],dp[i-1]+(s[i]==t[dp[i-1]+1]));
		dp[i]=max(dp[i],dp[i-3]+(s[i]==t[dp[i-3]+1]));
	}
	cout<<dp[n];
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll tq;cin>>tq;while(tq--)
	solve();
	return 0;
}

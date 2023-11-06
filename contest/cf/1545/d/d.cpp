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


const ll MXN=1e3+5;

ll n,m,k;
ll modt,delt;
ll arr[MXN][MXN],s[MXN];
bool vis[MXN];
ll cnt[(int)1e6+5];
inline ll chk(ll x){return s[x-1]+s[x+1]-(s[x]<<1);}
inline void solve(){
	scanf("%lld%lld",&m,&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%lld",&arr[i][j]);
			s[i]+=arr[i][j];
		}
	modt=0;
	for(int i=3;i<n-1;i++)
		if(chk(i-1) && chk(i) && chk(i+1)){
			modt=i;
			delt=chk(i)>>1;
			break;
		}
	if(modt){
		for(int i=1;i<=m;i++){
			arr[modt][i]+=delt;
			for(int j=1;j<=m;j++)cnt[arr[modt-1][j]]++,vis[j]=0;
			bool g=1;
			for(int j=1;j<=m;j++){
				bool f=0;
				for(int k=1;k<=m;k++)
					if(!vis[k] && cnt[(arr[modt][j]<<1)-arr[modt+1][j]]){
						cnt[(arr[modt][j]<<1)-arr[modt+1][j]]--;
						vis[k]=1;
						f=1;
						break;
					}
				if(!f){
					g=0;
					break;
				}
			}
			if(g){
				printf("%lld %lld",modt,arr[modt][i]);
				return;
			}
			for(int j=1;j<=m;j++)cnt[arr[modt-1][j]]=0;
			arr[modt][i]-=delt;
		}

	}
	else{
		if(!chk(2)){
			modt=1+!chk(3);
			delt=2*s[modt+1]-s[modt+2];
		}
		else if(!chk(n-1)){
			modt=n-!chk(n-2);
			delt=2*s[modt-1]-s[modt-2];
		}
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

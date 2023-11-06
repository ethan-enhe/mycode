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


const ll MXN=2e5+5;

ll n,m,k;
ll arr[MXN],hero[MXN];
inline void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&arr[i]),hero[i]=-INF;
	scanf("%lld",&m);
	for(int i=1;i<=m;i++){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		hero[y]=max(hero[y],x);
	}
	for(int i=n-1;i;i--)
		hero[i]=max(hero[i],hero[i+1]);

	ll cur=0,cnt=0;
	while(cur<n){
		ll nx=cur,mx=arr[nx+1];
		while(nx<n && hero[nx-cur+1]>=mx)
			mx=max(mx,arr[(++nx)+1]);
		if(nx==cur){
			puts("-1");
			return;
		}
		cnt++;cur=nx;
	}
	printf("%lld\n",cnt);

}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

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


const ll MXN=105+5;

ll n,m,c1,cm;
ll arr[MXN];
vector<ll> app[MXN];
bool ans[MXN];
inline void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",arr+i);
		app[arr[i]].pb(i);
	}
	for(int i=1;i<MXN;i++){
		if(app[i].size()==1)c1++;
		if(app[i].size()>2)cm++;
	}
	if(c1&1){
		if(!cm){
			puts("NO");
			return;
		}
		else
			for(int i=1;i<MXN;i++)
				if(app[i].size()>2){
					ans[app[i][0]]=1;
					break;
				}
	}
	ll cnt=0;
	for(int i=1;i<MXN;i++)
		if(app[i].size()==1)
			ans[app[i][0]]=(cnt++)&1;
	puts("YES");
	for(int i=1;i<=n;i++)putchar('A'+ans[i]);
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

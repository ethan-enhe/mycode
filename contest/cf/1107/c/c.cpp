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

ll n,m,ans;
ll arr[MXN];
char str[MXN];
priority_queue<ll> q;
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)scanf("%lld",arr+i);
	scanf("%s",str+1);
	for(ll i=1;i<=n;i++){
		if(str[i]!=str[i-1]){
			ll tmp=m;
			while(tmp-- && !q.empty()){
				ans+=q.top();
				q.pop();
			}
			while(!q.empty())q.pop();
		}
		q.push(arr[i]);
	}
	ll tmp=m;
	while(tmp-- && !q.empty()){
		ans+=q.top();
		q.pop();
	}
	printf("%lld",ans);
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}

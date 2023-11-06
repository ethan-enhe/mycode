#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rd scanf
#define pt printf
#define setp(x) setprecision(x)
#define mem(x,y) memset(x,y,sizeof(x))
#define sz(x) (int)x.size()
#define umn(x,y) x=min(x,y)
#define umx(x,y) x=max(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;
typedef queue<ll> qi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

const ll INF=1e18;
const ll P=1e9+7;
const ll MXN=1e5+5;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}



ll n,m,k;
ll arr[MXN],brr[MXN],ca,cb;
inline void solve(){
	ca=cb=0;
	rd("%lld",&n);
	for(int i=1;i<=(n<<1);i++){
		ll x,y;
		rd("%lld%lld",&x,&y);
		if(!x)arr[++ca]=y*y;
		else brr[++cb]=x*x;
	}
	sort(brr+1,brr+1+n);
	sort(arr+1,arr+1+n);
	double res=0;
	for(int i=1;i<=n;i++)
		res+=sqrt(arr[i]+brr[i]);
	pt("%.13f\n",res);
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	ll tq=1;
	cin>>tq;
	while(tq--)solve();
	return 0;
}

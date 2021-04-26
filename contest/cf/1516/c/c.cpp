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

inline ll mod(const ll &x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(const ll &x,const ll &y){return !y?x:gcd(y,x%y);}
inline void pbin(const ll &x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=105;
const ll NR=2e5+5;

ll n,m,k,arr[MXN];
bool dp[NR];
inline void solve(){
	scanf("%lld",&n);
	ll sum=0;
	dp[0]=1;
	for(int i=1;i<=n;i++){
		scanf("%lld",arr+i);
		sum+=arr[i];
		for(int j=sum;j>=arr[i];j--)
			dp[j]|=dp[j-arr[i]];
	}
	if(sum&1 || !dp[sum>>1])printf("0\n");
	else{
		ll mni,mn=INF;
		for(int i=1;i<=n;i++){
			ll tmp=arr[i];
			if((tmp&(-tmp))<mn){
				mn=tmp&(-tmp);
				mni=i;
			}
		}
		printf("1\n%lld\n",mni);
	}

    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ios_base::sync_with_stdio(0);cin.tie(0);cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	solve();
	return 0;
}

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

const ll MXN=1e5+5;
const ll MXD=19;

ll n,m,k;
ll arr[MXN],jmp[MXN][MXD+1],last[MXN];
inline ll que(ll l,ll r){
	ll res=0;
	for(int i=MXD;~i;i--)
		if(jmp[l][i]<=r){
			l=jmp[l][i];
			res+=1<<i;
		}
	return res+1;
}
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",arr+i);
	}
	for(int i=1;i<=n+1;i++)
		for(int j=0;j<=MXD;j++)
			jmp[i][j]=n+1;
	for(int i=1;i<MXN;i++)last[i]=n+1;
	for(int i=n;i;i--){
		for(int j=2;j*j<=arr[i];j++)
			if(arr[i]%j==0){
				while(arr[i]%j==0)arr[i]/=j;
				jmp[i][0]=min(jmp[i][0],last[j]);
				last[j]=i;
			}
		if(arr[i]!=1){
			jmp[i][0]=min(jmp[i][0],last[arr[i]]);
			last[arr[i]]=i;
		}
		jmp[i][0]=min(jmp[i][0],jmp[i+1][0]);
		for(int j=1;j<=MXD;j++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
	}
	while(m--){
		ll a,b;
		scanf("%lld%lld",&a,&b);
		printf("%lld\n",que(a,b));
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

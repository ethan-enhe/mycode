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


const ll MXN=505+5;
const ll MXK=15;

ll n,m,k;
ll ev[MXN][MXN],eh[MXN][MXN];
ll arr[MXK][MXN][MXN];
inline void solve(){
	scanf("%lld%lld%lld",&n,&m,&k);
	if(k&1){
		for(int i=1;i<=n;i++,putchar('\n'))
			for(int j=1;j<=m;j++)
				printf("-1 ");
		return;
	}
	k>>=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
			scanf("%lld",&eh[i][j]);
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lld",&ev[i][j]);
	mem(arr,0x3f);
	mem(arr[0],0);
	for(int l=1;l<=k;l++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				{
					if(i>1)arr[l][i][j]=min(arr[l][i][j],arr[l-1][i-1][j]+2*ev[i-1][j]);
					if(i<n)arr[l][i][j]=min(arr[l][i][j],arr[l-1][i+1][j]+2*ev[i][j]);
					if(j>1)arr[l][i][j]=min(arr[l][i][j],arr[l-1][i][j-1]+2*eh[i][j-1]);
					if(j<m)arr[l][i][j]=min(arr[l][i][j],arr[l-1][i][j+1]+2*eh[i][j]);
				}

	for(int i=1;i<=n;i++,putchar('\n'))
		for(int j=1;j<=m;j++)
			printf("%lld ",arr[k][i][j]);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ios_base::sync_with_stdio(0);cin.tie(0);cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	solve();
	return 0;
}

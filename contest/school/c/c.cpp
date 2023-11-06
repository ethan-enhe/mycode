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
const ll P=998244353;
const ll MXN=1505;

inline ll mod(const ll &x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(const ll &x,const ll &y){return !y?x:gcd(y,x%y);}
inline void pbin(const ll &x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}



ll n,m,res=0;
ll cnt[MXN][MXN];
ll times[MXN][MXN],ss[MXN][MXN],st[MXN][MXN];
inline void prt(ll tmp[MXN][MXN]){
	for(int i=1;i<=n;i++,putchar('\n'))
		for(int j=1;j<=n;j++)
			cout<<tmp[i][j]<<" ";
	puts("\n---");
}
inline ll getsq(ll x1,ll y1,ll x2,ll y2){return (ss[x2][y2]-ss[x1-1][y2]-ss[x2][y1-1]+ss[x1-1][y1-1])%P;}
inline ll gettri(ll x,ll y,ll len){return (st[x+len-1][y]-getsq(1,y,x-1,y+len-1)-st[x-1][y+len])%P;}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%lld%lld",&n,&m);
	cnt[1][1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1+(i==1);j<=n;j++)
			cnt[i][j]=cnt[i-1][j]+cnt[i][j-1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			times[i][j]=cnt[i][j]*cnt[n-i+1][n-j+1]%P;
			ss[i][j]=(ss[i-1][j]+ss[i][j-1]-ss[i-1][j-1]+times[i][j])%P;
			st[i][j]=(st[i-1][j+1]+ss[i][j]-ss[i][j-1])%P;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			ll tmp;
			scanf("%lld",&tmp);
			res=(res+tmp*times[i][j])%P;
		}
	while(m--){
		ll x,y,len,c;
		scanf("%lld%lld%lld%lld",&x,&y,&len,&c);
		res=(res+gettri(x,y,len)*c)%P;
		printf("%lld",(res+P)%P);
	}
	return 0;
}

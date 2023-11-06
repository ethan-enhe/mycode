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

const double INF=1e13;
const ll P=1e9+7;
const ll MXN=1e5+5;
const double EPS=1e-9;

inline ll mod(const ll &x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(const ll &x,const ll &y){return !y?x:gcd(y,x%y);}
inline void pbin(const ll &x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}



ll n,d;
double arr[MXN],dp[MXN][2];
inline bool chk(double t){
	dp[0][0]=dp[0][1]=-INF;
	for(int i=1;i<=n;i++){
		if(i==1)dp[i][0]=arr[i]+t;
		else dp[i][0]=dp[i-1][1]>=-EPS?arr[i]+t:-INF;
		dp[i][1]=min(max(dp[i-1][0],dp[i-1][1])+d,arr[i]+t);
		if(fabs(dp[i][1]-arr[i])>t+EPS)dp[i][1]=-INF;
	}
	return dp[n][1]>=-EPS;
}
inline void solve(){
	scanf("%lld%lld",&n,&d);
	for(int i=1;i<=n;i++)scanf("%lf",arr+i);
	sort(arr+1,arr+1+n);
	double l=0,r=1e9+5;
	while(l+(1e-7)<r){
		double mid=(l+r)/2;
		if(chk(mid))r=mid;
		else l=mid;
	}
	printf("%.6f\n",l);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll tq=1;
	cin>>tq;
	while(tq--)solve();
	return 0;
}

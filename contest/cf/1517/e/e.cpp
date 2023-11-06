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

inline ll mod(const ll &x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(const ll &x,const ll &y){return !y?x:gcd(y,x%y);}
inline void pbin(const ll &x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=2e5+5;

ll n,m,k,ans;
ll arr[MXN];
ll sum[4][MXN];
inline ll gs(ll tp,ll l,ll r){return sum[tp][max(r,(ll)0)]-sum[tp][max(l-1,(ll)0)];}
inline void cal(ll l,ll r,ll pmin){
	if(l>r)return;
	ll ind=l-2;
	for(int i=r+((l^r)&1);i>=l;i-=2){
		ll tmp=gs(3,i,r);
		while(ind+2<=i && gs(l&1,ind+2,i-1)+tmp>=pmin)
			ind+=2;
		ind=min(ind,(ll)i);
		ans+=(ind-l+2)>>1;
	}
}
inline void solve(){
	//mod!!!
	scanf("%lld",&n);
	arr[0]=arr[n+1]=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",arr+i);
		sum[0][i]=sum[0][i-1],sum[1][i]=sum[1][i-1];
		sum[i&1][i]+=arr[i];
		sum[3][i]=sum[0][i]+sum[1][i];
	}
	ans=0;
	ll mid=(sum[3][n]>>1)+1;
	//右边无，左边无
	//CPPPP,PCPPP,CCPP,PPPPP,PCPCP
	cal(1,n,mid);
	cal(2,n,mid);
	
	//右边有，左边无
	//PPPPC,CPPPC,PCPPC
	if(n>2){
		cal(1,n-3,mid-arr[n-1]-arr[n-2]);
		cal(2,n-3,mid-arr[n-1]-arr[n-2]);
	}

	//左边有，右边无
	cal(4,n,mid-arr[1]);
	cal(5,n,mid-arr[1]);
	
	//两边都有
	if(n>2){
		cal(4,n-3,mid-arr[1]-arr[n-1]-arr[n-2]);
		cal(5,n-3,mid-arr[1]-arr[n-1]-arr[n-2]);
	}

	//PPPPP, CPPPP, PCPPP, CCPPP, PCCPP, PCPCP, PPPPC, CPPPC, PCPPC, PPPCC.
	for(int i=1;i<n-1;i++)
		if(gs(3,1,i)>=mid)
			ans++;
	printf("%lld\n",ans);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ios_base::sync_with_stdio(0);cin.tie(0);cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	ll tq;cin>>tq;while(tq--)
	solve();
	return 0;
}

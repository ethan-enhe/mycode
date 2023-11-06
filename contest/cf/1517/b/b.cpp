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


const ll MXN=100+5;

ll n,m,k;
ll arr[MXN][MXN],ans[MXN][MXN];
bool mark[MXN][MXN];
struct path{
	ll len,x,y;
	path(ll len,ll x,ll y):len(len),x(x),y(y){}
	bool operator < (const path &b)const{return len<b.len;}
};
priority_queue<path> q;
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%lld",&arr[i][j]);
			if((ll)q.size()<m)q.push(path(arr[i][j],i,j));
			else if(q.top().len>arr[i][j]){
				q.pop();
				q.push(path(arr[i][j],i,j));
			}
		}
	mem(mark,0);
	mem(ans,0);
	for(int i=1;i<=m;i++){
		path tmp=q.top();q.pop();
		ans[tmp.x][i]=tmp.len;
		mark[tmp.x][tmp.y]=1;
	}
	for(int i=1;i<=n;i++){
		ll ind=1;
		for(int j=1;j<=m;j++){
			if(ans[i][j])printf("%lld ",ans[i][j]);
			else{
				while(ind<=m && mark[i][ind])ind++;
				printf("%lld ",arr[i][ind++]);
			}
		}
		putchar('\n');
	}
    
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

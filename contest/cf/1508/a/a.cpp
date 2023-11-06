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
const ll MXN=5e5+5;

inline ll mod(const ll &x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(const ll &x,const ll &y){return !y?x:gcd(y,x%y);}
inline void pbin(const ll &x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}



ll n,m,k;
ll cnt[4][2];
char str[4][MXN];
inline void prt(ll x,ll y,ll type){
	ll ind=1;
	for(int i=1;i<=(n<<1);i++){
		if(str[x][i]==type+'0'){
			while(ind<=(n<<1) && str[y][ind]!=type+'0'){
				putchar(str[y][ind]);
				ind++;
			}
			ind++;
		}
		putchar(str[x][i]);
		//cerr<<i<<ind<<endl;
	}
	while(ind<=(n<<1))
		putchar(str[y][ind++]);
	putchar('\n');
}
inline void solve(){
	mem(cnt,0);
	cin>>n;
	for(int i=1;i<=3;i++){
		scanf("%s",str[i]+1);
		for(int j=1;j<=(n<<1);j++)
			cnt[i][str[i][j]-'0']++;
	}
	for(int type=0;type<=1;type++)
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++)
				if(i!=j && cnt[i][type]>=n && cnt[j][type]>=n){
					prt(i,j,type);
					return;
				}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);

	ll tq=1;
	cin>>tq;
	while(tq--)solve();
	return 0;
}

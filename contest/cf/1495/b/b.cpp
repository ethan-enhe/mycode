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
ll arr[MXN];
ll prei[MXN],sufi[MXN];
ll pred[MXN],sufd[MXN];
ll cnt[MXN];
inline void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>arr[i];
	for(int i=2;i<=n;i++)
		arr[i]>arr[i-1]?prei[i]=prei[i-1]+1:pred[i]=pred[i-1]+1;
	for(int i=n-1;i;i--)
		arr[i]>arr[i+1]?sufi[i]=sufi[i+1]+1:sufd[i]=sufd[i+1]+1;
	for(int i=1;i<=n;i++)
		cnt[max(pred[i],sufd[i])]++;
	for(int i=n-1;~i;i--)
		cnt[i]+=cnt[i+1];
	ll res=0;
	for(int i=1;i<=n;i++){
		ll il=prei[i],ir=sufi[i];
		if(!il || !ir)continue;
		if(il>=ir){
			if(cnt[il]>1+(max(pred[i+ir],sufd[i+ir])>=il) ||
				   	sufd[i+ir]>=il ||
				   	pred[i-il]>=il)continue;
			if(il==ir+1)continue;
			il--;il-=il&1;
			ll tmp=i-il-1;
			if(pred[tmp]>=ir || sufd[tmp]>=ir)continue;
		}
		il=prei[i],ir=sufi[i];
		if(il<=ir){
			if(cnt[ir]>1+(max(pred[i-il],sufd[i-il])>=ir) ||
					sufd[i+ir]>=ir||
					pred[i-il>=ir])continue;
			if(cnt[ir]>1+(il==ir))continue;
			if(ir==il+1)continue;
			ir--;ir-=ir&1;
			ll tmp=i+ir+1;
			if(pred[tmp]>=il || sufd[tmp]>=il)continue;
		}
		res++;
	}
	cout<<res;
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios_base::sync_with_stdio(0);cin.tie(0);
	cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	ll tq=1;
	while(tq--)solve();
	return 0;
}

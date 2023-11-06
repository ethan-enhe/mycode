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



ll n,m;
ll times[MXN],ans[MXN];
vi fr[MXN];
inline void solve(){
	bool f=1;
	cin>>n>>m;
	for(int i=1;i<=n;i++)times[i]=(m+1)>>1;
	for(int i=1;i<=m;i++){
		ll tmp;
		cin>>tmp;
		while(tmp--){
			ll ttmp;
			cin>>ttmp;
			fr[i].pb(ttmp);
		}
		if(fr[i].size()==1){
			if(times[fr[i][0]])times[fr[i][0]]--;
			else f=0;
		}
	}
	if(f){
		cout<<"YES"<<endl;
		for(int i=1;i<=m;i++){
			ll mxi=0;
			if(fr[i].size()==1){
				cout<<fr[i][0]<<" ";
				continue;
			}
			for(int j=0;j<fr[i].size();j++)
				if(times[fr[i][j]]>times[mxi])
					mxi=fr[i][j];
			times[mxi]--;
			cout<<mxi<<" ";
		}
		cout<<endl;
	}
	else cout<<"NO"<<endl;
	for(int i=1;i<=m;i++)fr[i].clear();

    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios_base::sync_with_stdio(0);cin.tie(0);
	cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	ll tq=1;
	cin>>tq;
	while(tq--)solve();
	return 0;
}

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
typedef set<pi>::iterator it;

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
ll ans[MXN],ac;


set<pi> st,alive;
inline it getnx(const set<pi> &tmp,ll x){
	it res=tmp.lower_bound(mp(x,0));
	if(res==tmp.end())return tmp.lower_bound(mp(1,0));
	return res;
}


inline void solve(){
	ac=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
		alive.insert(mp(i,0));
	}
	for(int i=1;i<=n;i++)
		if(gcd(arr[i],arr[i%n+1])==1)
			st.insert(mp(i,i%n+1));
	ll ind=1;
	while(!st.empty()){
		it p=getnx(st,ind);
		ll tmp=p->fi;
		ind=p->se;
		ans[++ac]=ind;
		st.erase(p);
		p=st.lower_bound(mp(ind,0));
		if(p!=st.end() && (p->fi==ind))
			st.erase(p);
		alive.erase(mp(ind,0));

		p=getnx(alive,ind);
		if(p!=alive.end()){
			ll nx=p->fi;
			if(gcd(arr[tmp],arr[nx])==1)
				st.insert(mp(tmp,nx));
		}
	}
	st.clear();
	alive.clear();
	cout<<ac<<" ";
	for(int i=1;i<=ac;i++)cout<<ans[i]<<" ";
	cout<<endl;
    
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


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
const ll SZ=710;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}



ll n,m,k;
ll arr[MXN],ans[MXN],place[MXN];

struct que{
	ll blk,l,r,id;
	bool operator < (const que &b)const{
		if(blk==b.blk)return blk&1?(r<b.r):(r>b.r);
		return blk<b.blk;
	}
}ask[MXN];

ll res=0,tot=0,rs=0,ls=0,l=1,r=0;
inline bool inrange(ll x){return place[x]>=l && place[x]<=r;}
inline void addl(){
	l--;
	ls+=r-l+1;
	tot++;
	if(arr[l]!=1 && inrange(arr[l]-1))ls-=r+1-place[arr[l]-1],tot--;
	if(arr[l]!=n && inrange(arr[l]+1))ls-=r+1-place[arr[l]+1],tot--;
	rs+=tot;
	res+=ls;
}
inline void addr(){
	r++;
	rs+=r-l+1;
	tot++;
	if(arr[r]!=1 && inrange(arr[r]-1))rs-=place[arr[r]-1]+1-l,tot--;
	if(arr[r]!=n && inrange(arr[r]+1))rs-=place[arr[r]+1]+1-l,tot--;
	ls+=tot;
	res+=rs;
}
inline void delr(){
	res-=rs;
	ls-=tot;
	if(arr[r]!=n && inrange(arr[r]+1))rs+=place[arr[r]+1]+1-l,tot++;
	if(arr[r]!=1 && inrange(arr[r]-1))rs+=place[arr[r]-1]+1-l,tot++;
	tot--;
	rs-=r-l+1;
	r--;
}
inline void dell(){
	res-=ls;
	rs-=tot;
	if(arr[l]!=n && inrange(arr[l]+1))ls+=r+1-place[arr[l]+1],tot++;
	if(arr[l]!=1 && inrange(arr[l]-1))ls+=r+1-place[arr[l]-1],tot++;
	tot--;
	ls-=r-l+1;
	l++;
}

inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",arr+i);
		place[arr[i]]=i;
	}
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&ask[i].l,&ask[i].r);
		ask[i].blk=ask[i].l/SZ;
		ask[i].id=i;
	}
	sort(ask+1,ask+1+m);
	for(int i=1;i<=m;i++){
		while(r<ask[i].r)addr();
		while(l>ask[i].l)addl();
		while(r>ask[i].r)delr();
		while(l<ask[i].l)dell();
		ans[ask[i].id]=res;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);

    
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


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
const ll MXN=2e5+5;

inline ll mod(const ll &x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(const ll &x,const ll &y){return !y?x:gcd(y,x%y);}
inline void pbin(const ll &x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}

ll n,arr[MXN],res;
ll last[MXN],pre[MXN];

#define ls (p<<1)
#define rs (p<<1|1)
const ll NR=MXN<<2;
struct node{
	ll va,sz,tag;
	inline node(ll va=0,ll sz=0,ll tag=0):va(va),sz(sz),tag(tag){}
	inline void addt(ll k){
		tag+=k;
		va+=sz*k;
	}
	inline node operator + (const node &y)const{return node(va+y.va,sz+y.sz);}
}t[NR];
inline void pushu(ll p){t[p]=t[ls]+t[rs];}
inline void pushd(ll p){
	t[ls].addt(t[p].tag);
	t[rs].addt(t[p].tag);
	t[p].tag=0;
}
void build(ll p,ll l,ll r){
	if(l==r){
		t[p]=node(-2,1);
		return;
	}
	ll mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushu(p);
}
void del(ll p,ll l,ll r,ll dx){
	if(l==r){
		t[p].sz=t[p].va=0;
		return;
	}
	ll mid=(l+r)>>1;
	pushd(p);
	if(dx<=mid)del(ls,l,mid,dx);
	else del(rs,mid+1,r,dx);
	pushu(p);
}
void mod(ll p,ll l,ll r,ll ml,ll mr,ll mx){
	if(ml<=l && r<=mr){
		t[p].addt(mx);
		return;
	}
	ll mid=(l+r)>>1;
	pushd(p);
	if(ml<=mid)mod(ls,l,mid,ml,mr,mx);
	if(mr>mid)mod(rs,mid+1,r,ml,mr,mx);
	pushu(p);
}
node que(ll p,ll l,ll r,ll ql,ll qr){
	if(ql<=l && r<=qr)return t[p];
	ll mid=(l+r)>>1;node res;
	pushd(p);
	if(ql<=mid)res=res+que(ls,l,mid,ql,qr);
	if(qr>mid)res=res+que(rs,mid+1,r,ql,qr);
	return res;
}


inline void solve(){
	scanf("%lld",&n);
	build(1,1,n);
	for(int i=1;i<=n;i++){
		scanf("%lld",arr+i);
		pre[i]=last[arr[i]];
		last[arr[i]]=i;
		
		//废除旧版的
		if(pre[i])del(1,1,n,pre[i]);
		mod(1,1,n,1,i,1);
		if(pre[i])mod(1,1,n,1,pre[i],-2);
		if(pre[pre[i]])mod(1,1,n,1,pre[pre[i]],1);
		if(pre[i]+2<=i)res+=que(1,1,n,pre[i]+1,i-1).va;
	}
	printf("%lld",res);
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ios_base::sync_with_stdio(0);cin.tie(0);
	cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	ll tq=1;
	//cin>>tq;
	while(tq--)solve();
	return 0;
}

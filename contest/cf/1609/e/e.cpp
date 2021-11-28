#include <bits/stdc++.h>
using namespace std;

//{{{ Def
#define fi first
#define se second
#define pb push_back
#define log(fmt...) fprintf(stderr, fmt)

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
//}}}
const ll INF = 1e18;
ll P = 1e9 + 7;
//{{{ Func
template <class T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <class T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <class T>
void umn(T &x, T y) {
    x = min(x, y);
}
//}}}
//{{{ Type
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
struct mll {
    ll v;
    explicit mll(ll _v = 0) : v(_v) {}
    ll redu(const ll &x) const {
        if (x < P) return x;
        if (x < (P << 1)) return x - P;
        return x % P;
    }
    explicit operator ll() const { return v; }
    mll operator+(const mll &y) const { return mll(redu(v + y.v)); }
    mll operator-(const mll &y) const { return mll(redu(P + v - y.v)); }
    mll operator*(const mll &y) const { return mll(redu(v * y.v)); }
    mll operator/(const mll &y) const { return mll(redu(v * (ll)qpow(y, P - 2))); }
    mll &operator=(const mll &y) { return v = y.v, *this; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = redu(v * y.v), *this; }
    mll &operator/=(const mll &y) { return v = redu(v * (ll)qpow(y, P - 2)), *this; }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
};
//}}}
const ll MXN = 1e6 + 5;
ll n, m;
ll cntc;
char str[MXN];

pi v[MXN];
/*
void mod(ll x,pi y){
	for(int i=x;i<=n+1;i++)
		v[i]=v[i]+y;
}
ll mn(){
	ll ans=INF;
	for(int i=0;i<=n+1;i++)
		for(int j=i;j<=n+1;j++)
			umn(ans,v[i].fi+v[j].se);
	return ans;
}
*/
struct node{
	pi v,tag;ll mn;
	node(){mn=INF;}
}t[MXN<<2];
#define ls p<<1
#define rs p<<1|1
void addt(ll p,pi tag){
	t[p].tag=t[p].tag+tag;
	t[p].v=t[p].v+tag;
	t[p].mn+=tag.fi+tag.se;
}
void pushd(ll p){
	addt(ls,t[p].tag);
	addt(rs,t[p].tag);
	t[p].tag={0,0};
}
void pushu(ll p){
	t[p].mn=min(t[ls].v.fi+t[rs].v.se,min(t[ls].mn,t[rs].mn));
	t[p].v.fi=min(t[ls].v.fi,t[rs].v.fi);
	t[p].v.se=min(t[ls].v.se,t[rs].v.se);
}
void build(ll p,ll l,ll r){
	t[p].tag={0,0};
	if(l==r){
		t[p].v={0,0};
		t[p].mn=0;
		return;
	}
	ll mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushu(p);
}
void mod(ll p,ll l,ll r,ll ml,ll mr,pi mv){
	if(ml<=l && r<=mr){
		addt(p,mv);
		return;
	}
	ll mid=(l+r)>>1;
	pushd(p);
	if(ml<=mid)mod(ls,l,mid,ml,mr,mv);
	if(mr>mid)mod(rs,mid+1,r,ml,mr,mv);
	pushu(p);
}


void prt(){
	printf("%s\nsc:%lld\n",str+1,cntc);
	for(int i=0;i<=n+1;i++)
		printf("%lld ",v[i].fi);
	putchar('\n');
	for(int i=0;i<=n+1;i++)
		printf("%lld ",v[i].se);
	putchar('\n');
}
void mod(ll x,char y,ll z){
	if(y=='a')
		mod(1,0,n+1,x,n+1,{z,0});
	else if(y=='c'){
		mod(1,0,n+1,x,n+1,{0,-z});
		cntc+=z;
	}
	else
		mod(1,0,n+1,x,n+1,{-z,z});
}

void solve() {
	scanf("%lld%lld",&n,&m);
	scanf("%s",str+1);
	build(1,0,n+1);
	for(int i=1;i<=n;i++){
		mod(i,str[i],1);
	}
	while(m--){
		ll x;char y;
		scanf("%lld %c",&x,&y);
		mod(x,str[x],-1);
		mod(x,str[x]=y,1);
		//prt();
		printf("%lld\n",cntc+t[1].mn);
	}

}

int main() {
#ifndef ONLINE_JUDGE
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    // ll t;scanf("%lld",&t);while(t--)
    solve();

    return 0;
}

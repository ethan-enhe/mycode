#include <bits/stdc++.h>
#include <vector>

using namespace std;

//{{{ Def
#define fi first
#define se second
#define pb push_back
#define log(fmt...) fprintf(stderr, fmt)
#define va2d(x, y) x[(y.fi)][(y.se)]

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
const ll INF = 1e18;
const ll P = 1e9 + 7;
const ll MXN = 1e6 + 5;
const pi go[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
ll n, m,ans=-INF;
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
ll abs(pi x) { return abs(x.fi) + abs(x.se); }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
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
template <class T>
struct myvec {
    T *v;
    int sz, dsz;
    myvec() { v = NULL, sz = dsz = 0; }
    ~myvec() { free(v); }
    operator T *() const { return v; }
    T *begin() { return v; }
    T *end() { return v + sz; }
    void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
    void pb(T x) {
        if (sz == dsz) v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
        v[sz++] = x;
    }
    void fill(T x) {
        for (int i = 0; i < sz; i++) v[i] = x;
    }
};
//}}}
bool cover[MXN];
ll fa[MXN];
ll dfn[MXN],id[MXN],sz[MXN],dpth[MXN],dfnc;
vector<ll> g[MXN];
void dfs(ll p){
	id[dfn[p]=++dfnc]=p;
	sz[p]=1;
	for(ll nx:g[p])
		if(nx!=fa[p]){
			fa[nx]=p;
			dpth[nx]=dpth[p]+1;
			dfs(nx);
			sz[p]+=sz[nx];
		}
}
struct node{
	ll tag;
	pi mx;
}t[MXN];
#define ls (p<<1)
#define rs (p<<1|1)
void pushu(ll p){
	t[p].mx=max(t[ls].mx,t[rs].mx);
}
void addt(ll p,ll tag){
	t[p].tag+=tag;
	t[p].mx.fi+=tag;
}
void pushd(ll p){
	if(t[p].tag){
		addt(ls,t[p].tag);
		addt(rs,t[p].tag);
		t[p].tag=0;
	}
}
void build(ll p,ll l,ll r){
	t[p].tag=0;
	if(l==r){
		t[p].mx={dpth[id[l]],id[l]};
		return;
	}
	ll mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushu(p);
}
void mod(ll p,ll l,ll r,ll ml,ll mr,ll mv){
	if(ml<=l && r<=mr){
		addt(p,mv);
		return;
	}
	pushd(p);ll mid=(l+r)>>1;
	if(ml<=mid)mod(ls,l,mid,ml,mr,mv);
	if(mr>mid)mod(rs,mid+1,r,ml,mr,mv);
	pushu(p);
}
void solve() {
    // code
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<n;i++){
		ll u,v;
		scanf("%lld%lld",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dpth[1]=1;
	dfs(1);
	build(1,1,n);
	//for(ll i=1;i<=n;i++)
	//	log("node %lld:%lld %lld %lld\n",(ll)i,dpth[i],dfn[i],sz[i]);
	cover[0]=1;
	ll b=n;
	for(ll i=1;i<=m;i++){
		ll cur=t[1].mx.se;
		//log("%lld\n",cur);
		while(!cover[cur]){
			--b;
			mod(1,1,n,dfn[cur],dfn[cur]+sz[cur]-1,-1);
			cover[cur]=1;
			cur=fa[cur];
		}
		umx(ans,(n-i-min(b,n/2))*(i-min(b,n/2)));
	}
	printf("%lld",ans);
}

int main() {
#ifndef ONLINE_JUDGE
     //freopen("test.in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    // ll t;scanf("%lld",&t);while(t--)
    solve();

    return 0;
}

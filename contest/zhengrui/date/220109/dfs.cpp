#include <bits/stdc++.h>
#include <vector>
using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back

#ifdef ONLINE_JUDGE
#define log(fmt...) void()
#else
#define log(fmt...) fprintf(stderr, fmt)
#endif

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
//{{{ Func
ll redu(const ll &x) {
    if (x < P) return x;
    if (x < (P << 1)) return x - P;
    return x % P;
}
template <typename T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <typename T>
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
const pi go[] = {{1, 0}, {-1, 0}, {0, 1},  {0, -1},
                 {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
struct mll {
    ll v;
    explicit mll(ll _v = 0) : v(_v) {}
    explicit operator ll() const { return v; }
    mll operator+(const mll &y) const { return mll(redu(v + y.v)); }
    mll operator-(const mll &y) const { return mll(redu(P + v - y.v)); }
    mll operator*(const mll &y) const { return mll(redu(v * y.v)); }
    mll operator/(const mll &y) const {
        return mll(redu(v * (ll)qpow(y, P - 2)));
    }
    mll &operator=(const mll &y) { return v = y.v, *this; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = redu(v * y.v), *this; }
    mll &operator/=(const mll &y) {
        return v = redu(v * (ll)qpow(y, P - 2)), *this;
    }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
};
mll ltm(const ll &x) { return mll(redu(x % P + P)); }
template <typename T>
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
ll n, m;
ll arr[MXN],ans,cnt[MXN];
vector<int> g[MXN];
bool vis[MXN];
void dfs(int p,int t,int fa,int len){
	vis[p]=1;
	for(int nx:g[p]){
		if(nx==fa)continue;
		if(nx==t)++ans,++cnt[len/2];
		else if(nx>t && !vis[nx])
			dfs(nx,t,p,len+1);
	}
	vis[p]=0;
}
int main(int argc, char *argv[]) {
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",arr+i);
		for(int j=1;j<=arr[i];j++){
			g[i].push_back(j+n);
			g[j+n].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		dfs(i,i,0,1);
	}
	cout<<ans/2<<endl;
	for(int i=1;i<=n;i++)
		cout<<cnt[i]<<endl;
    return 0;
}

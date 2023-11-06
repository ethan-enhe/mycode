#include <bits/stdc++.h>

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
const ll MXN = 2e5 + 5, MXZERO = 1000000;
const pi go[] = {{1, 0}, {-1, 0}, {0, 1},  {0, -1},
				 {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
ll n, m;
//{{{ Func
template <class T> T qpow(T x, ll y) {
	T r(1);
	while (y) {
		if (y & 1)
			r = r * x;
		x = x * x, y >>= 1;
	}
	return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <class T> void umx(T &x, T y) { x = max(x, y); }
template <class T> void umn(T &x, T y) { x = min(x, y); }
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
		if (x < P)
			return x;
		if (x < (P << 1))
			return x - P;
		return x % P;
	}
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
template <class T> struct myvec {
	T *v;
	int sz, dsz;
	myvec() { v = NULL, sz = dsz = 0; }
	~myvec() { free(v); }
	operator T *() const { return v; }
	T *begin() { return v; }
	T *end() { return v + sz; }
	void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
	void pb(T x) {
		if (sz == dsz)
			v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
		v[sz++] = x;
	}
	void fill(T x) {
		for (int i = 0; i < sz; i++)
			v[i] = x;
	}
};
//}}}
vector<pi> g[MXN];
ll fw[MXN];
void ini(ll p, ll fa) {
	for (pi &nx : g[p])
		if (nx.fi != fa) {
			fw[nx.fi] = nx.se;
			ini(nx.fi, p);
		}
}
ll dp[MXN][4];
namespace s3 {
myvec<ll> t1[MXN], t2[MXN];
void dfs(ll p, ll fa) {
	ll ZERO = min(MXZERO, (ll)g[p].size() + 2), RG = ZERO * 2;
	t1[p].rsz(RG);
	t2[p].rsz(RG);
	for (ll i = 0; i < RG; i++)
		t1[p][i] = -INF;
	t1[p][ZERO] = 0;
	for (pi &nx : g[p])
		if (nx.fi != fa) {
			dfs(nx.fi, p);
			for (ll j = 1; j < RG - 1; j++) {
				t2[p][j] =
					max({t1[p][j] + dp[nx.fi][0], t1[p][j - 1] + dp[nx.fi][2],
						 t1[p][j + 1] + dp[nx.fi][1]});
			}
			for (ll i = 0; i < RG; i++)
				t1[p][i] = t2[p][i];
		}
	dp[p][0] = max(t1[p][ZERO], t1[p][ZERO + 1] + fw[p]);
	dp[p][1] = t1[p][ZERO] + fw[p];
	dp[p][2] = t1[p][ZERO - 1] + fw[p];
	// log("%lld ",p);
	// for(int i=0;i<3;i++){
	//	if(dp[p][i]<=-1000)log("-inf ");
	//	else log("%lld ",dp[p][i]);
	//}
	// log("\n");
}
} // namespace s3
namespace s4 {
myvec<ll> t1[MXN][2], t2[MXN][2];
void dfs(ll p, ll fa) {
	ll ZERO = min(MXZERO, (ll)g[p].size() + 2), RG = ZERO * 2;
	for (int f = 0; f < 2; f++) {
		t1[p][f].rsz(RG);
		t2[p][f].rsz(RG);
		for (ll i = 0; i < RG; i++)
			t1[p][f][i] = -INF;
	}
	t1[p][0][ZERO] = 0;
	for (pi &nx : g[p])
		if (nx.fi != fa) {
			dfs(nx.fi, p);
			for (ll j = 1; j < RG - 1; j++)
				for (int f = 0; f < 2; f++) {
					t2[p][f][j] = max({t1[p][f][j] + dp[nx.fi][0],
									   t1[p][f][j - 1] + dp[nx.fi][3],
									   t1[p][f][j + 1] + dp[nx.fi][1],
									   t1[p][!f][j] + dp[nx.fi][2]});
				}
			for (int f = 0; f < 2; f++)
				for (ll i = 0; i < RG; i++)
					t1[p][f][i] = t2[p][f][i];
		}
	dp[p][0] = max(t1[p][0][ZERO], t1[p][0][ZERO + 1] + fw[p]);
	dp[p][1] = t1[p][0][ZERO] + fw[p];
	dp[p][2] = t1[p][0][ZERO - 1] + fw[p];
	dp[p][3] = t1[p][1][ZERO] + fw[p];
	// log("%lld ",p);
	// for(int i=0;i<3;i++){
	//	if(dp[p][i]<=-1000)log("-inf ");
	//	else log("%lld ",dp[p][i]);
	//}
	// log("\n");
}
} // namespace s4
void solve() {
	// TODO:
	// MXN
	scanf("%lld%lld", &n, &m);
	for (ll i = 1; i < n; i++) {
		ll u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	for (ll i = 1; i <= n; i++)
		shuffle(g[i].begin(), g[i].end(), myrand);
	ini(1, 0);
	if (m == 3) {
		s3::dfs(1, 0);
		printf("%lld", dp[1][1]);
	} else {
		s4::dfs(1, 0);
		printf("%lld", dp[1][1]);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
	// freopen(".out","w",stdout);
#endif
	// ll t;scanf("%lld",&t);while(t--)
	solve();

	return 0;
}

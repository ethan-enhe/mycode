#include <bits/stdc++.h>
using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define ce constexpr

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
// typedef __uint128_t u128;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ FastMod
// struct brt {
// 	ull m, b;
// 	ce brt(const ull &m = 1) : m(m), b((u128(1) << 64) / m) {}
// 	friend ce ull operator/(const ull &a, const brt &mod) {
// 		ull r = (u128(mod.b) * a >> 64) + 1;
// 		return r - ((a - r * mod.m) >> 63);
// 	}
// 	friend ce ull operator%(const ull &a, const brt &mod) {
// 		ull r = a - mod.m * (u128(mod.b) * a >> 64);
// 		return r >= mod.m ? r - mod.m : r;
// 	}
// };
//}}}
ce ll INF = 1e18;
// ce brt P(1e9 + 7);
ce ll MXN = 1e6 + 5;
//{{{ Func
template <typename T> ce T qpow(T x, ll y) {
	T r(1);
	while (y) {
		if (y & 1)
			r = r * x;
		x = x * x, y >>= 1;
	}
	return r;
}
ce ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T> ce void umx(T &x, T y) { x = max(x, y); }
template <typename T> ce void umn(T &x, T y) { x = min(x, y); }
ce ll abs(pi x) {
	return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se);
}
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
ce pi go[] = {{1, 0}, {-1, 0}, {0, 1},  {0, -1},
			  {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
ce pi operator+(const pi &x, const pi &y) {
	return pi(x.fi + y.fi, x.se + y.se);
}
ce pi operator-(const pi &x, const pi &y) {
	return pi(x.fi - y.fi, x.se - y.se);
}
ce pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
// struct mll {
// 	ll v;
// 	ce explicit mll(ll _v = 0) : v(_v) {}
// 	ce explicit operator ll() const { return v; }
// 	// mll operator+(const mll &y) const { return mll((v + y.v) % P); }
// 	mll operator-(const mll &y) const { return mll((P.m + v - y.v) % P); }
// 	mll operator*(const mll &y) const { return mll((v * y.v) % P); }
// 	mll operator/(const mll &y) const {
// 		return mll((v * (ll)qpow(y, P.m - 2)) % P);
// 	}
// 	mll &operator=(const mll &y) { return v = y.v, *this; }
// 	mll &operator+=(const mll &y) { return v = (v + y.v) % P, *this; }
// 	mll &operator-=(const mll &y) { return v = (P.m + v - y.v) % P, *this; }
// 	mll &operator*=(const mll &y) { return v = v * y.v % P, *this; }
// 	mll &operator/=(const mll &y) {
// 		return v = v * (ll)qpow(y, P.m - 2) % P, *this;
// 	}
// 	ce bool operator==(const mll &y) const { return v == y.v; }
// 	ce bool operator!=(const mll &y) const { return v != y.v; }
// };
// ce mll ltm(const ll &x) { return mll(x % P); }
// template <typename T> struct myvec {
// 	T *v;
// 	int sz, dsz;
// 	myvec() { v = NULL, sz = dsz = 0; }
// 	~myvec() { free(v); }
// 	operator T *() const { return v; }
// 	T *begin() { return v; }
// 	T *end() { return v + sz; }
// 	void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
// 	void pb(T x) {
// 		if (sz == dsz)
// 			v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
// 		v[sz++] = x;
// 	}
// 	void fill(T x) {
// 		for (int i = 0; i < sz; i++)
// 			v[i] = x;
// 	}
// };
//}}}
ll n, m;
char arr[MXN];

int main(int argc, char *argv[]) {
	// code
	ll t;
	scanf("%lld",&t);
	while(t--){
		scanf("%s",arr+1);
		ll n=strlen(arr+1);
		sort(arr+1,arr+1+n);
		printf("%s\n",arr+1);
	}
	return 0;
}

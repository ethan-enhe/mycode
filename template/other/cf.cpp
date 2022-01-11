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
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
ce ll INF = 1e18;
ce ll P = 1e9 + 7;
ce ll MXN = 1e6 + 5;
//{{{ Func
ce ll redu(const ll &x) {
	if (x < P) return x;
	if (x < (P << 1)) return x - P;
	return x % P;
}
template <typename T>
ce T qpow(T x, ll y) {
	T r(1);
	while (y) {
	    if (y & 1) r = r * x;
	    x = x * x, y >>= 1;
	}
	return r;
}
ce ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T>
ce void umx(T &x, T y) {
	x = max(x, y);
}
template <typename T>
ce void umn(T &x, T y) {
	x = min(x, y);
}
ce ll abs(pi x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
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
ce pi go[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
ce pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
ce pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
ce pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
struct mll {
	ll v;
	ce explicit mll(ll _v = 0) : v(_v) {}
	ce explicit operator ll() const { return v; }
	ce mll operator+(const mll &y) const { return mll(redu(v + y.v)); }
	ce mll operator-(const mll &y) const { return mll(redu(P + v - y.v)); }
	ce mll operator*(const mll &y) const { return mll(redu(v * y.v)); }
	ce mll operator/(const mll &y) const { return mll(redu(v * (ll)qpow(y, P - 2))); }
	ce mll &operator=(const mll &y) { return v = y.v, *this; }
	ce mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
	ce mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
	ce mll &operator*=(const mll &y) { return v = redu(v * y.v), *this; }
	ce mll &operator/=(const mll &y) { return v = redu(v * (ll)qpow(y, P - 2)), *this; }
	ce bool operator==(const mll &y) const { return v == y.v; }
	ce bool operator!=(const mll &y) const { return v != y.v; }
};
ce mll ltm(const ll &x) { return mll(redu(x % P + P)); }
template <typename T>
struct myvec {
	T *v;
	int sz, dsz;
	ce myvec() { v = NULL, sz = dsz = 0; }
	~myvec() { free(v); }
	ce operator T *() const { return v; }
	ce T *begin() { return v; }
	ce T *end() { return v + sz; }
	ce void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
	ce void pb(T x) {
	    if (sz == dsz) v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
	    v[sz++] = x;
	}
	ce void fill(T x) {
	    for (int i = 0; i < sz; i++) v[i] = x;
	}
};
//}}}
ll n, m;
ll arr[MXN];

int main(int argc, char *argv[]) {
	
	return 0;
}

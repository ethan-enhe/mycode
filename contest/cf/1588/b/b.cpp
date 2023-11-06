#include <bits/stdc++.h>
#include <cstdio>
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
ll arr[MXN];
map<pi,ll> saved;

ll ask(ll l,ll r){
	if(r<=l)return 0;
	if(saved.find({l,r})!=saved.end())return saved[{l,r}];
	printf("? %lld %lld\n",l,r);
	fflush(stdout);
	ll res;
	scanf("%lld",&res);
	return saved[{l,r}]=res;
}
void solve() {
	saved.clear();
	scanf("%lld",&n);
	//findk
	ll l=1,r=n;
	while(l<r){
		ll mid=(l+r)>>1;
		if(ask(1,mid)==ask(1,n))r=mid;
		else l=mid+1;
	}
	//log("k=%lld",l);
	ll k=l,j=k-ask(1,k)+ask(1,k-1),i=j-1-ask(1,j-1)+ask(1,j-2);
	printf("! %lld %lld %lld\n",i,j,k);
	fflush(stdout);
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    ll t;scanf("%lld",&t);while(t--)
    solve();

    return 0;
}

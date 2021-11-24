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
bool vis[MXN];
ll arr[MXN],brr[MXN];

inline bool cal(){
	m=0;
	for(int i=1;i<=n;i++)
		if(!vis[i])
			brr[++m]=arr[i];
	for(int i=1;i<=m;i++)
		if(brr[m+1-i]!=brr[i])
			return 0;
	return 1;
}
inline bool dfs(ll ind,ll x){
	if(ind==n+1){
		return cal();
	}
	if(dfs(ind+1,x))return 1;
	if(arr[ind]==x){
		vis[ind]=1;
		if(dfs(ind+1,x))return 1;
		vis[ind]=0;
	}
	return 0;
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
	}
	for(int i=1;i<=n;i++)
		if(dfs(1,i))
		{
			puts("YES");
			return;

		}
			puts("NO");

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


#include <bits/stdc++.h>
#include <vector>
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
pi l;
char *str[MXN];
vector<bool> mp[MXN];
vector<bool> vis[MXN];
const pi go[]={{1,0},{-1,0},{0,1},{0,-1}};
void dfs(pi p){
	if(mp[p.fi][p.se] || vis[p.fi][p.se])return;
	ll cnt=0;
	for(int i=0;i<4;i++){
		pi nx=p+go[i];
		cnt+=!mp[nx.fi][nx.se];
	}
	if(cnt>2)return;
	vis[p.fi][p.se]=1;
	for(int i=0;i<4;i++){
		pi nx=p+go[i];
		dfs(nx);
	}
}
void solve() {
	scanf("%lld%lld",&n,&m);
	for(int i=0;i<=n+1;i++){
		vis[i].resize(m+5);
		mp[i].resize(m+5);
		str[i]=new char[m+5];
		for(int j=0;j<vis[i].size();j++)
			vis[i][j]=0;
	}
	for(int i=0;i<=n;i++)
		mp[i][0]=mp[i][m+1]=1;
	for(int i=0;i<=m;i++)
		mp[0][i]=mp[n+1][i]=1;
	for(int i=1;i<=n;i++){
		scanf("%s",str[i]+1);
		for(int j=1;j<=m;j++){
			mp[i][j]=str[i][j]=='#';
			if(str[i][j]=='L')l={i,j};
		}
	}
	for(int i=0;i<4;i++)
		dfs(l+go[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(str[i][j]=='.')putchar(vis[i][j]?'+':'.');
			else putchar(str[i][j]);
		}
		putchar('\n');
	}

}

int main() {
#ifndef ONLINE_JUDGE
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    // ll t;scanf("%lld",&t);while(t--)
	ll t;
	cin>>t;
	while(t--)
    solve();

    return 0;
}

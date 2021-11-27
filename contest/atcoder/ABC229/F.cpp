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
ll arr[MXN], brr[MXN];
ll dp[MXN][2][2][2];

inline void cal() {
    for (ll i = 0; i < n; i++)
		for (ll k0 = 0; k0 < 2; k0++)
			for (ll k1 = 0; k1 < 2; k1++)
				for (ll hasdel = 0; hasdel < 2; hasdel++) {
					for (ll delb = 0; delb < 2; delb++) {
						ll nxhasdel = hasdel | delb, nxk[] = {k0, k1};
						if (delb) nxk[0] = nxk[1] = 0;
						for (ll hasa = 0; hasa < 2; hasa++) {
							if (nxk[i & 1] && hasa) continue;
							nxk[!(i & 1)] |= hasa;
							ll cost = delb * brr[i] + (1 - hasa) * arr[i + 1];
							umn(dp[i + 1][nxk[0]][nxk[1]][nxhasdel], dp[i][k0][k1][hasdel] + cost);
						}
					}
				}
}
void solve() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", arr + i);
    for (int i = 1; i <= n; i++) scanf("%lld", brr + i);
    arr[0] = arr[n];
    brr[0] = brr[n];
    ll ans = INF;

	bool f=n&1;
    for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			memset(dp,0x3f,sizeof(dp));
			dp[0][i][j][0]=0;
			cal();
			umn(ans,dp[n][i^f][j^f][1]);
			if(!f)umn(ans,dp[n][i^f][j^f][0]);
		}
    }
    printf("%lld", ans);
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

#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for (int i = (l); i <= (r); i++)
#define per(i,r,l) for (int i = (r); i >= (l); i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define maxn(a, b) a = max(a, b)
#define minn(a, b) a = min(a, b)
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
const ll mod = 998244353;
ll rp(ll a,ll b) {ll res=1%mod;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}

const int N = 200010;
int n, k;
int a[N];
map<int, int> cnt;
VI b[N];

int main() {
	scanf("%d%d", &n, &k);
	int d = 0;
	rep(i,1,n) {
		scanf("%d", &a[i]);
		++cnt[a[i]];
		maxn(d, cnt[a[i]]);
	}
	VI ve;
	for (auto [x, c] : cnt) if (c == d) {
		ve.eb(x);
	}
	ll ans = (n - d) * 1ll * k+ve[0] - ve.back();
	rep(i,1,SZ(ve)-1) maxn(ans, (n-d-1)*1ll*k+ve[i] -ve[i-1]);
	printf("%lld\n",ans);
	return 0;
}

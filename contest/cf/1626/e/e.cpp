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
ce ll MXN = 3e5+5;
ll n, m;
ll arr[MXN];
bool isb[MXN], ans[MXN];
ll sz[MXN];

bool vip[MXN];
vector<ll> g[MXN];

void dsz(ll p, ll fa) {
	for (ll nx : g[p])
		if (nx != fa) {
			dsz(nx, p);
			sz[p] += sz[nx];
		}
}
bool dfs(ll p, ll fa, bool has_out) {
	bool has_in = 0;
	if (vip[p]) {
		if (sz[1] - sz[p])
			has_out = 1;
		if (sz[p])
			has_in = 1;
	}
	for (ll nx : g[p])
		if (nx != fa)
			has_in |= dfs(nx, p, has_out);
	ans[p] |= has_in | has_out;
	return has_in;
}
void cal(ll dig, bool f, bool rev) {
	for (int i = 1; i <= n; i++)
		sz[i] = vip[i] = 0;
	for (int i = 1; i <= n; i++)
		if (isb[i]) {
			//关键点
			if (~dig) {
				if (((i >> dig) & 1) ^ rev)
					sz[i] = 1;
				else {
					if (f)
						for (ll nx : g[i])
							vip[nx] = 1;
					else
						vip[i] = 1;
				}
			}
		}
	dsz(1, 0);
	dfs(1, 0, 0);
}
int main(int argc, char *argv[]) {
	// freopen("e.in", "r", stdin);
	// freopen("e.out","w",stdout);
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		ll tmp;
		scanf("%lld", &tmp);
		isb[i] = tmp;
	}
	for (int i = 1; i < n; i++) {
		ll u, v;
		scanf("%lld%lld", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i <= 20; i++) {
		cal(i, 0, 0);
		cal(i, 0, 1);
		cal(i, 1, 0);
		cal(i, 1, 1);
	}
	for (int i = 1; i <= n; i++)
		printf("%lld ", (ll)ans[i]);
	putchar('\n');

	return 0;
}

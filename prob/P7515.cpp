#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
constexpr ll MXN = 605, INF = 1e6;
ll t, n, m, arr[MXN][MXN], brr[MXN][MXN];
ll dis[MXN], len[MXN];
deque<ll> q;
vector<pi> g[MXN];
// y<=x+z
void lim(ll x, ll y, ll z) { g[x].push_back({y, z}); }

bool spfa() {
	memset(dis, 0x3f, sizeof(dis));
	while (!q.empty())
		q.pop_front();
	dis[0] = 0;
	q.push_front(0);
	while (!q.empty()) {
		ll p = q.front();
		q.pop_front();
		for (pi &nx : g[p]) {
			ll nd = dis[p] + nx.second;
			if (dis[nx.first] > nd) {
				if ((len[nx.first] = len[p] + 1) > n + m)
					return 0;
				dis[nx.first] = nd;
				if (!q.empty() && nd < dis[q.front()])
					q.push_front(nx.first);
				else
					q.push_back(nx.first);
			}
		}
	}
	return 1;
}
int main() {
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld%lld", &n, &m);
		for (int i = 0; i <= n + m; i++)
			g[i].clear();
		//偶数行，奇数列flip
		for (int i = 2; i <= n; i++)
			for (int j = 2; j <= m; j++) {
				scanf("%lld", &arr[i][j]);
				brr[i][j] = arr[i][j] - brr[i - 1][j] - brr[i][j - 1] -
							brr[i - 1][j - 1];
			}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				ll s = i, t = n + j;
				if ((i + j) & 1)
					swap(s, t);
				lim(s, t, brr[i][j]);
				lim(t, s, INF - brr[i][j]);
			}
		for (int i = 1; i <= n + m; i++)
			lim(0, i, 1e9);
		if (!spfa())
			puts("NO");
		else {
			puts("YES");
			for (int i = 1; i <= n; i++, putchar('\n'))
				for (int j = 1; j <= m; j++) {
					ll s = i, t = n + j;
					if ((i + j) & 1)
						swap(s, t);
					printf("%lld ", brr[i][j] + dis[s] - dis[t]);
				}
		}
	}

	return 0;
}

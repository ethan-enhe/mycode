#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MXN = 3e5 + 5, LG = 31 - __builtin_clz(MXN);
int n, m, k;
int fa[MXN], sz[MXN];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int rt[MXN], nodec;
struct node {
	int ls, rs, va;
} t[MXN * LG];
queue<pair<int, int>> q;
int que(int p, int l, int r, int qi) {
	if (l == r || !p)
		return t[p].va;
	int mid = (l + r) >> 1;
	return qi <= mid ? que(t[p].ls, l, mid, qi) : que(t[p].rs, mid + 1, r, qi);
}
void mod(int &p, int l, int r, int mi, int mv) {
	if (!p)
		p = ++nodec;
	if (l == r) {
		if (t[p].va)
			q.push({t[p].va, mv});
		else
			t[p].va = mv;
		return;
	}
	int mid = (l + r) >> 1;
	mi <= mid ? mod(t[p].ls, l, mid, mi, mv) : mod(t[p].rs, mid + 1, r, mi, mv);
}
int mrg_seg(int x, int y) {
	if (!x || !y)
		return x | y;
	if (t[x].va && t[y].va)
		q.push({t[x].va, t[y].va});
	t[x].ls = mrg_seg(t[x].ls, t[y].ls);
	t[x].rs = mrg_seg(t[x].rs, t[y].rs);
	return x;
}
void mrg_all(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) {
		rt[x] = mrg_seg(rt[x], rt[y]);
		fa[y] = x, sz[x] += sz[y], sz[y] = 0;
	}
}

int main(int argc, char *argv[]) {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		sz[fa[i] = i] = 1;
	while (m--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		mod(rt[v], 1, k, w, u);
	}
	while (!q.empty()) {
		auto p = q.front();
		q.pop();
		mrg_all(p.first, p.second);
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans += (ll)sz[i] * (sz[i] - 1) >> 1;
	printf("%lld", ans);

	return 0;
}

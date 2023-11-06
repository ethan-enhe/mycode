#include <bits/stdc++.h>
using namespace std;
const int MXN = 5e5 + 5;
int n, s, t, len, path[MXN];
bool on_path[MXN];

vector<int> g[MXN];
bool mark_path(int p, int fa) {
	if (p == s)
		return on_path[path[++len] = p] = 1, 1;
	for (int &nx : g[p])
		if (nx != fa)
			if (mark_path(nx, p))
				return on_path[path[++len] = p] = 1, 1;
	return 0;
}
int cal_dpth(int p, int fa) {
	int r = 0;
	for (int &nx : g[p])
		if (!on_path[nx] && nx != fa)
			r = max(1 + cal_dpth(nx, p), r);
	return r;
}
typedef tuple<int, int, int> tp;
// mxr 表示从len走到lr之间的最大值
tp solve(int l, int r) {
	bool turn = l == (len - r + 1);
	int mxr, mxl, res, d;
	if (r == l + 1) {
		d = cal_dpth(path[l], 0);
		int dr = cal_dpth(path[r], 0);
		mxl = max(d + l, dr + r);
		mxr = max(d + (len - l + 1), dr + (len - r + 1));
		res = d + l - (dr + (len - r + 1));
	} else if (turn) {
		d = cal_dpth(path[l], 0);
		tie(mxr, mxl, res) = solve(l + 1, r);
		res = max(res, l + d - mxr);
		mxr = max(mxr, d + (len - l + 1));
		mxl = max(mxl, d + l);
	} else {
		d = cal_dpth(path[r], 0);
		tie(mxr, mxl, res) = solve(l, r - 1);
		res = min(res, mxl - (d + len - r + 1));
		mxr = max(mxr, d + (len - r + 1));
		mxl = max(mxl, d + r);
	}
	return tp{mxr, mxl, res};
}

int main(int argc, char *argv[]) {
	scanf("%d%d%d", &n, &s, &t);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	mark_path(t, 0);
	printf("%d", get<2>(solve(1, len)));
	return 0;
}

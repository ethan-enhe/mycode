#include <bits/stdc++.h>
#include "testlib.h"

#define rep(i, x, y) for(int i = (x); i <= (y); i++)

using namespace std;

const int N = 1e6 + 10;

int n, a[N], ansT, outT;
int val[N << 2];

void pu(int o) { val[o] = max(val[o << 1], val[o << 1 | 1]); }
void build(int o = 1, int l = 1, int r = n) {
	if(l == r) return val[o] = a[l], void(); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); pu(o);
}

int tfind(int x, int o = 1, int l = 1, int r = n) {
	if(val[o] < x) return n + 1; if(l == r) return l; int mid = l + r >> 1;
	if(val[o << 1] >= x) return tfind(x, o << 1, l, mid); else return tfind(x, o << 1 | 1, mid + 1, r);
}
void upd(int pos, int v, int o = 1, int l = 1, int r = n) {
	if(l == r) return val[o] = v, void(); int mid = l + r >> 1;
	if(pos <= mid) upd(pos, v, o << 1, l, mid); else upd(pos, v, o << 1 | 1, mid + 1, r); pu(o);
}

int main(int argc, char **argv) {
	registerTestlibCmd(argc, argv);
	n = inf.readInt(); rep(i, 1, n) a[i] = inf.readInt();
	outT = ouf.readInt(); ansT = ans.readInt();
	if(outT != ansT) { quitf(_wa, "jury has answer %d, but participant has answer %d", ansT, outT); return 0; }
	build();
	rep(i, 1, outT) {
		int x = ouf.readInt(1, n + 1, "x_i is not in [1, n + 1]"), y = ouf.readInt(1, n + 1, "y_i is not in [1, n + 1]");
		int p = tfind(x), q = tfind(y);
		if(p <= n) upd(p, 0); if(q <= n) upd(q, 0);
	}	
	if(val[1] != 0) { quitp(0.5, "ans is correct, but your plan is not correct."); return 0; }
	quitf(_ok, "ok."); return 0;
}

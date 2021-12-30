#include <bits/stdc++.h>
using namespace std;

#define ref sjdkflansdklfnalsd
#define AIA __attribute__((always_inline)) __attribute__((flatten)) __attribute__((aligned())) __attribute__((hot)) __attribute__((nothrow)) __attribute__((no_stack_protector))

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

AIA inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

AIA inline int Abs(const int& x) {return (x > 0 ? x : -x);}
AIA inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
AIA inline int Min(const int& x, const int& y) {return (x < y ? x : y);}
AIA inline long long Absll(const long long& x) {return (x > 0 ? x : -x);}
AIA inline long long Maxll(const long long& x, const long long& y) {return (x > y ? x : y);}
AIA inline long long Minll(const long long& x, const long long& y) {return (x < y ? x : y);}

const int N = 300005;
vector <pair <int, int> > g[N];
int n, hd[N], pnt, q, dep[N], fa[N][21], dfn[N], pst[N], _time, tmpn, costup, costdown[N], leafid[N], lcnt;
int son[N], top[N], highbit[(1<<20)+5], lid[N], trh[N], ref[N], rtmp[N], s, fa_before[N], w_before[N], vis[N], faWeight[N], dgr[N], fapresum[N];

namespace GenHelper
{
    unsigned z1,z2,z3,z4,b;
    AIA inline unsigned rand_()
    {
    b=((z1<<6)^z1)>>13;
    z1=((z1&4294967294U)<<18)^b;
    b=((z2<<2)^z2)>>27;
    z2=((z2&4294967288U)<<2)^b;
    b=((z3<<13)^z3)>>21;
    z3=((z3&4294967280U)<<7)^b;
    b=((z4<<3)^z4)>>12;
    z4=((z4&4294967168U)<<13)^b;
    return (z1^z2^z3^z4);
    }
}
AIA inline void srand(unsigned x)
{using namespace GenHelper;
z1=x; z2=(~x)^0x233333333U; z3=x^0x1234598766U; z4=(~x)+51;}
AIA inline int read()
{
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b;
}

struct Segnode {
	int lldis, lrdis, rldis, rrdis, midw;
	Segnode() {lldis = rrdis = lrdis = rldis = midw = -1;}
	Segnode(int lldis, int lrdis, int rldis, int rrdis, int midw)
		: lldis(lldis), lrdis(lrdis), rldis(rldis), rrdis(rrdis), midw(midw) {}
	AIA inline Segnode operator + (const Segnode& b) const {
		if (!~lldis) return b;
		if (!~b.lldis) return *this;
		Segnode res;
		int v1 = Min(b.lldis, b.rldis + midw), v2 = Min(b.lldis + midw, b.rldis), v3 = Min(b.lrdis, b.rrdis + midw), v4 = Min(b.lrdis + midw, b.rrdis);
		res.lldis = Min(lldis + v1, lrdis + v2);
		res.lrdis = Min(lldis + v3, lrdis + v4);
		res.rldis = Min(rldis + v1, rrdis + v2);
		res.rrdis = Min(rldis + v3, rrdis + v4);
		res.midw = b.midw;
		return res;
	}
};

namespace SqrtTree {
	Segnode pre[3][400005], suf[3][400005], mid[3][400005], seq[400005];
	int treeSize, idSeq[400005];
	const int S[4] = {1024, 32, 8, 4}, SL[4] = {10, 5, 3, 2};
	const int LV[20] = {4, 4, 3, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	AIA inline int Bid(int i, int Si) {return (Si<0?1:(i-1>>SL[Si])+1);}
	AIA inline int Bl(int i, int Si) {return (Si<0?1:(i-1<<SL[Si])+1);}
	AIA inline int Br(int i, int Si) {return (Si<0?treeSize:Min(i<<SL[Si],treeSize));}
	AIA inline int Midid(int Si, int l, int r) {
		int i, j;
		if (Si > 0) {
			i = (l - 1 & ((((Si == 0 ? treeSize : S[Si - 1]) + S[Si] - 1) >> SL[Si]) - 1)) + 1;
			j = (r - 1 & ((((Si == 0 ? treeSize : S[Si - 1]) + S[Si] - 1) >> SL[Si]) - 1)) + 1;
		} else {
			i = l;
			j = r;
		}
		return (i - 1) * (2 * (((Si == 0 ? treeSize : S[Si - 1]) + S[Si] - 1) >> SL[Si]) - i + 2) / 2 + j - i + 1 + (Si == 0 ? 0 : l >> SL[Si - 1] - SL[Si]) * (((Si == 0 ? treeSize : S[Si - 1]) + S[Si] - 1) >> SL[Si]) * ((((Si == 0 ? treeSize : S[Si - 1]) + S[Si] - 1) >> SL[Si]) + 1) / 2;
	}
	AIA inline void Build() {
		//for (int i = 2;i <= 1048575;i++) highbit[i] = highbit[i >> 1] + 1;
		for (int L = 0;L < 3;L++) {
			const int S1 = S[L], S0 = (L ? S[L - 1] : treeSize);
			for (int i = 1;i <= Bid(treeSize, L);i++) {
				pre[L][Bl(i, L)] = seq[Bl(i, L)];
				for (int j = Bl(i, L) + 1;j <= Br(i, L);j++) pre[L][j] = seq[j] + pre[L][j - 1];
			}
			for (int i = Bid(treeSize, L);i >= 1;i--) {
				suf[L][Br(i, L)] = seq[Br(i, L)];
				for (int j = Br(i, L) - 1;j >= Bl(i, L);j--) suf[L][j] = suf[L][j + 1] + seq[j];
			}
			int bcnt = (S0 + S1 - 1) / S1, idx = 0;
			for (int i = 1;i <= Bid(treeSize, L-1);i++) {
				int l = Bl(i, L-1), r = Br(i, L-1);
				for (int j = 1;j <= bcnt;j++) {
					++idx;
					mid[L][idx] = pre[L][Br(Bid(l, L) + j - 1, L)];
					for (int k = j + 1;k <= bcnt;k++) {
						mid[L][idx + 1] = pre[L][Br(Bid(l, L) + k - 1, L)] + mid[L][idx]; ++idx;
					}
				}
			}
		}
	}
	AIA inline Segnode Query(int l, int r) {
		int up = LV[31 - __builtin_clz((l - 1) ^ (r - 1))];
		int bl = Bid(l, up) + 1, br = Bid(r, up) - 1;
		if (bl > br) return pre[up][r] + suf[up][l];
		else return pre[up][r] + mid[up][Midid(up, bl, br)] + suf[up][l];
	}
}

namespace LCA {
	int st[21][N << 1], _time, dfn[N];
	inline void Dfs(int u) {
		int siz = g[u].size();
		st[0][++_time] = u;
		dfn[u] = _time;
		for (int i = 0;i < siz;i++) {
			Dfs(g[u][i].first);
			st[0][++_time] = u;
		}
	}
	AIA inline void PrefixST() {
		for (int i = 1;i <= 20;i++) {
			for (int j = 1;j <= _time;j++) {
				if (j + (1 << i) - 1 > _time) break;
				st[i][j] = (dep[st[i-1][j]]<dep[st[i-1][j+(1<<i-1)]]?st[i-1][j]:st[i-1][j+(1<<i-1)]);
			}
		}
	}
	AIA inline int Lca(int u, int v) {
		int l = LCA::dfn[u], r = LCA::dfn[v];
		if (l > r) swap(l, r);
		int k = 31 - __builtin_clz(r - l + 1);
		return (dep[st[k][l]]<dep[st[k][r-(1<<k)+1]]?st[k][l]:st[k][r-(1<<k)+1]);
	}
}
Segnode dp[N][21];

AIA inline void Read() {
	n = qread(); q = qread(); s = qread();
	for (int i = 2;i <= n;i++) {
		vis[fa_before[i] = qread()]++;
		w_before[i] = qread();
	}
	w_before[1] = 0x3f3f3f3f;
	for (int i = 1;i <= n;i++) {
		if (!vis[i]) leafid[++lcnt] = i;
	}
	//printf("lcnt = %d\n", lcnt);
}

inline int GetRoot(int v) {
	if (ref[v] == v) return v;
	return ref[v] = GetRoot(ref[v]);
}

AIA inline void Merge(int x, int y) {
	int u = GetRoot(x), v = GetRoot(y);
	if (u != v) {
		ref[v] = u;
		w_before[u] = Min(w_before[u], w_before[v]);
	}
}

AIA inline void Shrink() {
	for (int i = 1;i <= n;i++) ref[i] = i;
	for (int i = 1;i <= n;i++) {
		if (vis[fa_before[i]] == 1 && vis[i] <= 1) Merge(i, fa_before[i]);
	}
	for (int i = 1;i <= n;i++) ref[i] = GetRoot(i);
	memcpy(rtmp, ref, sizeof(rtmp));
	sort(rtmp + 1, rtmp + n + 1);
	tmpn = unique(rtmp + 1, rtmp + n + 1) - rtmp - 1;
	for (int i = 1;i <= n;i++) ref[i] = lower_bound(rtmp + 1, rtmp + tmpn + 1, ref[i]) - rtmp;
	//for (int i = 1;i <= n;i++) printf("%d ", ref[i]); puts("");
	for (int i = 2;i <= n;i++) {
		if (ref[i] != ref[fa_before[i]]) {
			//printf("%d->%d %d\n", ref[fa_before[i]] + 1, ref[i] + 1, w_before[rtmp[ref[i]]]);
			g[ref[fa_before[i]] + 1].push_back(make_pair(ref[i] + 1, w_before[rtmp[ref[i]]]));
		}
	}
	memset(costdown, 0x3f, sizeof(costdown));
	swap(n, tmpn);
	n++;
	g[1].push_back(make_pair(2, faWeight[2] = qread()));
	for (int i = 1;i <= tmpn;i++) {
		if (!vis[i]) costdown[ref[i] + 1] = Min(costdown[ref[i] + 1], qread());
	}
	//for (int i = 1;i <= n;i++) sort(g[i].begin(), g[i].end());
	// for (int i = 1;i <= n;i++) {
	// 	for (int j = 0;j < g[i].size();j++) printf("%d ", g[i][j].first);
	// 	puts("");
	// }
}

inline void FixWeight1(int u, int& lastw) {
	if (g[u].empty()) {
		//printf("u=%d d=%d\n", u, costdown[u]);
		lastw = Min(lastw, costdown[u]);
		return;
	}
	int siz = g[u].size();
	int sum = 0;
	for (int i = 0;i < siz;i++) {
		FixWeight1(g[u][i].first, g[u][i].second);
		//printf("%d->%d %d\n", u, g[u][i].first, g[u][i].second);
		sum += g[u][i].second;
	}
	if (sum < lastw) lastw = sum;
}

inline void FixWeight2(int u) {
	if (g[u].empty()) {
		costdown[u] = Min(costdown[u], faWeight[u]);
		return;
	}
	int siz = g[u].size(), sum = faWeight[u];
	for (int i = 0;i < siz;i++) sum += g[u][i].second;
	for (int i = 0;i < siz;i++) {
		g[u][i].second = Min(g[u][i].second, sum - g[u][i].second);
		//printf("%d->%d %d\n", u, g[u][i].first, g[u][i].second);
	}
	for (int i = 0;i < siz;i++) {
		faWeight[g[u][i].first] = g[u][i].second;
		FixWeight2(g[u][i].first);
	}
}

AIA inline void CalcEdge() {
	//for (int i = 1;i <= n;i++) printf("%d ", faWeight[i]); puts("");
	for (int i = 2;i <= n;i++) {
		int siz = g[i].size(), presum = 0;
		for (int j = 0;j < siz;j++) dgr[i] += g[i][j].second;
		for (int j = 0;j < siz;j++) {
			fapresum[g[i][j].first] = presum;
			dp[g[i][j].first][0].lldis = Min(presum, dgr[i] - presum + faWeight[i]);
			dp[g[i][j].first][0].lrdis = Min(presum + faWeight[i], dgr[i] - presum);
			dp[g[i][j].first][0].rldis = Min(g[i][j].second + presum, dgr[i] - presum - g[i][j].second + faWeight[i]);
			dp[g[i][j].first][0].rrdis = Min(g[i][j].second + presum + faWeight[i], dgr[i] - presum - g[i][j].second);
			dp[g[i][j].first][0].midw = faWeight[i];
			presum += g[i][j].second;
		}
	}
	//for (int i = 1;i <= n;i++) printf("%d %d %d %d\n", dp[i][0].lldis, dp[i][0].lrdis, dp[i][0].rldis, dp[i][0].rrdis);
}

inline void Dfs1(int u) {
	for (int j = 1;(1 << j) <= dep[u];j++) {
		fa[u][j] = fa[fa[u][j - 1]][j - 1];
		dp[u][j] = dp[u][j - 1] + dp[fa[u][j - 1]][j - 1];
	}
	int siz = g[u].size();
	for (int i = 0;i < siz;i++) {
		dep[g[u][i].first] = dep[u] + 1;
		fa[g[u][i].first][0] = u;
		Dfs1(g[u][i].first);
		if (trh[son[u]] < trh[g[u][i].first]) son[u] = g[u][i].first;
	}
	trh[u] = trh[son[u]] + 1;
}

inline void Dfs2(int u, int tp) {
	dfn[u] = ++_time;
	top[u] = tp;
	if (son[u]) Dfs2(son[u], tp);
	int siz = g[u].size();
	for (int i = 0;i < siz;i++) {
		if (g[u][i].first == son[u]) continue;
		Dfs2(g[u][i].first, g[u][i].first);
	}
	pst[u] = ++_time;
}

inline void Dfs3(int u) {
	if (u == top[u]) {
		if (trh[u] <= 14) return;
		int updis = Min(trh[u] - 1, dep[u] - 1);
		lid[u] = SqrtTree::treeSize + updis + 1;
		int tmp = u;
		for (int i = 1;i <= updis;i++) {
			tmp = fa[tmp][0];
			SqrtTree::seq[lid[u] - i] = dp[tmp][0];
			SqrtTree::idSeq[lid[u] - i] = tmp;
		}
		tmp = u;
		for (int i = 1;i <= trh[u];i++) {
			SqrtTree::idSeq[lid[u] + i - 1] = tmp;
			SqrtTree::seq[lid[u] + i - 1] = dp[tmp][0];
			tmp = son[tmp];
		}
		SqrtTree::treeSize += updis + trh[u];
	}
	int siz = g[u].size();
	for (int i = 0;i < siz;i++) {
		if (g[u][i].first == fa[u][0]) continue;
		Dfs3(g[u][i].first);
	}
}

AIA inline void Prefix() {
	Dfs3(1);
	//printf("%d\n", SqrtTree::treeSize);
	SqrtTree::Build();
}

AIA inline Segnode Upquery(int &u, int k) {
	if (!k) return Segnode(0, 0, 0, 0, 0);
	Segnode ans;
	for (;k;k^=(k&-k)) {
		int tmp = 31 - __builtin_clz(k&-k);
		ans = ans + dp[u][tmp];
		u = fa[u][tmp];
	}
	return ans;
}

AIA inline Segnode kUpQuery(int &u, int k) {
	if (!k) return Segnode(0, 0, 0, 0, 0);
	int tmp = 31 - __builtin_clz(k);
	Segnode ans = dp[u][tmp];
	u = fa[u][tmp];
	k ^= (1 << tmp);
	if (!k) return ans;
	if (__builtin_popcount(k) <= 4) return ans + Upquery(u, k);
	int r = lid[top[u]] + dep[u] - dep[top[u]], l = r - k;
	u = SqrtTree::idSeq[l];
	return ans + SqrtTree::Query(l + 1, r);
}

#define Dist(i,j,l) Min(Abs(i - j), dgr[l] + faWeight[l] - Abs(i - j))

AIA inline void Solve() {
	if (s != -1) srand(s);
	int lastans = 0, finalans = 0;
	long long finalsum = 0;
	bool flag = 0;
	while (q--) {
		if (s != -1) {
			finalans ^= lastans;
			finalsum += lastans;
		} else if (flag) printf("%d\n", lastans);
		else flag = 1;
		int u, v;
		if (s != -1) {
			int tmpu = (read() ^ lastans)%tmpn+1, tmpv = (read() ^ lastans)%tmpn+1;
			//printf("%d %d\n", tmpu, tmpv);
			u = (ref[tmpu]) + 1;
			v = (ref[tmpv]) + 1;
		} else {
			u = (ref[qread() ^ lastans]) + 1;
			v = (ref[qread() ^ lastans]) + 1;
		}
		if (u == v) {
			lastans = 0;
			continue;
		}
		if (dep[u] < dep[v]) swap(u, v);
		if (dfn[v] <= dfn[u] && dfn[u] <= pst[v]) {
			Segnode res = kUpQuery(u, dep[u] - dep[v] - 1);
			//printf("%d %d %d %d\n", res.lldis, res.lrdis, res.rldis, res.rrdis);
			lastans = Min(Min(Min(res.lldis, res.lrdis), res.rldis), res.rrdis);
		} else {
			int l = LCA::Lca(u, v);
			Segnode resu = kUpQuery(u, dep[u] - dep[l] - 1);
			Segnode resv = kUpQuery(v, dep[v] - dep[l] - 1);
			//printf("u=%d v=%d\n", u, v);
			//printf("%d %d %d %d\n%d %d %d %d\n", resu.lldis, resu.lrdis, resu.rldis, resu.rrdis, resv.lldis, resv.lrdis, resv.rldis, resv.rrdis);
			int idul = fapresum[u], idur = fapresum[u] + faWeight[u], idvl = fapresum[v], idvr = fapresum[v] + faWeight[v];
			//printf("%d %d %d %d\n", idul, idur, idvl, idvr);
			int utol = Min(resu.lldis, resu.rldis), utor = Min(resu.lrdis, resu.rrdis), vtol = Min(resv.lldis, resv.rldis), vtor = Min(resv.lrdis, resv.rrdis);
			int ans = utol + vtol + Dist(idul, idvl, l);
			ans = Minll(ans, utol + vtor + Dist(idul, idvr, l));
			ans = Minll(ans, utor + vtol + Dist(idur, idvl, l));
			ans = Minll(ans, utor + vtor + Dist(idur, idvr, l));
			lastans = ans;
		}
	}
	if (s != -1) printf("%d %lld\n", finalans ^ lastans, finalsum + lastans);
	else printf("%d\n", lastans);
}

int main() {
	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
	memset(hd, -1, sizeof(hd));
	Read();
	Shrink();
	//puts("FIX1");
	FixWeight1(2, g[1][0].second);
	//puts("FIX2");
	FixWeight2(2);
	CalcEdge();
	dep[1] = 1;
	Dfs1(1);
	Dfs2(1, 1);
	Prefix();
	LCA::Dfs(1);
	LCA::PrefixST();
	//printf("T=%d\n", clock() - t);
	Solve();
	#ifdef CFA_44
	while (1);
	#endif
	return 0;
}

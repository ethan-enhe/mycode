// LUOGU_RID: 136156831
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define mp(x, y) make_pair(x, y)
#define fro(i, x, y) for(int i = (x);i <= (y);i++)
#define pre(i, x, y) for(int i = (x);i >= (y);i--)

typedef long long ll;
typedef __int128 lll;
typedef unsigned int uint;
typedef pair<int, int> PII;
typedef unsigned long long ull;

const int N = 1000010;
const int mod = 998244353;

int n, m, cnt, a[N], siz[N], head[N];
int mx1[N], mx2[N], d[N]; ll ans;
string s;
struct edge { int to, nxt; } e[N * 2];
inline void add(int x, int y)
{
	e[++cnt] = {y, head[x]}, head[x] = cnt;
	e[++cnt] = {x, head[y]}, head[y] = cnt;
}
inline void dfs1(int p, int fa)
{
	if(a[p]) siz[p] = 1; else d[p] = mod;
	for(int i = head[p];i;i = e[i].nxt) if(e[i].to != fa)
	{
		int v = e[i].to; dfs1(v, p), siz[p] += siz[v];
		if(mx1[v] + 1 > mx1[p]) mx2[p] = mx1[p], mx1[p] = mx1[v] + 1;
		else if(mx1[v] + 1 > mx2[p]) mx2[p] = mx1[v] + 1;
		if(siz[v]) d[p] = min(d[p], mx1[v] + 1);
	}
}
inline void dfs2(int p, int fa)
{
	ans = ans + max(0, min(mx1[p], mx2[p] + 2) - d[p]);
	for(int i = head[p];i;i = e[i].nxt) if(e[i].to != fa)
	{
		int v = e[i].to, s = (mx1[v] + 1 == mx1[p] ? mx2[p] + 1 : mx1[p] + 1);
		if(s > mx1[v]) mx2[v] = mx1[v], mx1[v] = s;
		else if(s > mx2[v]) mx2[v] = s;
		if(siz[1] - siz[v]) d[v] = min(d[v], s);
		dfs2(v, p);
	}
}

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	fro(i, 1, n - 1)
	{
		int x, y;
		cin >> x >> y;
		add(x, y);
	}
	cin >> s;
	fro(i, 1, n)
		a[i] = s[i - 1] - '0';
	dfs1(1, 0), dfs2(1, 0);
	cout << ans + 1 << "\n";
	return 0;
}

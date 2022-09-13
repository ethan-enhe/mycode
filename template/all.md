# 模板

## 流

```
e3b0 | // File:             mcmf.cpp
e3b0 | // Author:           ethan
e3b0 | // Created:          01/07/22
e3b0 | // Description:      mcmf
e3b0 |
a2f9 | #include <bits/stdc++.h>
e3b0 |
790b | using namespace std;
e3b0 |
e3b0 | // {{{ flow
e3b0 | // 原始版费用流
6798 | template <const int MXN, typename T = int>
f3fa | struct raw_flow {
bb6d |     const T INF = numeric_limits<T>::max();
e67e |     struct edge {
8664 |         int v, o;
9095 |         T c, w;
e9e5 |         edge(int _v, T _c, T _w, int _o) : v(_v), o(_o), c(_c), w(_w) {}
df39 |     };
9054 |     vector<edge> g[MXN];
c98c |     queue<int> q;
98f2 |     int s, t, cure[MXN];
c1dd |     bool vis[MXN];
962d |     T dis[MXN];
2034 |     void addedge(int u, int v, T c, T w) {
8c8d |         g[u].push_back(edge(v, c, w, g[v].size()));
ecbb |         g[v].push_back(edge(u, 0, -w, g[u].size() - 1));
d10b |     }
fa43 |     void adduedge(int u, int v, T c) {
c26d |         g[u].push_back(edge(v, c, 1, g[v].size()));
9aab |         g[v].push_back(edge(u, 0, 1, g[u].size() - 1));
d10b |     }
f933 |     bool spfa() {
0050 |         for (int i = 0; i < MXN; i++) dis[i] = INF, cure[i] = 0;
94f2 |         dis[s] = 0;
dc94 |         q.push(s);
e1b4 |         while (!q.empty()) {
2abc |             int p = q.front();
d22c |             q.pop();
b5f3 |             vis[p] = 0;
99eb |             for (edge &nx : g[p])
2b43 |                 if (nx.c && dis[nx.v] > dis[p] + nx.w) {
a54f |                     dis[nx.v] = dis[p] + nx.w;
c0e0 |                     if (!vis[nx.v]) {
a7bf |                         vis[nx.v] = 1;
538e |                         q.push(nx.v);
d10b |                     }
d10b |                 }
d10b |         }
3e48 |         return dis[t] != INF;
d10b |     }
2403 |     T dinic(int p, T fi) {
b642 |         if (p == t) return fi;
e49f |         T fo = 0;
82e7 |         vis[p] = 1;
c2d6 |         for (int &i = cure[p]; i < (int)g[p].size(); i++) {
ba9a |             edge &nx = g[p][i];
a132 |             if (dis[nx.v] == dis[p] + nx.w && !vis[nx.v] && nx.c) {
eb12 |                 T delt = dinic(nx.v, min(fi - fo, nx.c));
7238 |                 if (delt) {
f447 |                     nx.c -= delt;
2350 |                     g[nx.v][nx.o].c += delt;
991d |                     fo += delt;
435a |                     if (fi == fo) return vis[p] = 0, fo;
7a6d |                 } else
b122 |                     dis[nx.v] = -1;
d10b |             }
d10b |         }
42e1 |         return vis[p] = 0, fo;
d10b |     }
a3a8 |     pair<T, T> run(int _s, int _t) {
a55e |         s = _s, t = _t;
9a6a |         pair<T, T> res = {0, 0};
9976 |         while (spfa()) {
85de |             T delt = dinic(s, INF);
3b0b |             res.first += delt, res.second += delt * dis[t];
d10b |         }
f4f0 |         return res;
d10b |     }
df39 | };
e3b0 | // 封装的上下界网络流
6798 | template <const int MXN, typename T = int>
0749 | struct lim_flow {
bb6d |     const T INF = numeric_limits<T>::max();
f04e |     raw_flow<MXN, T> f;
0fa7 |     T deg[MXN];
038f |     pair<T, T> res;
e3b0 |     // 加边函数 起点 终点 流量下界 流量上界 [是否有负环=false]
9676 |     void addedge(int u, int v, T l, T r, T w, bool cycle = 0) {
adf5 |         if (cycle && w < 0) {
aece |             w = -w;
abe1 |             swap(v, u), swap(l, r);
7de1 |             l = -l, r = -r;
d10b |         }
16f2 |         deg[u] -= l, deg[v] += l;
bb12 |         res.second += l * w;
fd82 |         f.addedge(u, v, r - l, w);
d10b |     }
e3b0 |     // 加单位边的函数（只求最大流，不求费用的时候用这个加边，跑的比较快）
5d87 |     void adduedge(int u, int v, T l, T r) {
16f2 |         deg[u] -= l, deg[v] += l;
bfc9 |         f.adduedge(u, v, r - l);
d10b |     }
e3b0 |     // 超级源点 超级汇点 源点 汇点 [选项=1]
e3b0 |     // 选项：
e3b0 |     // 0->最小费用可行流
e3b0 |     // 1->最小费用最大流
e3b0 |     // 2->最小费用最小流
e3b0 |     // 返回值 {流量，费用} 如果没有可行流返回 {-1,-1}
fa21 |     pair<T, T> run(int super_s, int super_t, int s, int t, int opt = 1) {
57a0 |         T all = 0;
cd9d |         for (int i = 0; i < MXN; i++) {
a95e |             if (deg[i] > 0)
06da |                 f.addedge(super_s, i, deg[i], 0), all += deg[i];
4ee7 |             else if (deg[i] < 0)
d229 |                 f.addedge(i, super_t, -deg[i], 0);
d10b |         }
b5fc |         f.addedge(t, s, INF, 0);
c60e |         pair<T, T> tres = f.run(super_s, super_t);
3e6d |         if (tres.first != all) return {-1, -1};
ad9b |         res.second += tres.second;
6759 |         res.first += f.g[s].back().c;
f867 |         f.g[s].back().c = 0;
d30e |         f.g[t].back().c = 0;
1f71 |         if (opt == 1) {
0911 |             tres = f.run(s, t);
18a1 |             res.first += tres.first, res.second += tres.second;
9551 |         } else if (opt == 2) {
1696 |             tres = f.run(t, s);
cb3e |             res.first -= tres.first, res.second += tres.second;
d10b |         }
f4f0 |         return res;
d10b |     }
df39 | };
e3b0 | // }}}
e3b0 |
565c | int main() {
7145 |     return 0;
d10b | }
```

## 高斯消元

```
e3b0 | //[SDOI2006]线性方程组
a2f9 | #include <bits/stdc++.h>
790b | using namespace std;
59b3 | const int MXN = 52;
aac8 | const double eps = 1e-8;
b081 | int n;
d336 | double arr[MXN][MXN], tmp[MXN];
003d | inline bool is0(double x) { return fabs(x) <= eps; }
8861 | inline void eli(double *a, double *b, int ind) {
7054 |     if (is0(a[ind]) || is0(b[ind])) return;
fdaf |     double rate = a[ind] / b[ind];
8e54 |     for (int i = ind; i <= n + 1; i++) a[i] -= rate * b[i];
d10b | }
e3ed | inline int insert(double *eq) {
fd5c |     for (int i = 1; i <= n; i++)
2161 |         if (!is0(eq[i])) {
21e6 |             if (!is0(arr[i][i]))
cce5 |                 eli(eq, arr[i], i);
7a1a |             else {
28dd |                 for (int j = i + 1; j <= n; j++) eli(eq, arr[j], j);
71a0 |                 for (int j = 1; j < i; j++) eli(arr[j], eq, i);
2bb6 |                 for (int j = i; j <= n + 1; j++) arr[i][j] = eq[j];
31a0 |                 return 1;
d10b |             }
d10b |         }
680a |     return is0(eq[n + 1]) ? 0 : -1;
d10b | }
e3b0 |
565c | int main() {
33c4 |     scanf("%d", &n);
8e8c |     bool infsol = 0;
5c1f |     for (int i = 1; i <= n; i++) {
71db |         for (int j = 1; j <= n + 1; j++) scanf("%lf", tmp + j);
5470 |         int tres = insert(tmp);
7999 |         if (tres == -1) return printf("-1"), 0;
8f32 |         infsol |= !tres;
d10b |     }
6c7a |     if (infsol)
498a |         printf("0");
7dd5 |     else
9c8b |         for (int i = 1; i <= n; i++) printf("x%d=%.2f\n", i, arr[i][n + 1] / arr[i][i] + eps);
e3b0 |
7145 |     return 0;
d10b | }
```

## SA

```
a2f9 | #include <bits/stdc++.h>
790b | using namespace std;
4aeb | const int MXN = 2e5 + 5, LG = 31 - __builtin_clz(MXN);
4c1c | int t, n, tot;
2d9a | char str[MXN];
e3b0 |
87fe | namespace SA {
80d4 | typedef int arrn[MXN];
614b | arrn sa, rk, tmp, ork, cnt;
69ad | int h[LG + 1][MXN];
275e | inline bool cmp(int x, int y, int w) { return ork[x] == ork[y] && ork[x + w] == ork[y + w]; }
2c45 | template <typename T>
bad5 | inline void init(int n, int m, T *arr) {
d837 |     for (int i = 1; i <= m; i++) cnt[i] = 0;
d916 |     for (int i = 1; i <= n; i++) cnt[rk[i] = arr[i]]++;
85ac |     for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
305b |     for (int i = n; i; i--) sa[cnt[rk[i]]--] = i;
0922 |     for (int w = 1; w <= n; w <<= 1) {
a7ee |         int ind = 0;
c7a8 |         for (int i = n - w + 1; i <= n; i++) tmp[++ind] = i;
fd5c |         for (int i = 1; i <= n; i++)
c2c2 |             if (sa[i] > w) tmp[++ind] = sa[i] - w;
d837 |         for (int i = 1; i <= m; i++) cnt[i] = 0;
1df0 |         for (int i = 1; i <= n; i++) cnt[rk[i]]++;
85ac |         for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
5061 |         for (int i = n; i; i--) sa[cnt[rk[tmp[i]]]--] = tmp[i], ork[i] = rk[i];
7b65 |         m = 0;
5aea |         for (int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? m : ++m;
e453 |         if (m == n) break;
d10b |     }
e3b0 |
d835 |     arr[n + 1] = -1;
0bb4 |     for (int i = 1, lcp = 0; i <= n; i++) {
4869 |         lcp -= !!lcp;
95ab |         while (arr[i + lcp] == arr[sa[rk[i] - 1] + lcp]) ++lcp;
c363 |         h[0][rk[i]] = lcp;
d10b |     }
aad6 |     for (int i = 1; i <= LG; i++)
7cac |         for (int w = 1 << (i - 1), j = n - (1 << i) + 1; j > 0; j--) h[i][j] = min(h[i - 1][j], h[i - 1][j + w]);
d10b | }
4a44 | inline int lcp(int x, int y) {
5069 |     x = rk[x], y = rk[y];
f144 |     assert(x != y);
0c62 |     if (x > y) swap(x, y);
557a |     ++x;
1062 |     int lg = 31 - __builtin_clz(y - x + 1);
7eb9 |     return min(h[lg][x], h[lg][y - (1 << lg) + 1]);
d10b | }
d10b | } // namespace SA
e3b0 |
565c | int main() {
2bf3 |     scanf("%d", &t);
73d1 |     while (t--) {
33c4 |         scanf("%d", &n);
8a9b |         tot = n * 2 + 2;
5c1f |         for (int i = 1; i <= n; i++) {
31e3 |             char x;
ac0b |             do
82c1 |                 x = getchar();
18ee |             while (x != 'a' && x != 'b');
adf6 |             str[i] = str[tot - i] = x;
d10b |         }
bdde |         str[n + 1] = '#';
8ec9 |         str[tot] = 0;
abe0 |         SA::init(tot - 1, 130, str);
83bd |         int ans = 0;
fd5c |         for (int i = 1; i <= n; i++)
bac4 |             for (int j = i << 1; j <= n; j += i)
82a7 |                 ans = max(ans, (SA::lcp(tot - j, tot - j + i) + SA::lcp(j, j - i) + i - 1) / i);
d054 |         printf("%d\n", ans);
d10b |     }
7145 |     return 0;
d10b | }
```

## 李超树

```
a2f9 | #include <bits/stdc++.h>
990c | #define fi first
1eee | #define se second
a4fb | #define mp make_pair
790b | using namespace std;
8f5d | typedef long long ll;
266c | typedef pair<ll, ll> pr;
0825 | const ll MXN = 1e5;
0373 | const ll NR = 1e10;
00a9 | const ll INF = 1e18;
e3b0 |
79e8 | struct node {
f122 |     ll ls, rs;
2226 |     pr line;
48e7 | } t[MXN * 100];
f10e | ll rt, nodec;
d001 | inline ll f(pr line, ll x) { return line.fi * x + line.se; }
f99e | inline ll nnode() { return t[++nodec].line = mp(0, -INF), nodec; }
4390 | inline void mod(ll &p, ll l, ll r, pr ml) {
bbce |     ll mid = (l + r) >> 1;
fc35 |     if (!p) p = nnode();
04d3 |     if (f(ml, mid) > f(t[p].line, mid)) swap(ml, t[p].line);
89d6 |     if (l == r) return;
99fd |     ml.fi < t[p].line.fi ? mod(t[p].ls, l, mid, ml) : mod(t[p].rs, mid + 1, r, ml);
d10b | }
d52f | inline ll que(ll p, ll l, ll r, ll qx) {
b392 |     if (!p || l == r) return f(t[p].line, qx);
bbce |     ll mid = (l + r) >> 1;
c9e6 |     return max(f(t[p].line, qx), qx > mid ? que(t[p].rs, mid + 1, r, qx) : que(t[p].ls, l, mid, qx));
d10b | }
979c | int main() { return 0; }
```

# 重要

## 重要公式

### 矩阵树

#### 无向图

**矩阵形式：**

$A(i,i)=\deg(i)$，$A(i,j)=-\operatorname {cnt}(i,j)\text{（i 到 j 的边权/重边数量）}$

#### 有向图

**矩阵形式：**

- 内向树：$A_{out}(i,i)=\deg_{out}(i)$，$A(i,j)=-\operatorname {cnt}(i,j)\text{（i 到 j 的边权/重边数量）}$
- 外向树：$A_{in}(i,i)=\deg_{in}(i)$，$A(i,j)=-\operatorname {cnt}(i,j)\text{（i 到 j 的边权/重边数量）}$

以 $i$ 为根的生成树数量为 $A$ 删去第 i 行以及第 i 列，之后求行列式。

### 行列式

**定义式：**
$$\operatorname{det}(A)=\sum_{排列 P} (-1)^\text{P 中逆序对数}\prod_{i=1}^{n} a_{i, P(i)} $$

- 交换两行，结果取反
- 某行乘 k，结果乘 k
- 某行减去另一行乘一个系数，结果不变，直观理解：

![](https://pic.imgdb.cn/item/6256da5d239250f7c5a956ee.jpg)

## trick

- dp 提前算贡献
- 时光倒流（常用于从环、序列上删数，且过程与所删数当前的前驱、后继相关的时候，或者贪心的候选集合递减（蔬菜））
- 模拟最大流转模拟最小割
- 找不变量（交换差分，逆序对个数奇偶性....）
- 分阶段 dp（寿司晚宴&皮配）
- prim 最小生成树/考虑kruskal过程，是否有一些边无效
- 按余数分类（定长区间异或 1）
- 消消乐 dp
- n 选 k 使得和最大，n 很大，k 很小，考虑排除没有可能的方案（CF1572D）
- 切糕模型
- 子树合并 dp 复杂度
- 取关键点（字符串循环节/答案对应的长度不超过 $B$，并支持 $n^2$ 计算，则可取若干关键区间计算 $[1,2B],[B,3B],[2B,4B]\cdots$）
- dp 变为 dag 路径计数（然后可以搞一些操作，比如在反图上跑）
- 二进制分组斜率优化（当斜率不递增时，可以分别开若干个大小为 $2^0,2^1,2^2\cdots$ 的单调栈，加的时候先在最小的里面加，一旦大小撑爆了就跟下一个单调栈合并）
- i 行 j 列转化为 i 行向 j 列连边。
- 在生成树上构造。
- 点减边容斥。求连通块个数转化为求包含每个点连通块个数-包含每个边连通块个数

### 数论

- 多次杜教筛复杂度依然是 $n^{\frac 23}$
- 反演的时候发现用不了整除分块多换换元

## 我的常犯错误

### 做题策略（惨痛教训）

1. 开始把题全看一遍（15 min 左右）
2. 开始想题前手玩样例（5 min 以内可以玩的话）
3. 除非分数有保障，想题超过 30 min 考虑换换，不要有心理负担，暴力也能搞好多分
4. 思路较复杂，且不好调的题，重新回忆下算法，不一定是写错了，可能是假了。不要一心认为某nb做法是对的，其他做法是假的。

### 重大错误

#### 2021省选

$$\large{\text{我 tm {\color{purple}RE} 了！}}$$

- 爆搜不要瞎加剪枝，引起不必要的 RE，导致 60+分 -> 0分
- 暴力拼起来的题全打挂
- 想出算法开始打，打完发现算法假，灵机一动新想法，又写了个假算法。
- 诸如两个数的和，这类边界特判要特别注意，最大值是原来两倍

#### 2020NOIP

- 求 lcm 注意要 **先除后乘**

### NOI 笔试易错

- `RAM=Random Access Memory`，`ROM=Read-Only Memory` 分不清
- Lazarus 是 Pascal IDE，GUIDE 和 Anjuta（AG）是 C++ IDE ~~（然而我用 vim）~~

### STL

- `multimap` 的 `erase(x)` 会把所有值等于 x 的删掉

### 细节

- 建图把无向图建成有向图
- 组合数计算函数忘记特判 `x>y`，`x,y<0`，开 O2 后 UB 爆零了。。
- 预处理阶乘/扫描线分开存储修改查询时，数组忘 **开两倍**

### 数据结构

- 线段树着急写错左右儿子
- 值域线段树 `pushdown` 忘记把空节点新建出来

### fhqTreap 专栏

- `pushdown` 时要 **判空节点**
- 按 `rank` 分裂时应该判断 `sz[ls]+1>=rank`
- `push_up` 时 `sz[p]=sz[ls]+sz[rs]+1` 忘记写 `+1`
- 把 `split` 复制粘贴改成 `splitrk` 忘记改递归的函数名
- `split(rt,b,c)` 之后应该 `split(b,a,b)`，写成 `split(rt,a,b)`

### 算法

- 求树的直径时忘记把父亲的跟儿子取 max
- 线段树合并忘记 **判断叶子节点**
- 点分治忘记考虑 **分治中心的贡献**
- 扫描线先改后查
- **莫队排序写挂**
- AC 自动机，在把 fail 树上子树加起来的时候，必须**显式建图**，倒着遍历所有节点，并加到自己的 father 上不对
- dinic 中 bfs 的 queue 忘记清零
- 写线性基形式的高斯消元时，消元这一步：

```cpp
inline void eli(double *x,double *y,int ind){
    if(is0(x[ind]))return;
    double rate=x[ind]/y[ind];
    for(int i=0;i<=ind;i++)//第四行
        x[i]-=y[i]*rate;
}
```

- 可撤销单调栈的时候，不管 top 增加减少，都要记录数组原来的值，并复原。

第 4 行**不可以**循环到 n，否则会**被卡精度**。

### 其他

- 函数内开大数组 RE 了
- 对拍时要把 `std` 中的小数据暴力注释掉
- 编译不会开 O2 的命令 `g++ -O2 -Wall *.cpp -o *`

### Tarjan 专栏

- 有向图建成无向图
- 缩完点后建图把原来的点和缩成的点搞混。。。
- `instack` 数组应该在弹栈时置零

#### 判断条件

- 强连通：`dfn[p]==low[p]`，弹到 `p`。
- 点双：`low[nx]==dfn[p]`，则如果 `p` 不是搜索树的根，或者 `p` 在搜索树上有多个儿子，`p` 为割点，弹栈直到 `nx`（`nx` 要保留，因为割点可能在多个点双中）
- 边双：`dfn[p]==low[p]`，弹到 `p`，当前边为桥。

## 总是忘记的

- sa 中求 h 数组时：`h[rk[i]]>=h[rk[i-1]]-1`
- 2-SAT 中最终应该选择编号大的强连通分量

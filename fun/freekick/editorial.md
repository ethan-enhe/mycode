# 思路：

## 暴力

首先考虑和值域相关做法。
设 $dp(i,j)$ 表示 $y_i$ 是否可以等于 $j$。

则转移方式显然：

- $dp(i+1,j)\gets dp(i,j) \vee dp(i,j-1) \vee dp(i,j+1)$
- 如果有任何一个限制使得 $A_i$ 不可能等于 $j$,则将 $dp(i,j)$ 置为 $0$。

复杂度 $O(nw)$。

## 优化 1

不难发现，$dp(i,\cdots)$ 中必然有 $O(m)$ 个 $dp$ 值为 $1$ 的连续段。随着 $i$ 的增加，这些连续段的左右端点都会向外扩张 $1$ 单位的长度。不难维护，复杂度 $O(nm)$。

## 优化 2

因为 $n$ 很大，而上述优化中需要进行 $n$ 轮“连续段扩张 $1$”的转移过程，每一轮的转移都是非常机械的，而只有 $m$ 轮是涉及到限制的，考虑如何加速其余的 $n-m$ 次转移。

考虑 $dp$ 值为 $1$ 的连续段在转移中会不断扩张，如果有两个连续段相交，则它们会合并。

这个合并的过程是不太好维护的（至少我是这么觉得）。所以还不如维护 $dp$ 值为 $0$ 的连续段，这些连续段会不断缩小，直到消失，同时，缩小过程中连续段的相对位置不变，这样就相对好维护一点。

剩下的就是数据结构问题，可以直接开一个 `set`，里头维护若干二元组 $l_j,r_j$，表示在 $dp$ 转移到 $i$ 的时候该连续段为 $[l_j+i,r_j-i]$。

然后遇到一条限制 $i,l,r$，就取出 `set` 中当前与 $[l,r]$ 相交的所有区间，全都 `erase` 掉，并用来更新 $[l,r]$ 然后把这个区间插到 `set` 里，略有细节，详见实现。

```cpp
#include <bits/stdc++.h>

using namespace std;
#define fi first
#define se second

using ll = long long;
using pi = pair<ll, ll>;
const char nl = '\n';
const ll INF = 1e18;

ll t, n, m, r;
struct lim {
    ll i;
    pi rng;
};
vector<lim> lims;
set<pi> cant_vis;

bool vanish(pi x, ll t) { return x.se - x.fi < (t << 1); }
pi shrink(pi x, ll t) { return {x.fi + t, x.se - t}; }
bool intersec(pi x, pi y) {
    if (x.fi > y.fi) swap(x, y);
    return x.se + 1 >= y.fi;
}

void ins(lim x) {
    if (x.rng.fi == 0) x.rng.fi = -INF;
    if (x.rng.se == r) x.rng.se = INF;
    pi ori = shrink(x.rng, -x.i);
    //找到第一个左端点被覆盖的
    //--itl为第一个在当前区间左的
    auto itl = cant_vis.lower_bound({ori.fi, -INF});
    while (1) {
        if (itl == cant_vis.begin()) break;
        if (!vanish(*(--itl), x.i)) {
            ++itl;
            break;
        }
    }
    // itr为第一个在当前区间右的
    auto itr = (itl != cant_vis.begin() ? prev(itl) : itl);
    while (1) {
        if (itr == cant_vis.end() || (!vanish(*itr, x.i) && itr->se > ori.se)) break;
        ++itr;
    }
    if (itl != cant_vis.begin())
        if (intersec(x.rng, shrink(*prev(itl), x.i))) ori.fi = (--itl)->fi;
    if (itr != cant_vis.end()) {
        if (intersec(x.rng, shrink(*itr, x.i))) {
            ori.se = itr->se;
            ++itr;
        }
    }
    cant_vis.erase(itl, itr);
    cant_vis.insert(ori);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> m >> r;
        lims.resize(m);
        cant_vis.clear();
        for (auto &i : lims) cin >> i.i >> i.rng.fi >> i.rng.se;
        sort(lims.begin(), lims.end(), [](lim x, lim y) { return x.i < y.i; });
        for (auto &i : lims) ins(i);

        bool f = 1;
        for (auto &i : cant_vis) {
            auto tmp = shrink(i, n);
            if (tmp.fi <= 0 && tmp.se >= r) {
                f = 0;
                break;
            }
        }
        cout << (f ? "YES" : "NO") << nl;
    }
    return 0;
}
```

// File:             mcmf.cpp
// Author:           ethan
// Created:          01/07/22
// Description:      mcmf

#include <bits/stdc++.h>
using namespace std;

// {{{ flow
// 原始版费用流
template <const int MXN, typename T = int>
struct flow {
    const T INF = numeric_limits<T>::max();
    struct edge {
        int v, o;
        T c, w;
        edge(int _v, T _c, T _w, int _o) : v(_v), c(_c), w(_w), o(_o) {}
    };
    vector<edge> g[MXN];
    queue<int> q;
    int s, t, cure[MXN];
    bool vis[MXN];
    T dis[MXN];
    void addedge(int u, int v, T c, T w) {
        g[u].push_back(edge(v, c, w, g[v].size()));
        g[v].push_back(edge(u, 0, -w, g[u].size() - 1));
    }
    void adduedge(int u, int v, T c) {
        g[u].push_back(edge(v, c, 1, g[v].size()));
        g[v].push_back(edge(u, 0, 1, g[u].size() - 1));
    }
    bool spfa() {
        for (int i = 1; i < MXN; i++) dis[i] = INF, cure[i] = 0;
        dis[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            vis[p] = 0;
            for (edge &nx : g[p])
                if (nx.c && dis[nx.v] > dis[p] + nx.w) {
                    dis[nx.v] = dis[p] + nx.w;
                    if (!vis[nx.v]) {
                        vis[nx.v] = 1;
                        q.push(nx.v);
                    }
                }
        }
        return dis[t] != INF;
    }
    T dinic(int p, T fi) {
        if (p == t) return fi;
        T fo = 0;
        vis[p] = 1;
        for (int &i = cure[p]; i < (int)g[p].size(); i++) {
            edge &nx = g[p][i];
            if (dis[nx.v] == dis[p] + nx.w && !vis[nx.v] && nx.c) {
                T delt = dinic(nx.v, min(fi - fo, nx.c));
                if (delt) {
                    nx.c -= delt;
                    g[nx.v][nx.o].c += delt;
                    fo += delt;
                    if (fi == fo) return vis[p] = 0, fo;
                } else
                    dis[nx.v] = -1;
            }
        }
        return vis[p] = 0, fo;
    }
    pair<T, T> run(int _s, int _t) {
        s = _s, t = _t;
        pair<T, T> res = {0, 0};
        while (spfa()) {
            T delt = dinic(s, INF);
            res.first += delt, res.second += delt * dis[t];
        }
        return res;
    }
};
// 封装的上下界网络流
template <const int MXN, typename T = int>
struct limflow {
    const T INF = numeric_limits<T>::max();
    flow<MXN, T> f;
    T deg[MXN];
    pair<T, T> res;
    // 加边函数 起点 终点 流量下界 流量上界 [是否有负环=false]
    void addedge(int u, int v, T l, T r, T w, bool cycle = 0) {
        if (cycle && w < 0) {
            w = -w;
            swap(v, u), swap(l, r);
            l = -l, r = -r;
        }
        deg[u] -= l, deg[v] += l;
        res.second += l * w;
        f.addedge(u, v, r - l, w);
    }
    // 加单位边的函数（只求最大流，不求费用的时候用这个加边，跑的比较快）
    void adduedge(int u, int v, T l, T r) {
        deg[u] -= l, deg[v] += l;
        f.adduedge(u, v, r - l);
    }
    // 超级源点 超级汇点 源点 汇点 [选项=1]
    // 选项：
    // 0->最小费用可行流
    // 1->最小费用最大流
    // 2->最小费用最小流
    pair<T, T> run(int ss, int st, int s, int t, int opt = 1) {
        T all = 0;
        for (int i = 1; i < MXN; i++) {
            if (deg[i] > 0)
                f.addedge(ss, i, deg[i], 0), all += deg[i];
            else if (deg[i] < 0)
                f.addedge(i, st, -deg[i], 0);
        }
        f.addedge(t, s, INF, 0);
        pair<T, T> tres = f.run(ss, st);
        if (tres.first != all) return {-1, -1};
        res.second += tres.second;
        res.first += f.g[s].rbegin()->c;
        f.g[s].rbegin()->c = 0;
        f.g[t].rbegin()->c = 0;
        if (opt == 1) {
            tres = f.run(s, t);
            res.first += tres.first, res.second += tres.second;
        } else if (opt == 2) {
            tres = f.run(t, s);
            res.first -= tres.first, res.second += tres.second;
        }
        return res;
    }
};
// }}}

//{{{ Def
#define fi first
#define se second
#define pb push_back

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
const ll INF = 1e9;
const ll P = 1e9 + 7;
//{{{ Func
ll redu(const ll &x) {
    if (x < P) return x;
    if (x < (P << 1)) return x - P;
    return x % P;
}
template <typename T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, T y) {
    x = min(x, y);
}
ll abs(pi x) { return abs(x.fi) + abs(x.se); }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
//}}}
//{{{ Type
const pi go[] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
struct mll {
    ll v;
    explicit mll(ll _v = 0) : v(_v) {}
    explicit operator ll() const { return v; }
    mll operator+(const mll &y) const { return mll(redu(v + y.v)); }
    mll operator-(const mll &y) const { return mll(redu(P + v - y.v)); }
    mll operator*(const mll &y) const { return mll(redu(v * y.v)); }
    mll operator/(const mll &y) const { return mll(redu(v * (ll)qpow(y, P - 2))); }
    mll &operator=(const mll &y) { return v = y.v, *this; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = redu(v * y.v), *this; }
    mll &operator/=(const mll &y) { return v = redu(v * (ll)qpow(y, P - 2)), *this; }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
};
mll ltm(const ll &x) { return mll(redu(x % P + P)); }
template <typename T>
struct myvec {
    T *v;
    int sz, dsz;
    myvec() { v = NULL, sz = dsz = 0; }
    ~myvec() { free(v); }
    operator T *() const { return v; }
    T *begin() { return v; }
    T *end() { return v + sz; }
    void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
    void pb(T x) {
        if (sz == dsz) v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
        v[sz++] = x;
    }
    void fill(T x) {
        for (int i = 0; i < sz; i++) v[i] = x;
    }
};
//}}}
const int MXN = 230;
flow<MXN * MXN> f;
int n, m;
bool obs[MXN][MXN];
int id(pi x) { return 2 + x.fi * n + x.se; }
int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m;i++){
        int x, y;
        scanf("%d%d", &x, &y);
        obs[x][y] = 1;
    }
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if((j+i)&1){
				f.adduedge(1, id({i,j}), obs[i][j]?0:1);
				for(int k=0;k<8;k++){
					pi nx=pi{i,j}+go[k];
					if(nx.fi<1 || nx.fi>n)continue;
					if(nx.se<1 || nx.se>n)continue;
					f.adduedge(id({i,j}), id(nx), 1);
				}
			}
			else f.adduedge(id({i,j}), 2, obs[i][j]?0:1);
		}
	printf("%d\n",n*n-f.run(1, 2).fi-m);
    return 0;
}

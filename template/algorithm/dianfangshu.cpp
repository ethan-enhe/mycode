#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN = 3e5 + 5;
ll n, m;
vector<ll> g[MXN], t[MXN];
void ae(vector<ll> *_g, ll u, ll v) {
    _g[u].push_back(v);
    _g[v].push_back(u);
}
ll dfn[MXN], low[MXN], dfnc, sqrc;
stack<ll> stk;
void tj(ll p) {
    dfn[p] = low[p] = ++dfnc;
    stk.push(p);
    for (ll nx : g[p]) {
        if (!dfn[nx]) {
            tj(nx);
            low[p] = min(low[nx], low[p]);
            if (low[nx] == dfn[p]) {
                ll x;
                ++sqrc;
                do {
                    x = stk.top();
                    stk.pop();
                    ae(t, x, sqrc);
                } while (x != nx);
                ae(t, p, sqrc);
            }
        } else
            low[p] = min(low[p], dfn[nx]);
    }
}
int main() {
    scanf("%lld%lld", &n, &m);
    sqrc = n;
    while (m--) {
        ll u, v;
        scanf("%lld%lld", &u, &v);
        ae(g, u, v);
    }
    for (ll i = 1; i <= n; i++)
        if (!dfn[i]) tj(i);

    return 0;
}

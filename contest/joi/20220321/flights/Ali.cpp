#include "Ali.h"

#include <bits/stdc++.h>

#include <bitset>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (63 - __builtin_clzll(x))
#define popc(x) __builtin_popcountll(x)
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}

namespace {
const ll MXN = 5e4;
vec<ll> g[MXN];
ll n, plc[MXN], id[MXN], idc;
} // namespace
void dfs(ll p, ll fa) {
    id[plc[p] = idc++] = p;
    /* cerr<<p<<endl; */
    for (ll nx : g[p])
        if (nx != fa) {
            dfs(nx, p);
            id[idc++] = p;
        }
}
ll dis(ll p, ll fa, ll tg) {
    if (p == tg) return 0;
    for (ll nx : g[p])
        if (nx != fa) {
            ll r = dis(nx, p, tg);
            if (r != -1) return r + 1;
        }
    return -1;
}

void Init(int N, std::vector<int> U, std::vector<int> V) {
    n = N;
    idc = 0;
    for (ll i = 0; i < n; i++) g[i].clear();
    for (ll i = 0; i < U.size(); i++) {
        ll u = U[i], v = V[i];
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, -1);
    for (ll i = 0; i < n; i++) {
        SetID(i, plc[i]);
    }
}

std::string SendA(std::string S) {
    ll res = bitset<20>(S).to_ullong();
    ll x = res >> 6, yl = (res ^ (x << 6)) << 8, yr = yl + 256;
    string ans;
    ll last = dis(id[x], -1, id[yl]);
    ans += bitset<14>(last).to_string();
    for (ll i = yl + 1; i < yr; i++) {
        ll cur = dis(id[x], -1, id[i]);
        ans += (cur > last ? '1' : '0');
        last = cur;
    }
    return ans;
}

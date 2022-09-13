#include <bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pr;
const ll MXN = 1e5;
const ll NR = 1e10;
const ll INF = 1e18;

struct node {
    ll ls, rs;
    pr line;
} t[MXN * 100];
ll rt, nodec;
inline ll f(pr line, ll x) { return line.fi * x + line.se; }
inline ll nnode() { return t[++nodec].line = mp(0, -INF), nodec; }
inline void mod(ll &p, ll l, ll r, pr ml) {
    ll mid = (l + r) >> 1;
    if (!p) p = nnode();
    if (f(ml, mid) > f(t[p].line, mid)) swap(ml, t[p].line);
    if (l == r) return;
    ml.fi < t[p].line.fi ? mod(t[p].ls, l, mid, ml) : mod(t[p].rs, mid + 1, r, ml);
}
inline ll que(ll p, ll l, ll r, ll qx) {
    if (!p || l == r) return f(t[p].line, qx);
    ll mid = (l + r) >> 1;
    return max(f(t[p].line, qx), qx > mid ? que(t[p].rs, mid + 1, r, qx) : que(t[p].ls, l, mid, qx));
}
int main() { return 0; }

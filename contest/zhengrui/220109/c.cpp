
#include <bits/stdc++.h>
using namespace std;
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
const ll INF = 1e18;
const ll P = 1e9 + 7;
const ll MXN = 1e6 + 5;
ll n, m, q, nodec;
ll arr[MXN];
const int NR = 5e6;
struct node {
    ll tag, va, ul, ur, dl, dr;
} t[NR];
void addt(ll &p, ll k) {
    if (!p) p = ++nodec;
    t[p].tag += k;
    t[p].va += k;
}
#define upd(x) addt(t[p].x, t[p].tag);
void pushd(ll p) {
    upd(ul);
    upd(ur);
    upd(dl);
    upd(dr);
    t[p].tag = 0;
}
#define _upd(x) t[p].va = max(t[p].va, t[t[p].x].va)
void pushu(ll p) {
    t[p].va = 0;
    _upd(ul);
    _upd(ur);
    _upd(dl);
    _upd(dr);
}
void mod(ll &p, ll xl, ll xr, ll yl, ll yr, ll qxl, ll qxr, ll qyl, ll qyr, ll k) {
    if (xr < qxl || xl > qxr || yr < qyl || yl > qyr) return;
    if (!p) p = ++nodec;
    if (xl >= qxl && xr <= qxr && yl >= qyl && yr <= qyr) {
        addt(p, k);
        return;
    }
    pushd(p);
    ll xm = (xl + xr) >> 1, ym = (yl + yr) >> 1;
    mod(t[p].ul, xl, xm, yl, ym, qxl, qxr, qyl, qyr, k);
    mod(t[p].ur, xm + 1, xr, yl, ym, qxl, qxr, qyl, qyr, k);
    mod(t[p].dl, xl, xm, ym + 1, yr, qxl, qxr, qyl, qyr, k);
    mod(t[p].dr, xm + 1, xr, ym + 1, yr, qxl, qxr, qyl, qyr, k);
    pushu(p);
}
ll que(ll &p, ll xl, ll xr, ll yl, ll yr, ll qxl, ll qxr, ll qyl, ll qyr) {
    if (xr < qxl || xl > qxr || yr < qyl || yl > qyr) return 0;
    if (!p) return 0;
    if (xl >= qxl && xr <= qxr && yl >= qyl && yr <= qyr) return t[p].va;

    pushd(p);
    ll xm = (xl + xr) >> 1, ym = (yl + yr) >> 1;
    return max({que(t[p].ul, xl, xm, yl, ym, qxl, qxr, qyl, qyr), que(t[p].ur, xm + 1, xr, yl, ym, qxl, qxr, qyl, qyr),
                que(t[p].dl, xl, xm, ym + 1, yr, qxl, qxr, qyl, qyr),
                que(t[p].dr, xm + 1, xr, ym + 1, yr, qxl, qxr, qyl, qyr)});
}

ll rt;
int main(int argc, char *argv[]) {
    scanf("%lld%lld%lld", &n, &m, &q);
    for (int i = 1; i <= m; i++) {
        ll a, b, c, d, e;
        scanf("%lld%lld%lld%lld%lld", &a, &b, &c, &d, &e);
        mod(rt, 1, n, 1, n, a, c, b, d, e);
    }
    for (int i = 1; i <= q; i++) {
        ll a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        printf("%lld\n", que(rt, 1, n, 1, n, a, c, b, d));
    }
    return 0;
}

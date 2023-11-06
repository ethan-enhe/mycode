#include <bits/stdc++.h>

#include <algorithm>
#include <vector>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (63 - __builtin_clzll(x))
#define popc(x) __builtin_popcountll(x)
#define all(x) (x) + 1, (x) + 1 + n
#define unq(x) (x).erase(unique(all(x)), (x).end())

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ Func
template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &y) {
    return is >> y.fi >> y.se;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &y) {
    return os << '(' << y.fi << ',' << y.se << ')';
}
template <typename T>
void umx(T &x, const T &y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, const T &y) {
    x = min(x, y);
}
template <typename T = int>
T nxt() {
    T x;
    cin >> x;
    return x;
}
//}}}
const char nl = '\n';
const ll MXN = 1e6 + 5;
const ll INF = 1e18;
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

struct p {
    pi a, b;
} arr[MXN];
ll n;
pi suf[MXN];
ll px[MXN], py[MXN];
void upd(pi &x, pi y) {
    umx(x.fi, y.fi);
    umx(x.se, y.se);
}
bool cmp(const p &x, const p &y) { return x.a < y.a; }

/* #define ls ((p) << 1) */
/* #define rs ((p) << 1 | 1) */
/* struct node { */
/*     // same x,same y */
/*     ll mn[2], mx[2], t[2], mnans; */
/* } t[MXN * 4]; */
/* void pull(ll p) { */
/*     for (int i = 0; i < 2; i++) { */
/*         t[p].mx[i] = max(t[ls].mx[i], t[rs].mx[i]); */
/*         t[p].mn[i] = min(t[ls].mn[i], t[rs].mn[i]); */
/*         /1* t[p].mxs[i] = max(t[ls].mxs[i], t[rs].mxs[i]); *1/ */
/*     } */
/*     t[p].mnans = min(t[ls].mnans, t[rs].mnans); */
/* } */
/* void apply(ll p, ll d, ll i) { */
/*     t[p].t[i] += d; */
/*     t[p].mx[i] += d; */
/*     t[p].mn[i] += d; */
/*     /1* t[p].mxs[i] += d; *1/ */
/*     t[p].mnans += d; */
/* } */
/* void push(ll p) { */
/*     for (int i = 0; i < 2; i++) */
/*         if (t[p].t[i]) { */
/*             apply(ls, t[p].t[i], i); */
/*             apply(rs, t[p].t[i], i); */
/*             t[p].t[i] = 0; */
/*         } */
/* } */
/* void mdf(ll p, ll l, ll r, ll ql, ll qr, ll qv, ll qi) { */
/*     if (ql > qr || qr < l || r < ql || t[p].mn[qi] >= qv) return; */
/*     if (ql <= l && r <= qr && t[p].mn[qi] == t[p].mx[qi]) { */
/*         apply(p, qv - t[p].mx[qi], qi); */
/*         return; */
/*     } */
/*     push(p); */
/*     ll mid = (l + r) >> 1; */
/*     mdf(ls, l, mid, ql, qr, qv, qi); */
/*     mdf(rs, mid + 1, r, ql, qr, qv, qi); */
/*     pull(p); */
/* } */
/* void bld(ll p, ll l, ll r) { */
/*     for (int i = 0; i < 2; i++) t[p].t[i] = 0; */
/*     if (l == r) { */
/*         for (int i = 0; i < 2; i++) { */
/*             t[p].mn[i] = t[p].mx[i] = 0; */
/*             t[p].mnans = py[l]; */
/*             /1* t[p].mxs[i] = py[l]; *1/ */
/*         } */
/*         return; */
/*     } */
/*     ll mid = (l + r) >> 1; */
/*     bld(ls, l, mid); */
/*     bld(rs, mid + 1, r); */
/*     pull(p); */
/* } */
/* ll que(ll p, ll l, ll r, ll ql, ll qr) { */
/*     if (ql > qr || qr < l || r < ql) return INF; */
/*     if (ql <= l && r <= qr) return t[p].mnans; */
/*     push(p); */
/*     ll mid = (l + r) >> 1; */
/*     return min(que(ls, l, mid, ql, qr), que(rs, mid + 1, r, ql, qr)); */
/* } */
/* void prt(ll p, ll l, ll r) { */
/*     if (l == r) { */
/*         cerr << l << "(" << py[l] << "):" << nl; */
/*         for (int i = 0; i < 2; i++) { */
/*             cerr << t[p].mx[i] << " "; */
/*         } */
/*         cerr << t[p].mnans << nl; */
/*         return; */
/*     } */
/*     push(p); */
/*     ll mid = (l + r) >> 1; */
/*     prt(ls, l, mid); */
/*     prt(rs, mid + 1, r); */
/* } */

/* void solve() { */
/*     cin >> n; */
/*     for (int i = 1; i <= n; i++) { */
/*         cin >> arr[i].a >> arr[i].b; */
/*         px[i] = arr[i].a.fi; */
/*         py[i] = arr[i].a.se; */
/*     } */
/*     sort(all(px)), sort(all(py)); */
/*     mnans = INF; */
/*     for (int i = 1; i <= n; i++) { */
/*         arr[i].a.fi = lower_bound(all(px), arr[i].a.fi) - px; */
/*         arr[i].a.se = lower_bound(all(py), arr[i].a.se) - py; */
/*         /1* cout << arr[i].a << " " << arr[i].b << endl; *1/ */
/*         umn(mnans, arr[i].b.fi + arr[i].b.se); */
/*     } */
/*     sort(arr + 1, arr + 1 + n, cmp); */
/*     suf[n + 1] = {0, 0}; */
/*     for (ll i = n; i; i--) { */
/*         suf[i] = suf[i + 1]; */
/*         upd(suf[i], arr[i].b); */
/*     } */
/*     bld(1, 1, n); */
/*     /1* prt(1, 1, n); *1/ */
/*     /1* mdf(1, 1, n, 2, 3, 1, 0); *1/ */
/*     /1* prt(1, 1, n); *1/ */
/*     /1* mdf(1, 1, n, 2, 3, 1, 0); *1/ */
/*     /1* mdf(1, 1, n, 1,2, 1, 0); *1/ */
/*     /1* cout<<que(1,1,n,2,3); *1/ */
/*     ll mny = INF, mxy = -INF, ans = INF; */
/*     for (int i = 1; i <= n; i++) { */
/*         umx(mxy, arr[i].a.se); */
/*         umn(mny, arr[i].a.se); */
/*         mdf(1, 1, n, 1, arr[i].a.se - 1, arr[i].b.fi, 0); */
/*         mdf(1, 1, n, 1, arr[i].a.se - 1, arr[i].b.se, 1); */
/*         ans = min(ans, px[arr[i].a.fi] + que(1, 1, n, 1, n)); */
/*         cout << ans << " " << arr[i].a << " " << arr[i].b << nl; */
/*         prt(1, 1, n); */
/*     } */
/*     cout << ans << nl; */
/*     //注意！！不能全空！！ */
/* } */
void solve() {
    bool f = 1;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].a >> arr[i].b;
        if (arr[i].a.fi || arr[i].a.se) f = 0;
        px[i] = arr[i].a.fi;
        py[i] = arr[i].a.se;
    }
    if (!f) {
        sort(all(px)), sort(all(py));
        for (int i = 1; i <= n; i++) {
            arr[i].a.fi = lower_bound(all(px), arr[i].a.fi) - px;
            arr[i].a.se = lower_bound(all(py), arr[i].a.se) - py;
            /* cout << arr[i].a << " " << arr[i].b << endl; */
        }
        sort(arr + 1, arr + 1 + n, cmp);
        suf[n + 1] = {0, 0};
        for (ll i = n; i; i--) {
            suf[i] = suf[i + 1];
            upd(suf[i], arr[i].b);
        }
        ll ans = INF;
        for (ll i = 1; i <= n; i++) {
            ll cnt = 0, pmn = INF;
            pi pmx = {0, 0};
            for (ll j = 1; j <= n; j++) {
                if (arr[j].a.se <= i) {
                    ++cnt;
                    umn(pmn, arr[j].b.fi + arr[j].b.se);
                } else
                    upd(pmx, arr[j].b);
                if (cnt) {
                    if (cnt != n) {
                        pi tmp = {0, 0};
                        upd(tmp, pmx);
                        upd(tmp, suf[j + 1]);
                        ans = min(ans, py[i] + px[arr[j].a.fi] + tmp.fi + tmp.se);
                    } else
                        ans = min(ans, py[i] + px[arr[j].a.fi] + pmn);
                }
            }
        }
        cout << ans << nl;
    } else {
        ll ans = INF;
        for (ll i = 1; i <= n; i++) umn(ans, arr[i].b.fi + arr[i].b.se);
        cout << ans << nl;
    }
    //注意！！不能全空！！
}
int main() {
    freopen("tinyds.in", "r", stdin);
    freopen("tinyds.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}

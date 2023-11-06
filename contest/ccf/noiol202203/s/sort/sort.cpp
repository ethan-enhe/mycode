#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXM = 6, MXN = 4e5 + 100, INF = 1e18;

ll ZERO, NR;
namespace cdq {
ll ans[MXN];
struct que {
    bool tp;
    ll i, a, b, c;
} arr[MXN];
inline bool cmpa(que x, que y) { return x.a == y.a ? x.tp > y.tp : x.a < y.a; }
inline bool cmpb(que x, que y) { return x.b == y.b ? x.tp > y.tp : x.b < y.b; }

ll d[MXN];
inline void mod(ll x, ll y) {
    x += ZERO;
    for (; x < NR; x += x & (-x)) d[x] += y;
}
inline ll sum(ll x) {
    ll r = 0;
    x += ZERO;
    for (; x; x ^= x & (-x)) r += d[x];
    return r;
}

inline void cdq(ll l, ll r) {
    if (l == r) return;
    ll mid = (l + r) >> 1, ind = l;
    cdq(l, mid), cdq(mid + 1, r);
    for (ll i = mid + 1; i <= r; i++)
        if (!arr[i].tp) {
            while (ind <= mid && arr[ind].b <= arr[i].b) {
                if (arr[ind].tp) mod(arr[ind].c, 1);
                ++ind;
                /* cout << "!!!" */
                /*      << "mod" */
                /*      << " " << arr[ind].c << endl; */
            }
            ans[arr[i].i] += sum(arr[i].c);
            /* cerr << "que" */
            /*      << " " << arr[i].c << " " << sum(arr[i].c) << arr[i].i << endl; */
        }
    while (--ind >= l)
        if (arr[ind].tp) mod(arr[ind].c, -1);
    inplace_merge(arr + l, arr + mid + 1, arr + r + 1, cmpb);
}
ll ind, qid;
void clr() { ind = qid = 0; }
ll add(ll x, ll y, ll z, bool tp) {
    /* cerr << x << " " << y << " " << z << " " << tp << endl; */
    if (tp == 0) ans[++qid] = 0;
    arr[++ind] = {tp, qid, x, y, z};
    return qid;
}
void run() {
    sort(arr + 1, arr + 1 + ind, cmpa);
    cdq(1, ind);
}
} // namespace cdq
ll m, n, ans;
ll arr[MXM][MXN];
void solve(ll line) {
    cdq::clr();
    for (ll i = 1; i <= n; i++) {
        ll qi[] = {0, 0, 0, 0, 0, 0}, ai[] = {0, 0, 0, 0, 0, 0}, ind = 0;
        for (ll j = 1; j <= m; j++)
            if (j != line) {
                ++ind;
                qi[ind] = arr[line][i] - arr[j][i] - (j < line);
                ai[ind] = arr[j][i] - arr[line][i];
            }
        cdq::add(ai[1], ai[2], ai[3], 1);
        cdq::add(qi[1], qi[2], qi[3], 0);
        if (qi[1] >= ai[1] && qi[2] >= ai[2] && qi[3] >= ai[3]) --cdq::ans[i];
    }
    cdq::run();
    for (ll i = 1; i <= n; i++) ans += cdq::ans[i] * 2 * arr[line][i];
}
void gmx() {
    for (ll i = 1; i <= m; i++) solve(i);
    for (ll i = 1; i <= n; i++) {
        ll mx = -INF;
        for (ll j = 1; j <= m; j++) mx = max(mx, arr[j][i]);
        ans += mx * 2;
    }
    /* cout << ans; */
}
int main() {
    /* freopen("sort.in", "r", stdin); */
    /* freopen("sort.out", "w", stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n;
    for (ll i = 1; i <= m; i++)
        for (ll j = 1; j <= n; j++) {
            cin >> arr[i][j];
            ZERO = max(ZERO, arr[i][j]);
        }
    ZERO += 10;
    NR = ZERO * 2;

    gmx();
    ll fans = ans;
    ans = 0;
    for (ll i = 1; i <= m; i++)
        for (ll j = 1; j <= n; j++) arr[i][j] = -arr[i][j];
    gmx();
    cout << fans - ans;

    return 0;
}


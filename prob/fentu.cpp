// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
#define NDEBUG
#endif
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = int;
//}}}
const ll P = 1e9 + 7;
const char nl = '\n';
const ll ZERO = 1e5 + 5;
const ll MXN = 2 * ZERO;

ll n, m;
ll arr[MXN];
struct node {
    ll settag;
    ll xortag;
} t[(MXN << 2) + 100];
void addt(ll p, ll s, ll x) {
    if (s != -1) t[p].settag = s, t[p].xortag = 0;
    t[p].xortag ^= x;
}
#define ls p << 1
#define rs p << 1 | 1
void push(ll p) {
    addt(ls, t[p].settag, t[p].xortag);
    addt(rs, t[p].settag, t[p].xortag);
    t[p].settag = -1;
    t[p].xortag = 0;
}
void build(ll p, ll l, ll r) {
    if (l == r) {
        return;
    }
    t[p].settag = -1;
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
}
void mdf(ll p, ll l, ll r, ll ml, ll mr, ll s, ll x) {
    if (l > mr || r < ml) return;
    if (ml <= l && r <= mr) {
        addt(p, s, x);
        return;
    }
    push(p);
    ll mid = (l + r) >> 1;
    mdf(ls, l, mid, ml, mr, s, x);
    mdf(rs, mid + 1, r, ml, mr, s, x);
}
ll qry(ll p, ll l, ll r, ll qi) {
    if (l == r) return t[p].settag ^ t[p].xortag;
    push(p);
    ll mid = (l + r) >> 1;
    return qi <= mid ? qry(ls, l, mid, qi) : qry(rs, mid + 1, r, qi);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    build(1, -ZERO, ZERO);
    // mdf(1, -ZERO, ZERO, -1, 1, 1, 0);
    // mdf(1, -ZERO, ZERO, -1, 1, -1, 1);
    // cout << qry(1, -ZERO, ZERO, 1);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) cin >> arr[i];
    for (ll i = 1; i <= m; i++) {
        char op;
        ll x;
        cin >> op >> x;
        if (op == '>') {
            if (x >= 0) {
                mdf(1, -ZERO, ZERO, x + 1, ZERO, 1, 0);
                mdf(1, -ZERO, ZERO, -ZERO, -x - 1, 0, 0);
            } else {
                x = -x;
                mdf(1, -ZERO, ZERO, x, ZERO, 1, 0);
                mdf(1, -ZERO, ZERO, -ZERO, -x, 0, 0);
                mdf(1, -ZERO, ZERO, -x + 1, x - 1, -1, 1);
            }
        } else {
            if (x <= 0) {
                mdf(1, -ZERO, ZERO, -ZERO, x - 1, 1, 0);
                mdf(1, -ZERO, ZERO, -x + 1, ZERO, 0, 0);
            } else {
                x = -x;
                mdf(1, -ZERO, ZERO, -ZERO, x, 1, 0);
                mdf(1, -ZERO, ZERO, -x, ZERO, 0, 0);
                mdf(1, -ZERO, ZERO, x + 1, -x - 1, -1, 1);
            }
        }
        // for (int i = -5; i <= 5; i++) cout << qry(1, -ZERO, ZERO, i);
        // cout << endl;
    }
    for (ll i = 1; i <= n; i++) {
        ll res = qry(1, -ZERO, ZERO, arr[i]);
        if (res) arr[i] = -arr[i];
        cout << arr[i] << " ";
    }
    return 0;
}

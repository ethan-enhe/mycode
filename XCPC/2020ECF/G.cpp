#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
const char nl = '\n';
const ll MXN = 5e5 + 5;

int n, m;
struct mat {
    ll v[3][3];
    mat() {}
    mat(bool f) {
        memset(v, 0, sizeof(v));
        if (f) v[0][0] = v[1][1] = v[2][2] = 1;
    }
    mat operator*(const mat &b) const {
        mat res;
        res.v[0][0] = 1;
        res.v[1][0] = v[1][0] + v[1][2] * b.v[2][0] + v[1][1] * b.v[1][0];
        res.v[1][1] = v[1][1] * b.v[1][1] + v[1][2] * b.v[2][1];
        res.v[1][2] = v[1][1] * b.v[1][2] + v[1][2] * b.v[2][2];
        res.v[2][0] = v[2][0] + v[2][1] * b.v[1][0] + v[2][2] * b.v[2][0];
        res.v[2][1] = v[2][1] * b.v[1][1] + v[2][2] * b.v[2][1];
        res.v[2][2] = v[2][1] * b.v[1][2] + v[2][2] * b.v[2][2];
        return res;
    }
    void prt() {
        for (int i = 0; i < 3; i++, cerr << endl)
            for (int j = 0; j < 3; j++) cerr << v[i][j] << ",";
        cerr << endl;
    }
    bool notunit() {
        return v[1][1] != 1 || v[2][2] != 1 || v[0][1] != 0 || v[0][2] != 0 || v[1][0] != 0 || v[1][2] != 0 ||
               v[2][0] != 0 || v[2][1] != 0;
    }
} flip, addhist;
struct vec {
    ll v[3];

    vec operator+(const vec &b) const {
        vec res;
        res.v[0] = v[0] + b.v[0];
        res.v[1] = v[1] + b.v[1];
        res.v[2] = v[2] + b.v[2];
        return res;
    }
    vec operator*(const mat &b) const {
        vec res;
        res.v[0] = v[0] * b.v[0][0] + v[1] * b.v[1][0] + v[2] * b.v[2][0];
        res.v[1] = v[1] * b.v[1][1] + v[2] * b.v[2][1];
        res.v[2] = v[1] * b.v[1][2] + v[2] * b.v[2][2];
        return res;
    }
};

#define ls (p << 1)
#define rs (p << 1 | 1)

struct node {
    vec val;
    mat tag;
} t[MXN << 2];

void pull(ll p) { t[p].val = t[ls].val + t[rs].val; }
void addt(ll p, mat &k) {
    t[p].val = t[p].val * k;
    t[p].tag = t[p].tag * k;
}
void push(ll p) {
    if (t[p].tag.notunit()) {
        addt(ls, t[p].tag);
        addt(rs, t[p].tag);
        t[p].tag = mat(1);
    }
}
void build(ll p = 1, ll l = 1, ll r = n) {
    t[p].tag = mat(1);
    if (l == r) {
        t[p].val.v[2] = 1;
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pull(p);
}
void mod(ll ml, ll mr, ll p = 1, ll l = 1, ll r = n) {
    if (ml <= l && r <= mr) {
        addt(p, flip);
        return;
    }
    if (l > mr || r < ml) return;
    ll mid = (l + r) >> 1;
    push(p);
    mod(ml, mr, ls, l, mid);
    mod(ml, mr, rs, mid + 1, r);
    pull(p);
}
ll sum(ll ml, ll mr, ll p = 1, ll l = 1, ll r = n) {
    if (ml <= l && r <= mr) {
        return t[p].val.v[0];
    }
    if (l > mr || r < ml) return 0;
    ll mid = (l + r) >> 1;
    push(p);
    return sum(ml, mr, ls, l, mid) + sum(ml, mr, rs, mid + 1, r);
}

map<ll, ll> last;
ll arr[MXN], ans[MXN];
vector<pi> q[MXN];
int main() {
    // freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    addhist.v[0][0] = addhist.v[1][1] = addhist.v[2][2] = addhist.v[1][0] = 1;
    flip.v[0][0] = flip.v[1][2] = flip.v[2][1] = 1;
    cin >> n;
    build();
    for (ll i = 1; i <= n; i++) cin >> arr[i];
    cin >> m;
    for (ll i = 1; i <= m; i++) {
        ll l, r;
        cin >> l >> r;
        q[r].push_back({l, i});
    }
    for (ll i = 1; i <= n; i++) {
        ll la = last[arr[i]];
        last[arr[i]] = i;
        mod(la + 1, i);
        addt(1, addhist);
        for (auto &j : q[i]) {
            ans[j.se] = sum(j.fi, i);
        }
    }
    for (ll i = 1; i <= m; i++) cout << ans[i] << endl;

    return 0;
}

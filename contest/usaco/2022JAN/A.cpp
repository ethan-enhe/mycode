#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
constexpr ll INF = 2e9;
constexpr ll MXN = 1e6 + 5;
ll n, m;
// cnt 表示符合条件的个数
priority_queue<pi> q;
ll arr[MXN], cnt[MXN];
void upd(ll x) {
    if (x == 0 || x == n + 1) return;
    if (++cnt[x] == 2) {
        /* cerr << "in" << x << endl; */
        q.push({-arr[x], -x});
    }
}
struct seg {
    struct node {
        pi mn;
        ll tag;
    } t[MXN];
#define ls p << 1
#define rs p << 1 | 1
    bool type;
    seg(bool _type) : type(_type) {}
    void addt(ll p, ll k) { t[p].mn.first += k, t[p].tag += k; }
    void pushd(ll p) {
        addt(ls, t[p].tag);
        addt(rs, t[p].tag);
        t[p].tag = 0;
    }
    void pushu(ll p) { t[p].mn = min(t[ls].mn, t[rs].mn); }
    void build(ll p, ll l, ll r, ll *arr) {
        if (l == r) {
            t[p].mn.second = l;
            if (arr) t[p].mn.first = arr[l];
            return;
        }
        ll mid = (l + r) >> 1;
        build(ls, l, mid, arr);
        build(rs, mid + 1, r, arr);
        pushu(p);
    }
    void mod(ll p, ll l, ll r, ll ml, ll mr, ll mv) {
        if (ml > r || mr < l) return;
        if (ml <= l && r <= mr && (type || t[p].mn.first + mv > 0)) {
            addt(p, mv);
            return;
        }
        if (l == r) {
            t[p].mn.first = INF;
            upd(l);
            return;
        }
        ll mid = (l + r) >> 1;
        pushd(p);
        mod(ls, l, mid, ml, mr, mv);
        mod(rs, mid + 1, r, ml, mr, mv);
        pushu(p);
    }
    pi first_lower(ll p, ll l, ll r, ll qv) {
        if (l == r) return t[p].mn;
        ll mid = (l + r) >> 1;
        /* cerr<<l<<" "<<mid<<" "<<r<<" "<<t[ls].mn.first<<" "<<t[rs].mn.first<<endl; */
        pushd(p);
        if (t[ls].mn.first <= qv) return first_lower(ls, l, mid, qv);
        return first_lower(rs, mid + 1, r, qv);
    }
    pi que(ll p, ll l, ll r, ll ql, ll qr) {
        if (ql > r || qr < l) return {INF, INF};
        if (ql <= l && r <= qr) return t[p].mn;
        ll mid = (l + r) >> 1;
        pushd(p);
        return min(que(ls, l, mid, ql, qr), que(rs, mid + 1, r, ql, qr));
    }
} a_mn(0), mx_a(0), mnp(1), mxp(1);
#define seg_op(func, args...) func(1, 0, n + 1, args)

bool in_mn_stack[MXN], in_mx_stack[MXN];
ll init_a_mn[MXN], init_mx_a[MXN];
void init() {
    ll mx = -2 * INF, mn = 2 * INF;
    in_mn_stack[0] = in_mn_stack[n + 1] = in_mx_stack[0] = in_mx_stack[n + 1] = 1;
    mnp.seg_op(build, NULL);
    mxp.seg_op(build, NULL);
    for (ll i = 0; i <= n + 1; i++) {
        if (i == n + 1) mx = INF, mn = -INF;
        /* if(i==3)cerr<<mn<<endl; */
        if (!i) arr[i] = INF;
        if (arr[i] < mn) mn = arr[i], in_mn_stack[i] = 1;
        mnp.seg_op(mod, i, i, arr[i]);

        if (!i) arr[i] = -INF;
        if (arr[i] > mx) mx = arr[i], in_mx_stack[i] = 1;
        mxp.seg_op(mod, i, i, -arr[i]);
        init_a_mn[i] = arr[i] - mn - m;
        init_mx_a[i] = mx - arr[i] - m;
        if (init_a_mn[i] <= 0) init_a_mn[i] = INF, upd(i);
        if (init_mx_a[i] <= 0) init_mx_a[i] = INF, upd(i);
    }
    a_mn.seg_op(build, init_a_mn);
    mx_a.seg_op(build, init_mx_a);
}
void prt() {
    cerr << "---\n";
    cerr << "mn stk: ";
    for (int i = 0; i <= n + 1; i++)
        if (in_mn_stack[i]) cerr << i << " ";
    cerr << endl;
    cerr << "mx stk: ";
    for (int i = 0; i <= n + 1; i++)
        if (in_mx_stack[i]) cerr << i << " ";
    cerr << endl;
    cerr << "mnp: ";
    for (int i = 0; i <= n + 1; i++) cerr << mnp.seg_op(que, i, i).first << " ";
    cerr << endl;
    cerr << "mxp: ";
    for (int i = 0; i <= n + 1; i++) cerr << mxp.seg_op(que, i, i).first << " ";
    cerr << endl;
}
void del(ll x) {
    /* prt(); */
    mnp.seg_op(mod, x, x, INF);
    mxp.seg_op(mod, x, x, INF);
    if (in_mn_stack[x]) {
        in_mn_stack[x] = 0;

        auto cur_ele = mnp.seg_op(que, 0, x);
        /* if (x == 3) cerr << "pre " << x << "=(" << cur_ele.first << "," << cur_ele.second << ")  (va,id)" << endl; */
        while (1) {
            auto nx_ele = mnp.seg_op(first_lower, cur_ele.first - 1);
            bool f = in_mn_stack[nx_ele.second];
            //!!!
            /* if (x == 3) cerr << "new ele (" << nx_ele.first << "," << nx_ele.second << ")\n"; */
            a_mn.seg_op(mod, max(x, cur_ele.second), nx_ele.second - 1, -cur_ele.first + arr[x]);
            if (f) break;
            in_mn_stack[nx_ele.second] = 1;
            cur_ele = nx_ele;
        }
    }
    if (in_mx_stack[x]) {
        in_mx_stack[x] = 0;

        auto cur_ele = mxp.seg_op(que, 0, x);
        while (1) {
            auto nx_ele = mxp.seg_op(first_lower, cur_ele.first - 1);
            bool f = in_mx_stack[nx_ele.second];
            //!!!
            mx_a.seg_op(mod, max(x, cur_ele.second), nx_ele.second - 1, -cur_ele.first - arr[x]);
            if (f) break;
            in_mx_stack[nx_ele.second] = 1;
            cur_ele = nx_ele;
        }
    }
}

int main(int argc, char *argv[]) {
    // code
    /* freopen("A.in", "r", stdin); */
    /* freopen("A.out", "w", stdout); */
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++) scanf("%lld", arr + i);
    init();
    for (int i = 1; i <= n; i++) {
        auto best = q.top();
        q.pop();
        printf("%lld\n", -best.first);
        del(-best.second);
        /* cerr<<"del"<<best.second<<endl; */
        /* prt(); */
    }
    /* arr[n + 1] = INF; */
    /* for (ll i = 1; i <= n; i++) { */
    /*     cal(i); */
    /* } */
    /* for (ll i = 1; i <= n; i++) { */
    /*     printf("%lld\n", arr[i]); */
    /* } */
    return 0;
}

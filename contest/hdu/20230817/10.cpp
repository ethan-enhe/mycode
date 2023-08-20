#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define ll long long
const ll N = 2e6 + 10, Q = 1e6 + 10;
string u, v;
char uu[N];
ll nxt[N];
char s[N];
ll sa[N], rk[N], tp[N], c[N], h[N], n, m, q, nn;
bool cmp(ll x, ll y, ll t) { return tp[x] == tp[y] && tp[x + t] == tp[y + t]; }
void tros(ll n, ll m) {
    for (ll i = 1; i <= m; i++) c[i] = 0;
    for (ll i = 1; i <= n; i++) c[rk[tp[i]]]++;
    for (ll i = 1; i <= m; i++) c[i] += c[i - 1];
    for (ll i = n; i >= 1; i--) sa[c[rk[tp[i]]]--] = tp[i];
}
void get_sa() {
    nn = strlen(s + 1);
    ll m = 128;
    for (ll i = 1; i <= nn; i++) tp[i] = i, rk[i] = s[i];
    tros(nn, m);
    for (ll l = 1, p = 0; p < nn; m = p, l <<= 1) {
        p = 0;
        for (ll i = nn - l + 1; i <= nn; i++) tp[++p] = i;
        for (ll i = 1; i <= nn; i++)
            if (sa[i] > l) tp[++p] = sa[i] - l;
        tros(nn, m);
        memcpy(tp, rk, sizeof(ll) * (nn + 2));
        rk[sa[1]] = p = 1;
        for (ll i = 2; i <= nn; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], l) ? p : ++p;
    }
    for (ll i = 1, j = 0; i <= nn; i++) {
        if (j) j--;
        while (s[i + j] == s[sa[rk[i] - 1] + j]) j++;
        h[rk[i]] = j;
    }
}

vector<ll> period;
ll period_cnt[N];

ll pre_u[N], pre_mn_h[N], nxt_u[N], nxt_mn_h[N];

ll mx_lcp[N], mx_r[N];

ll w[N], sw[N], pw[N];

struct query {
    ll l, r, id;
};
query que[Q];

struct BIT {
    ll c[N];
    void mdf(ll p, ll v) {
        for (; p <= m; p += p & -p) c[p] += v;
    }
    ll qry(ll p) {
        ll r = 0;
        for (; p; p -= p & -p) r += c[p];
        return r;
    }
    void clr() { memset(c, 0, sizeof(ll) * (m + 2)); }
};
// BIT small_cnt,small_sum;

ll ans[Q];

// ll qry(ll r,ll lim){
//     return (m-small_cnt.qry(r))*1ll*lim+small_sum.qry(r);
// }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> q;
        cin >> u >> v;
        for (ll i = 0; i < n; i++) uu[i + 1] = u[i];
        uu[n + 1] = '\0';

        nxt[1] = 0;
        for (ll i = 2; i <= n; i++) {
            ll j = nxt[i - 1];
            while (j && uu[j + 1] != uu[i]) j = nxt[j];
            if (uu[j + 1] == uu[i]) j++;
            nxt[i] = j;
        }

        period.clear();
        for (ll i = nxt[n]; i; i = nxt[i]) period.push_back(n - i);
        for (ll i = 0; i <= n; i++) period_cnt[i] = 0;
        for (ll i : period) period_cnt[i]++;
        for (ll i = 1; i <= n; i++) period_cnt[i] += period_cnt[i - 1];

        for (ll i = 1; i < n - 1; i++) s[++nn] = u[i];
        s[++nn] = '#';
        for (char c : v) s[++nn] = c;
        s[++nn] = '\0';

        get_sa();

        pre_u[0] = 0;
        pre_mn_h[0] = 0;
        for (ll i = 1; i <= nn; i++) {
            if (sa[i] <= n - 2) {
                pre_u[i] = i;
                pre_mn_h[i] = 1e9;
            } else {
                pre_u[i] = pre_u[i - 1];
                pre_mn_h[i] = min(pre_mn_h[i - 1], h[i]);
            }
        }

        nxt_u[nn + 1] = nn + 1;
        nxt_mn_h[nn + 1] = 0;
        for (ll i = nn; i >= 1; i--) {
            if (sa[i] <= n - 2) {
                nxt_u[i] = i;
                nxt_mn_h[i] = 1e9;
            } else {
                nxt_u[i] = nxt_u[i + 1];
                nxt_mn_h[i] = min(nxt_mn_h[i + 1], h[i + 1]);
            }
        }

        // cerr<<"n = "<<n<<endl;

        for (ll i = 1; i <= m; i++) {
            ll idx = n - 2 + 1 + i;
            ll rk = ::rk[idx];
            mx_lcp[i] = max(pre_mn_h[rk], nxt_mn_h[rk]);
            mx_r[i] = mx_lcp[i] + i - 1;
            // cerr<<"> "<<(s+sa[rk])<<"  "<<pre_u[rk]<<" "<<(s+sa[pre_u[rk]])<<"  "<<nxt_u[rk]<<"
            // "<<(s+sa[nxt_u[rk]])<<"  "<<mx_lcp[i]<<endl;
            w[i] = period_cnt[mx_lcp[i]];
        }
        // for(ll i=1;i<=m;i++)cerr<<w[i]<<" ";cerr<<endl;
        for (ll i = 1; i <= m; i++) pw[i] = i;
        for (ll i = 1; i <= m; i++) sw[i] = sw[i - 1] + w[i];
        sort(pw + 1, pw + 1 + m, [](ll a, ll b) { return w[a] < w[b]; });

        for (ll i = 1; i <= q; i++) {
            cin >> que[i].l >> que[i].r;
            que[i].id = i;
            ans[i] = 0;
        }
        sort(que + 1, que + 1 + q, [](query a, query b) { return a.r - a.l < b.r - b.l; });

        // ll p=1;
        // for(ll i=1;i<=q;i++){
        //     ll id=que[i].id;
        //     ll l=que[i].l,r=que[i].r;
        //     for(ll j=que[i].l;j<=que[i].r;j++){
        //         ans[id]+=period_cnt[min(que[i].r-j+1,mx_lcp[j])];
        //     }
        // }
        sort(period.begin(), period.end());
        vector<ll> sum(period);
        for (ll i = 1; i < sum.size(); i++) sum[i] += sum[i - 1];
        auto gets = [&](ll i) {
            if (i == -1) return 0ll;
            return sum[i];
        };
        for (ll i = 1; i <= q; i++) {
            ll id = que[i].id;
            ll l = que[i].l, r = que[i].r;
            ll u = lower_bound(mx_r + 1, mx_r + 1 + m, r) - mx_r;
            ans[id] += sw[u - 1] - sw[l - 1];
            if (u <= m) {
                auto up = upper_bound(period.begin(), period.end(), r - u + 1);
                auto up2 = upper_bound(period.begin(), period.end(), r - m + 1);
                ans[id] += (-u + 1) * (up - period.begin());
                ans[id] += (m) * (up2 - period.begin());
                ans[id] += gets(up - period.begin() - 1) - gets(up2 - period.begin() - 1);
            }
            // for (ll j : period) {
            //     // Need to be optimized
            //     ll le = u, ri = min(r - j + 1, m);
            //     if (le <= ri) ans[id] += ri - le + 1;
            // }
        }
        for (ll i = 1; i <= q; i++) cout << ans[i] << "\n";
    }
    return 0;
}

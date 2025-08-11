#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;
const int MXN = 1e6 + 5;
const int SZ = 26;
struct node {
    int minlen, fail, son[SZ];
} t[MXN];
int q[MXN], ql = 1, qr, nodec;
int newnode() {
    ++nodec;
    t[nodec].minlen = INF;
    t[nodec].fail = 0;
    for (int i = 0; i < SZ; i++) t[nodec].son[i] = 0;
    return nodec;
}
inline void ins(const char *tstr, int len) {
    int p = 0;
    for (int i = 0; i < len; i++) {
        if (t[p].son[tstr[i] - 'a'])
            p = t[p].son[tstr[i] - 'a'];
        else
            p = t[p].son[tstr[i] - 'a'] = newnode();
    }
    t[p].minlen = min(t[p].minlen, len);
}
inline void build() {
    for (int i = 0; i < SZ; i++)
        if (t[0].son[i]) q[++qr] = t[0].son[i];
    while (ql <= qr) {
        int p = q[ql++];
        for (int i = 0; i < SZ; i++) {
            int &nx = t[p].son[i], fa = t[p].fail;
            if (nx) {
                t[nx].fail = t[fa].son[i];
                t[nx].minlen = min(t[nx].minlen, t[t[fa].son[i]].minlen);
                q[++qr] = nx;
            } else
                nx = t[fa].son[i];
        }
    }
}
void clear() {
    nodec = -1;
    newnode();
    ql = 1, qr = 0;
};

int n;
vector<string> ls, rs;
char str[MXN];
vector<ll> lend[MXN];

ll sum[MXN];

ll pre(ll x) {
    ll res = 0;
    for (; x; x -= x & -x) res += sum[x];
    return res;
}
void mdf(ll x, ll v) {
    for (; x <= n; x += x & -x) sum[x] += v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll task;
    cin >> task;
    while (task--) {
        ls.clear();
        rs.clear();
        ll l, r;
        cin >> l >> r;
        while (l--) {
            string s;
            cin >> s;
            reverse(s.begin(), s.end());
            ls.push_back(s);
        }
        while (r--) {
            string s;
            cin >> s;
            rs.push_back(s);
        }
        cin >> str;
        n = strlen(str);
        for (ll i = n; i >= 1; i--) {
            str[i] = str[i - 1];
        }
        str[0] = 0;

        for (ll i = 1; i <= n; i++) {
            sum[i] = 0;
            lend[i].clear();
        }
        clear();
        for (const auto &s : ls) ins(s.c_str(), s.size());
        build();
        int p = 0;
        for (int i = n; i; i--) {
            p = t[p].son[str[i] - 'a'];
            if (t[p].minlen < INF) {
                // cout << i << " " <<  << "\n";
                lend[i + t[p].minlen - 1].push_back(i);
            }
        }

        clear();
        for (const auto &s : rs) ins(s.c_str(), s.size());
        build();
        p = 0;
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            for (const auto &j : lend[i]) {
                mdf(j, 1);
            }
            p = t[p].son[str[i] - 'a'];
            if (t[p].minlen < INF) {
                ans += pre(i - t[p].minlen + 1);
            }
        }
        cout << ans << "\n";
    }

    return 0;
}

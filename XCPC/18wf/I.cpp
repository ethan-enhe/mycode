#include <bits/stdc++.h>

#include <cctype>
#define fi first
#define se second
using namespace std;
using pi = pair<int, int>;
using ll = long long;
const ll MXN = 4505;
const ll INF = 1e9;
ll n, m;
bool r[MXN][MXN], d[MXN][MXN], c[MXN][MXN];
int clen[MXN][MXN], ulen[MXN][MXN], rlen[MXN][MXN];
string s;

bool inrng(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }

int sum[MXN];
void mdf(ll x, ll y) {
    for (; x; x -= x & (-x)) sum[x] += y;
}
ll suf(ll x) {
    ll r = 0;
    for (; x <= n; x += x & (-x)) {
        r += sum[x];
    }
    return r;
}

ll ans;
vector<int> del[MXN];
void solve_diag(int x, int y) {
    int _x = x, _y = y;
    while (inrng(_x + 1, _y + 1)) ++_x, ++_y;
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= m; ++i) {
        del[i].clear();
    }

    while (inrng(x, y)) {
        for (auto j : del[y]) {
            mdf(j, -1);
            // cerr << j << "-" << endl;
        }
        // cerr << (x - ulen[x][y] + 1) << "?" << endl;
        ans += suf(x - ulen[x][y] + 1);
        del[y + min(rlen[x][y], clen[x][y])].push_back(x);
        mdf(x, 1);
        // cerr << x << "+" << endl;
        ++x, ++y;
    }
    // cerr << x << " " << y << " " << ans << endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    m=(n+1)/2+(m+1)/2;
    getline(cin, s);

    ll ls = 1;
    for (ll i = 1; i <= n; i++) {
        if (!(i & 1)) ++ls;
        getline(cin, s);

        for (ll j = ls, idx = 0 + (i & 1 ? 0 : 2); idx < s.size(); idx += 4, j++) {
            if (idx + 1 < s.size() && s[idx + 1] != ' ') r[i][j] = 1;
        }
        getline(cin, s);
        if (i < n) {
            for (ll j = 1, idx = 1; idx < s.size(); idx += 2, j++) {
                if (s[idx] != ' ') {
                    ll t = (i & 1) + j;
                    if (t & 1)
                        d[i][ls + (t >> 1)] = 1;
                    else
                        c[i][ls + (t >> 1) - 1] = 1;
                }
            }
        }
    }
    for (int i = n; i; i--)
        for (int j = m; j >= 1; j--) {
            if (c[i][j])
                clen[i][j] = clen[i + 1][j + 1] + 1;
            else
                clen[i][j] = 1;
            if (r[i][j])
                rlen[i][j] = rlen[i][j + 1] + 1;
            else
                rlen[i][j] = 1;
        }
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--) {
            if (d[i - 1][j])
                ulen[i][j] = ulen[i - 1][j] + 1;
            else
                ulen[i][j] = 1;
        }
    for (int i = 1; i <= m; i++) solve_diag(1, i);
    for (int i = 2; i <= n; i++) solve_diag(i, 1);
    swap(n, m);
    for (int i = 0; i < MXN; i++)
        for (int j = i; j < MXN; j++) {
            swap(c[i][j], c[j][i]);
            swap(r[i][j], d[j][i]);
            if (i != j) swap(d[i][j], r[j][i]);
            // clen[i][j]=rlen[i][j]=ulen[i][j]=0;
            // clen[i][j]=rlen[i][j]=ulen[i][j]=0;
        }
    for (int i = n; i; i--)
        for (int j = m; j >= 1; j--) {
            if (c[i][j])
                clen[i][j] = clen[i + 1][j + 1] + 1;
            else
                clen[i][j] = 1;
            if (r[i][j])
                rlen[i][j] = rlen[i][j + 1] + 1;
            else
                rlen[i][j] = 1;
        }
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--) {
            if (d[i - 1][j])
                ulen[i][j] = ulen[i - 1][j] + 1;
            else
                ulen[i][j] = 1;
        }
    for (int i = 1; i <= m; i++) solve_diag(1, i);
    for (int i = 2; i <= n; i++) solve_diag(i, 1);

    cout << ans;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1e5 + 5;
const ll N = 1e5 + 5;
const ll LG = 30;
ll n, m, a[MXN], b[MXN], A[MXN], B[MXN];
ll dp[LG][MXN];
namespace Wallbreaker5th {

int mn[N * LG], ch[N * LG][2], tot = 1;
void insert(int x, int v) {
    int p = 1;
    for (int i = LG - 1; i >= 0; i--) {
        int c = (x >> i) & 1;
        if (!ch[p][c]) {
            ch[p][c] = ++tot;
            mn[tot] = 1e9;
            ch[tot][0] = ch[tot][1] = 0;
        }
        p = ch[p][c];
        mn[p] = min(mn[p], v);
    }
}
int query(int l, int r, int x, int nl, int nr) {
    if (l <= nl && nr <= r) {
        return mn[x];
    }
    int mid = (nl + nr) / 2;
    int res = 1e9;
    if (l <= mid && ch[x][0]) {
        res = min(res, query(l, r, ch[x][0], nl, mid));
    }
    if (r > mid && ch[x][1]) {
        res = min(res, query(l, r, ch[x][1], mid + 1, nr));
    }
    return res;
}
void preprocess() {
    for (int i = 0; i < LG; i++) {
        mn[1] = 1e9;
        tot = 1;
        ch[1][0] = ch[1][1] = 0;

        for (int j = n; j >= 1; j--) {
            int a = (A[j] % (1 << i + 1) + (1 << i + 1)) % (1 << i + 1);
            int b = (B[j] % (1 << i + 1) + (1 << i + 1)) % (1 << i + 1);
            insert(b, j);
            int bl = a - ((1 << i + 1) - 1), br = a - (1 << i);
            if (bl < 0) bl += 1 << i + 1;
            if (br < 0) br += 1 << i + 1;
            dp[i][j] = 1e9;
            if (bl <= br) dp[i][j] = query(bl, br, 1, 0, (1 << LG) - 1);
            if (bl > br) {
                dp[i][j] = min(dp[i][j], (ll)query(0, br, 1, 0, (1 << LG) - 1));
                dp[i][j] = min(dp[i][j], (ll)query(bl, (1 << i + 1) - 1, 1, 0, (1 << LG) - 1));
            }

            // int brute=1e9;
            // for(int k=j;k<=n;k++){
            //     if(((A[j]-B[k])>>i)&1){
            //         brute=k;
            //         break;
            //     }
            // }
            // cerr<<"> "<<i<<" "<<j<<" "<<brute<<" "<<dp[i][j]<<endl;
            // assert(brute==dp[i][j]);
        }
    }
}

} // namespace Wallbreaker5th
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (ll i = 1; i <= n; i++) cin >> a[i];
        for (ll i = 1; i <= n; i++) cin >> b[i];
        for (ll i = 1; i <= n; i++) {
            B[i] = B[i - 1] - b[i];
            A[i] = a[i] + B[i];
        }
        Wallbreaker5th::preprocess();
        // for (ll i = 0; i < LG; i++) {
        //     for (ll j = 1; j <= n; j++) cout << dp[i][j] << " ";
        //     cout << endl;
        // }
        for (ll i = 0; i < LG; i++)
            for (ll j = n - 1; j; j--) dp[i][j] = min(dp[i][j], dp[i][j + 1]);
        ll ans = 0;
        for (ll i = 1, mult = 233; i <= m; i++, mult = mult * 233 % 998244353) {
            ll l, r, res = 0;
            cin >> l >> r;
            for (ll j = 0; j < LG; j++)
                if (dp[j][l] <= r) res |= 1ll << j;
            // cout<<res<<endl;
            ans = (ans + mult * res) % 998244353;
        }
        cout << ans << '\n';
    }

    return 0;
}

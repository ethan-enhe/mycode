#include <bits/stdc++.h>

#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
#define fi first
#define se second
const int MAXN = 105;
const int LIM = 5.3e7;
const int SFT = LIM / 2;
const int MAXS = 25;
int n;
pli a[MAXN];
bitset<LIM> f[MAXN - MAXS];
ll sm[1 << MAXS];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }
const int NR = 1e6 + 5;
vector<int> ans1[NR];
int main() {
    // freopen("1.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // cerr << (sizeof(f) >> 20) << endl;
    cin >> n;
    // cerr << "n " << n << '\n';
    for (int i = 1; i <= n; i++) {
        cin >> a[i].fi;
        a[i].se = i;
        // cerr << "a " << i << ' ' << a[i] << '\n';
    }
    vector<pair<int, int>> tmp1;
    for (int i = 1; i < NR; i++) {
        int sum = 0;
        for (int j = 1; j <= n / 2; j++) {
            if (randint(0, 1)) {
                sum += a[j].fi;
                ans1[i].push_back(a[j].se);
            } else
                sum -= a[j].fi;
        }
        tmp1.push_back({sum, i});
    }
    sort(tmp1.begin(), tmp1.end());
    for (int i = 1; i <NR; i++) {
        int sum = 0;
        vector<int> ans;
        for (int j = n / 2 + 1; j <= n; j++) {
            if (randint(0, 1)) {
                sum += a[j].fi;
                ans.push_back(a[j].se);
            } else
                sum -= a[j].fi;
        }
        auto it = lower_bound(tmp1.begin(), tmp1.end(), pair<int, int>{-sum, 0});
        if (it != tmp1.end() && it->first == -sum) {
            for (int j : ans1[it->se]) ans.push_back(j);
            sort(ans.begin(), ans.end());
            cout << ans.size() << ' ';
            for (int j : ans) cout << j << ' ';
            return 0;
        }
    }
    // sort(a + 1, a + n + 1);
    // // cerr << "wtf\n";
    // int hf2 = min(n, MAXS);
    // int hf1 = n - hf2;
    // f[0][SFT] = 1;
    // for (int i = 1; i <= hf1; i++) {
    //     f[i] = (f[i - 1] << int(a[i].fi)) | (f[i - 1] >> int(a[i].fi));
    // }
    // ll tol = 0;
    // for (int i = 0; i < hf2; i++) {
    //     sm[1 << i] = a[hf1 + 1 + i].fi;
    //     tol += a[hf1 + 1 + i].fi;
    // }
    // int res = -1;
    // for (int s = 0; s < (1 << hf2); s++) {
    //     if (s != 0) sm[s] = sm[s ^ (s & (-s))] + sm[s & (-s)];
    //     if (tol - 2 * sm[s] + SFT >= 0 && tol - 2 * sm[s] + SFT < LIM && f[hf1][tol - 2 * sm[s] + SFT]) res = s;
    // }
    // assert(res != -1);
    // vector<int> ans;
    // for (int i = 0; i < hf2; i++) if ((res >> i) & 1) ans.push_back(a[hf1 + 1 + i].se);
    // ll ns = tol - 2 * sm[res];
    // for (int i = hf1; i >= 1; i--){
    //     if (ns - a[i].fi + SFT >= 0 && ns - a[i].fi + SFT < LIM && f[i - 1][ns - a[i].fi + SFT]){
    //         ns -= a[i].fi;
    //         ans.push_back(a[i].se);
    //     } else ns += a[i].fi;
    // }
    // sort(ans.begin(), ans.end());
    // cout << ans.size() << ' ';
    // for (int i : ans) cout << i << ' ';
    // cout << '\n';
    return 0;
}

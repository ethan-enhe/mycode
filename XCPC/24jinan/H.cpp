#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 24;
ll x, z;
ll x_dig[MXN], z_dig[MXN];
ll dp[MXN][2][3]; // 处理完成低i位，是否大于上界限，必不能/可能进位/必须。
const ll mp[2][2] = {{-1, 0}, {2, 1}};

bool rnd(int x) { return x >= 5; }
int rem(int x) { return x >= 10 ? x - 10 : x; }
bool carry(int x) { return x >= 10; }

ll solve(ll x, ll z) {
    for (ll i = 1; i < MXN; i++) {
        x_dig[i] = x % 10;
        x /= 10;
        z_dig[i] = z % 10;
        z /= 10;
        // cout << x_dig[i];
    }
    // cout << endl;
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    auto nxf = [](ll targ, ll dig, bool f) {
        if (f) return dig >= targ;
        return dig > targ;
    };
    for (ll i = 0; i < MXN - 1; i++) {
        for (ll f = 0; f < 2; f++)
            for (ll g = 0; g < 3; g++) {
                auto v = dp[i][f][g];
                if (!v) continue;
                // cerr << i << ' ' << f << ' ' << g << ' ' << v << endl;
                for (int j = 0; j < 10; j++) {
                    bool ngf[2] = {0, 0};
                    if (g <= 1) { // 不进位
                        // 不round
                        if (x_dig[i + 1] == j) ngf[0] = 1;
                        // round
                        if (x_dig[i + 1] == 0) ngf[rnd(j)] = 1;
                    }
                    if (g >= 1) {
                        // 不round
                        if (x_dig[i + 1] == rem(j + 1)) ngf[carry(j + 1)] = 1;
                        // 进位前round
                        if (x_dig[i + 1] == 1) ngf[rnd(j)] = 1;
                        // 进位后round
                        if (x_dig[i + 1] == 0) ngf[carry(j + 1) || rnd(rem(j + 1))] = 1;
                        // // 前后都round
                        if (x_dig[i + 1] == 0) ngf[rnd(j)] = 1;
                    }
                    ll ng = mp[ngf[1]][ngf[0]];
                    if (ng >= 0) dp[i + 1][nxf(z_dig[i + 1], j, f)][ng] += v;
                }
                // cerr << endl;
            }
    }
    return dp[MXN - 1][0][0];
}
ll kth(ll k) {
    ll l = 1, r = z;
    while (l < r) {
        ll mid = (l + r) / 2;
        if (solve(x, mid) < k) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    cout << l << " " << solve(x, l) << '\n';
    return l;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    //
    // cin >> x >> z;
    // ll ans = solve(x, z);
    // cout << " " << x << " " << ans << '\n';
    // for (ll i = 1; i <= 10; i++) {
    //     ll idx = rand() % ans + 1;
    //     ll val = kth(idx);
    //     // cout << val << " " << idx << endl;
    //     // assert(solve(x, val) - solve(x, val - 1) == 1);
    // }

    ll t;
    cin >> t;
    while (t--) {
        cin >> x >> z;
        cout << solve(x, z) << '\n';
    }

    //
    // 2123016556664996 1919810
    // 3122507962333010
    return 0;
}

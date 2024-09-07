
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 16;
const ll INF = 1e18;
const ll NR = 512;
ll arr[MXN][MXN];
ll n, m, s;
ll csum[MXN];

ll halfm;
pair<ll, ll> pool[NR];
ll top;
ll ssave_r;
void genc(ll i, ll sum, ll save_c) {
    if (i == halfm + 1) {
        pool[++top] = {sum, save_c};
        return;
    }
    genc(i + 1, sum + csum[i], save_c);
    genc(i + 1, sum, save_c | (1 << i));
}
void quec(ll i, ll sum, ll save_c) {
    if (i == m + 1) {
        ll tmp = s - sum;
        ll i = lower_bound(pool + 1, pool + top + 1, make_pair(tmp, 0ll)) - pool;
        if (i <= top && pool[i].first == tmp) {
            cout << "YES" << endl;
            ll totc = __builtin_popcount(save_c | pool[i].second);
            ll totr = __builtin_popcount(ssave_r);
            cout << totc + totr << endl;
            for (ll i = 1; i <= n; i++)
                if (ssave_r & (1 << (i))) cout << "1 " << i << endl;
            for (ll j = 1; j <= m; j++)
                if ((save_c | pool[i].second) & (1 << (j))) cout << "2 " << j << endl;
            exit(0);
        }
        return;
    }
    quec(i + 1, sum + csum[i], save_c);
    quec(i + 1, sum, save_c | (1 << i));
}

void dfsr(ll i, ll save_r) {
    if (i == n + 1) {
        ssave_r = save_r;
        top = 0;
        genc(1, 0, 0);
        sort(pool + 1, pool + top + 1);
        quec(halfm + 1, 0, 0);
        return;
    }
    for (ll j = 1; j <= m; j++) csum[j] += arr[i][j];
    dfsr(i + 1, save_r);
    for (ll j = 1; j <= m; j++) csum[j] -= arr[i][j];
    dfsr(i + 1, save_r | (1 << i));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    halfm = (m + 1) / 2;
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++) {
            cin >> arr[i][j];
        }
    cin >> s;
    dfsr(1, 0);
    cout << "NO" << endl;

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int MXN = 605;
using ll = long long;
ll n, m, arr[MXN];
bool I_is_a_english_man[MXN][MXN];
ll dis[MXN][MXN];

#define people(x) (x)
#define language(y) ((y) + n)
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));
    for (ll i = 1; i <= language(m); i++) dis[i][i] = 0;
    for (ll i = 1; i <= n; i++) {
        ll k;
        cin >> k;
        while (k--) {
            ll x;
            cin >> x;
            I_is_a_english_man[i][x] = 1;
        }
    }
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
            if (I_is_a_english_man[i][j]) {
                ll cnt = 0;
                for (ll l = 1; l <= n; l++) {
                    cnt += I_is_a_english_man[l][j];
                }
                dis[people(i)][language(j)] = cnt;
                dis[language(j)][people(i)] = 0;
            }
    for (ll i = 1; i <= m; i++)
        for (ll j = 1; j <= m; j++) {
            if (i == j) continue;
            ll cnt = 0;
            bool f = 0;
            for (ll k = 1; k <= n; k++) {
                cnt += I_is_a_english_man[k][j] && !I_is_a_english_man[k][i];
                f |= I_is_a_english_man[k][j] && I_is_a_english_man[k][i];
            }
            if (f) dis[language(i)][language(j)] = cnt;
        }
    for (ll k = 1; k <= language(m); k++)
        for (ll i = 1; i <= language(m); i++)
            for (ll j = 1; j <= language(m); j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    for (ll i = 1; i <= n; i++, cout << '\n')
        for (ll j = 1; j <= n; j++) cout << (dis[i][j] > 10000 ? -1 : dis[i][j]) << " ";
    return 0;
}

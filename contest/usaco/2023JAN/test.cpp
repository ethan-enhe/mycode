#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;

const ll MXN = 2e5 + 5;
ll n, m;
char str[MXN];
pi arr[MXN];

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    cin >> n >> m;
    cin >> (str + 1);
    for (ll i = 1, cl = 0, cr = 0; i <= n * 2; i++) {
        if (str[i] == 'L')
            arr[++cl].fi = i;
        else
            arr[++cr].se = i;
    }
    for (ll i = 1; i <= n; i++) cout << arr[i].fi << " " << arr[i].se << '\n';
    return 0;
}

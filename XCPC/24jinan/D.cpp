#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXN = 1200;
const ll P = 998244353;
struct inst {
    ll a, b, x, y;
} prog[MXN];
struct res {
    ll len, jmp;
} f[MXN][MXN];
// -1 死循环 -2 在栈里面 -3 未知
ll n;

res dfs(ll x, ll y) {
    auto &v = f[x][y];
    auto i = prog[x];
    if (v.len >= -1) return v;
    if (v.len == -2) return v = {-1, 0};
    v = {-2, 0};
    if (i.a == y) {
        return v = {1, i.x};
    } else {
        auto r1 = dfs(i.y, i.b);
        if (r1.len == -1) return v = {-1, 0};
        auto r2 = dfs(r1.jmp, y);
        if (r2.len == -1) return v = {-1, 0};
        r2.len = (r2.len + r1.len + 1) % P;
        return v = r2;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (ll i = 0; i < MXN; i++)
        for (ll j = 0; j < MXN; j++) f[i][j] = {-3, 0};
    for (ll i = 1; i <= n; i++) {
        auto &v = prog[i];
        string s;
        cin >> s;
        if (s[0] == 'P') {
            cin >> v.a >> s >> v.x >> s >> s >> v.b >> s >> v.y;
        } else {
            cin >> s >> v.b >> s >> v.y;
        }

        // cout << v.tp << " " << v.a << " " << v.x << " " << v.b << ' ' << v.y << endl;
    }
    cout << dfs(1, 0).len << '\n';

    return 0;
}

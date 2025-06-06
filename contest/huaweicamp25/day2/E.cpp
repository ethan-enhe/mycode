#include <bits/stdc++.h>

#include <vector>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
pi operator+(const pi x, const pi y) { return pi{x.first + y.first, x.second + y.second}; }
pi go[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

const ll MXN = 55;
char mp[MXN][MXN];
ll n, m;

bool valid(pi x) { return x.first > 0 && x.second > 0 && x.first <= n && x.second <= m; }

ll cal(char x, vector<ll> input) {
    if (x >= '0' && x <= '9') return x - '0';
    if (x == '#' || x == 'P') return input[0];
    if (input[0] < input[1]) swap(input[0], input[1]);
    if (x == '+') return input[0] + input[1];
    if (x == '-') return input[0] - input[1];
    if (x == '*') return input[0] * input[1];
    if (x == '/') return input[0] / input[1];
}

ll solve(pi u, pi fa) {
    // cerr << u.first << " " << u.second << endl;
    vector<ll> va;
    for (ll i = 0; i < 4; i++) {
        pi v = u + go[i];
        if (v == fa) continue;
        if (valid(v) && mp[v.first][v.second] != '.') va.push_back(solve(v, u));
    }
    return cal(mp[u.first][u.second], va);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> (mp[i] + 1);
    }
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
            if (mp[i][j] == 'P') {
                cout << solve({i, j}, {-1, -1});
                return 0;
            }
    return 0;
}

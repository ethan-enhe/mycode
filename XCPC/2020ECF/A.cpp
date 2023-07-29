#include <cstring>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll P = 998244353;
const ll MXN = 1000005;
const ll C = 62;
ll n;
char str[MXN];
int cnt[MXN][C];
int nxt[MXN][C];
int dp[MXN][C];
ll getnum(char x) {
    if (x >= 'a' && x <= 'z') return x - 'a';
    if (x >= 'A' && x <= 'Z') return x - 'A' + 26;
    return 52 + x - '0';
}
#define cur getnum(str[i])
int main() {
    // freopen("test.in", "r", stdin);

    ios::sync_with_stdio(0);
    cin.tie(0);
    // cout<<(sizeof(dp)>>20);
    cin >> (str + 1);
    n = strlen(str + 1);
    for (ll i = n; i; i--) {
        memcpy(nxt[i], nxt[i + 1], sizeof(nxt[0]));
        nxt[i][cur] = i;
    }
    for (ll i = n; i; i--) {
        memcpy(cnt[i], cnt[i + 1], sizeof(nxt[0]));
        ++cnt[i][cur];
    }
    for (ll i = n; i; i--) {
        ll nx = nxt[i + 1][cur];
        if (nx) {
            for (ll j = 0; j < C; j++) cnt[i][j] = (cnt[i][j] + cnt[nx][j]) % P;
        }
    }

    for (ll i = n; i; i--) {
        int c = cur;
        for (ll j = 0; j < C; j++) {
            int nx = nxt[i + 1][j];
            dp[i][j] = nx ? cnt[nx][c] : 0;
        }
        ll nx = nxt[i + 1][c];
        if (nx) {
            for (ll j = 0; j < C; j++) dp[i][j] = (dp[i][j] + dp[nx][j]) % P;
        }
    }

    for (ll i = n; i; i--) {
        int c = cur;
        for (ll j = 0; j < C; j++) {
            int nx = nxt[i + 1][j];
            cnt[i][j] = nx ? dp[nx][c] : 0;
        }
    }
    for (ll i = 1; i <= n; i++) {
        memcpy(dp[i], dp[i - 1], sizeof(nxt[0]));
        ++dp[i][cur];
    }
    ll ans = 0;
    for (ll i = n; i; i--) {
        ll multi = 0;
        ll c = cur;
        ll tot = i - 1 - dp[i - 1][c];
        for (ll j = 0; j < C; j++) {
            if (j != c) multi = (multi + (ll)dp[i - 1][j] * (dp[i - 1][j] - 1) / 2) % P;
        }
        for (ll j = 0; j < C; j++) {
            if (j == c) continue;
            ll tmp = (tot - dp[i - 1][j]);
            tmp = tmp * (tmp - 1) / 2;
            tmp = (tmp - multi + (ll)dp[i - 1][j] * (dp[i - 1][j] - 1) / 2) % P;

            ans = (ans + tmp * cnt[i][j]) % P;
        }
    }
    cout << (ans + P) % P;

    return 0;
}

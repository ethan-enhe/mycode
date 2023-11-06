#include <bits/stdc++.h>

#include <algorithm>
using namespace std;

//{{{ Def
#define fi first
#define se second
#define pb push_back
#define log(fmt...) fprintf(stderr, fmt)

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
//}}}
const ll INF = 1e18;
ll P = 1e9 + 7, B;
//{{{ Func
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <class T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <class T>
void umn(T &x, T y) {
    x = min(x, y);
}
//}}}
const ll MXN = 1e6 + 5;
ll n, m;
ll arr[MXN], last[MXN];
ll h[MXN], r1[MXN], r2[MXN];
inline ll qpow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P, y >>= 1;
    }
    return r;
}
inline void cal(ll *r) {
    for (int i = 1; i <= n; i++) {
        last[i] = r[i] = 0;
        h[i] = (h[i - 1] * B + arr[i]) % P;
    }
    for (int i = 1; i <= n; i++) {
        ll pre = last[arr[i]];
        r[arr[i]] = ((r[arr[i]] - h[pre]) * qpow(B, i - 1 - pre) + h[i - 1]) % P;
        last[arr[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        ll cur = n + 1, pre = last[i];
        r[i] = ((r[i] - h[pre]) * qpow(B, cur - 1 - pre) + h[cur - 1]) % P;
    }
}

void solve() {
    scanf("%lld", &n);
    B = rand() | 1;
    P = rand() | 1;
    for (int i = 1; i <= n; i++) scanf("%lld", arr + i);
    cal(r1);
    reverse(arr + 1, arr + 1 + n);
    cal(r2);
    for (int i = 1; i <= n; i++) {
        r1[i] = (r1[i] + P) % P;
        r2[i] = (r2[i] + P) % P;
        if (r1[i] == r2[i]) {
            puts("YES");
            return;
        }
    }
    puts("NO");
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    srand(time(NULL));
    ll t;
    scanf("%lld", &t);
    while (t--) solve();

    return 0;
}

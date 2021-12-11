#include <bits/stdc++.h>


using namespace std;

//{{{ Def
#define fi first
#define se second
#define pb push_back
#define log(fmt...) fprintf(stderr, fmt)
#define va2d(x, y) x[(y.fi)][(y.se)]

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
const ll INF = 1e18, MXN = 1e4 + 5;
ll n, m, ans = INF, cnt, ind;
ll arr[MXN], brr[MXN];
//{{{ Func
template <class T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <class T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <class T>
void umn(T &x, T y) {
    x = min(x, y);
}
ll abs(pi x) { return abs(x.fi) + abs(x.se); }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
//}}}

bool cmp(const ll &x, const ll &y) { return x > y; }
ll cal(ll *x, ll ci) {
    ll cur = 0, s1 = 0, s2 = 0;
    for (int i = 1; i <= n; i++) {
        cur += x[i];
        s1 += cur, s2 += cur * cur;
    }
    return -s1 * s1 + s2 * n;
}
void solve() {
    // code
    ll st = clock() + CLOCKS_PER_SEC * 0.95;
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", arr + i);
    for (int i = n; i; i--) arr[i] -= arr[i - 1];
    for (int i = 1; i <= n; i++) cnt += arr[i] <= arr[1];
    while (clock() < st) {
        double T = 1e18, rate = 0.99;
        ll ind = randint(1, n);
        if (n != 1) shuffle(arr + 2, arr + 1 + n, myrand);
		if (ind != 1) sort(arr + 2, arr + 1 + ind, cmp);
		if (ind != n) sort(arr + ind + 1, arr + n + 1);
        while (T > 0.1 && clock() < st) {
            for (int i = 1; i <= n; i++) brr[i] = arr[i];
            ll x = randint(2, n), nxind;
            if (x > ind) {
                nxind = ind + 1;
                swap(brr[nxind], brr[x]);
				for(int i=nxind;i>2;i--)
					if(brr[i-1]<brr[i])
						swap(brr[i-1],brr[i]);
            } else {
                swap(brr[ind], brr[x]);
				for(int i=ind;i<n;i++)
					if(brr[i]>brr[i+1])
						swap(brr[i],brr[i+1]);
                nxind = ind - 1;
            }
            ll cur = cal(arr, ind) - cal(brr, nxind);
            if (cur > 0 || randdb(0, 1) <= exp(cur / T)) {
                for (int i = 1; i <= n; i++) arr[i] = brr[i];
                ind = nxind;
            }

            T *= rate;
        }
        umn(ans, cal(arr, ind));
    }
    printf("%lld", ans);
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    // ll t;scanf("%lld",&t);while(t--)
    solve();

    return 0;
}


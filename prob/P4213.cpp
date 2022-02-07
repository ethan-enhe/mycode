#include <bits/stdc++.h>

#include <unordered_map>
using namespace std;
typedef long long ll;
namespace sum {
ll sum_g(ll x) { return x; }
ll sum_fg(ll x) { return 1; }
unordered_map<ll, ll> sum_f_save;
ll sum_f(ll x) {
    auto it = sum_f_save.find(x);
    if (it != sum_f_save.end()) return it->second;
    ll ans = sum_fg(x);
    for (ll l = 2, r, v; l <= x; l = r + 1) {
        v = x / l, r = x / v;
        ans -= (sum_g(r) - sum_g(l - 1)) * sum_f(v);
    }
    return sum_f_save[x] = ans;
}
} // namespace sum
ll t, n;
int main() {
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld", &n);
        printf("%lld\n", sum::sum_f(n));
    }

    return 0;
}

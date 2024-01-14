
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll P1 = 1e9 + 7;
const ll P2 = 998244353;
struct mod {
    ll x, y;
    mod(ll x, ll y) : x(x), y(y) {}
    mod(ll x = 0) : x(x), y(x) {}
    mod operator+(const mod &b) { return mod((x + b.x) % P1, (y + b.y) % P2); }
    mod operator-(const mod &b) { return mod((x - b.x + P1) % P1, (y - b.y + P2) % P2); }
    mod operator*(const mod &b) { return mod((x * b.x) % P1, (y * b.y) % P2); }
    bool operator==(const mod &b) { return x == b.x && y == b.y; }
};
const mod B(131, 101);
 
const ll MXN = 1e6 + 5;
 
mod pw[MXN];
mod h[MXN];
 
ll arr[MXN], n;
char ans[MXN];
ll mrk[MXN];
void init() {
    pw[0] = 1;
    for (ll i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * B;
        h[i] = h[i - 1] * B + arr[i];
    }
}
mod get_hash(ll l, ll r) { return h[r] - h[l - 1] * pw[r - l + 1]; }
bool chk(ll pre, ll k) { return get_hash(1, pre - k * 2) + get_hash(1 + k * 2, pre) == get_hash(1 + k, pre - k) * 2; }
stack<ll> s;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll q;
    cin >> n >> q;
    for (ll i = 1; i <= n; i++) {
        cin>>arr[i];
    }
    while (q--) {
        int qi, qx;
        cin >> qi >> qx;
        if (qi == -1) {
            init();
            for (ll i = 1; i <= n; i++) {
                ans[i] = '0';
                mrk[i] = 0;
            }
            for (int i = 1; i <= n; i++) {
                ll l = i * 2, r = n;
                while (l < r) {
                    ll mid = (l + r + 1) >> 1;
                    if (chk(mid, i))
                        l = mid;
                    else
                        r = mid - 1;
                }
                ++mrk[i * 2 + 1];
                --mrk[l + 1];
            }
            for (ll i = 1; i <= n; i++) {
                mrk[i] += mrk[i - 1];
                if (mrk[i]) ans[i] = '1';
            }
            cout << (ans + 1) << '\n';
        } else
            arr[qi] = qx;
    }
 
    return 0;
}

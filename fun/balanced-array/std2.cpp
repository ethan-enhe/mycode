#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll P1 = 1000004023;
const ll P2 = 1000000223;
struct mod {
    ll x, y;
    mod(ll x, ll y) : x(x), y(y) {}
    mod(ll x = 0) : x(x), y(x) {}
    mod operator+(const mod &b) { return mod((x + b.x) % P1, (y + b.y) % P2); }
    mod operator-(const mod &b) { return mod((x - b.x + P1) % P1, (y - b.y + P2) % P2); }
    mod operator*(const mod &b) { return mod((x * b.x) % P1, (y * b.y) % P2); }
    bool operator==(const mod &b) { return x == b.x && y == b.y; }
};
const mod B(137, 179);

const ll MXN = 1e7 + 5;

mod pw[MXN];
mod h[MXN];

ll arr[MXN], n;
char ans[MXN];
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
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        ans[i] = '0';
    }
    init();
    for (ll i = n; i > 2; i--) {
        s.push(i);
        if (i & 1) {
            while (!s.empty()) {
                if (!chk(s.top(), (i - 1) / 2)) break;
                ans[s.top()] = '1';
                s.pop();
            }
        }
    }
    cout << (ans + 1);

    return 0;
}

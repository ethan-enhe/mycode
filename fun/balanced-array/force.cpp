#include <bits/stdc++.h>
using namespace std;
namespace io {
using ll = long long;
const ll B = 62;
ll c2i(char c) {
    if (isdigit(c)) return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 36;
    assert(0);
}
char i2c(ll x) {
    if (x >= 0 && x < 10) return '0' + x;
    if (x >= 10 && x < 36) return x - 10 + 'a';
    if (x >= 36 && x < 62) return x - 36 + 'A';
    assert(0);
}
ll s2i(string s) {
    assert(s.length() <= 10);
    ll res = 0;
    for (auto &i : s) res = res * B + c2i(i);
    return res;
}
string i2s(ll x) {
    if (x == 0) return "0";
    string res = "", tt = "";
    while (x) {
        tt += i2c(x % B);
        x /= B;
    }
    for (int i = tt.size() - 1; i >= 0; i--) res += tt[i];
    return res;
}
} // namespace io
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

const ll MXN = 1e7 + 5;

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
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        string s;
        cin >> s;
        arr[i] = io::s2i(s);
        ans[i] = '0';
    }
    init();
    // cout<<get_hash(1, n/3).x<<" "<<get_hash(1+n/3, n/3*2).y<<endl;
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
    cout << (ans + 1);

    return 0;
}

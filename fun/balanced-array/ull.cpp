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
using mod = unsigned long long;
const mod B = 1e9 + 7;

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
        string s;
        cin >> s;
        arr[i] = io::s2i(s);
        ans[i] = '0';
    }
    init();
    // cout<<get_hash(1, n/3)<<" "<<get_hash(1+n/3, n/3*2)<<" "<<get_hash(1+n/3*2, n)<<endl;
    for (ll i = n; i > 2; i--) {
        s.push(i);
        if (i & 1) {
            while (!s.empty()) {
                if (!chk(s.top(), (i - 1) / 2)) break;
            // if ((i - 1) / 2 == n / 3) cout << "!!!" << endl;
                ans[s.top()] = '1';
                s.pop();
            }
        }
    }
    cout << (ans + 1);

    return 0;
}

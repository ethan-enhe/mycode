#include <bits/stdc++.h>
using namespace std;
namespace fio {
const int BS = 1 << 20;
char ibuf[BS], *ip1 = ibuf, *ip2 = ibuf;
#define gc() (ip1 == ip2 && (ip2 = (ip1 = ibuf) + fread(ibuf, 1, BS, stdin), ip1 == ip2) ? EOF : *ip1++)

inline bool is62d(char c) { return isdigit(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
inline int c2i(char c) {
    if (isdigit(c)) return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return c - 'A' + 36;
}
template <class T>
inline void read(T &x) {
    x = 0;
    char c;
    while (c = gc(), !is62d(c))
        ;
    while (is62d(c)) x = x * 62 + c2i(c), c = gc();
}
#undef gc
#undef pc
#undef flsh
} // namespace fio
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
const mod B(499999993, 499999931);

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
        fio::read(arr[i]);
        ans[i] = '0';
    }
    init();
    // cout<<get_hash(1, n/3).x<<" "<<get_hash(1+n/3, n/3*2).y<<endl;
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


#include <bits/stdc++.h>
using namespace std;
namespace nqio {
const unsigned R = 4e5, W = 4e5;
char *a, *b, i[R], o[W], *c = o, *d = o + W, h[40], *p = h, y;
bool s;
struct q {
    void r(char &x) { x = a == b && (b = (a = i) + fread(i, 1, R, stdin), a == b) ? -1 : *a++; }
    void f() {
        fwrite(o, 1, c - o, stdout);
        c = o;
    }
    ~q() { f(); }
    void w(char x) {
        *c = x;
        if (++c == d) f();
    }
    q &operator>>(char &x) {
        do r(x);
        while (x <= 32);
        return *this;
    }
    q &operator>>(char *x) {
        do r(*x);
        while (*x <= 32);
        while (*x > 32) r(*++x);
        *x = 0;
        return *this;
    }
    template <typename t>
    q &operator>>(t &x) {
        for (r(y), s = 0; !isdigit(y); r(y)) s |= y == 45;
        if (s)
            for (x = 0; isdigit(y); r(y)) x = x * 10 - (y ^ 48);
        else
            for (x = 0; isdigit(y); r(y)) x = x * 10 + (y ^ 48);
        return *this;
    }
    q &operator<<(char x) {
        w(x);
        return *this;
    }
    q &operator<<(char *x) {
        while (*x) w(*x++);
        return *this;
    }
    q &operator<<(const char *x) {
        while (*x) w(*x++);
        return *this;
    }
    template <typename t>
    q &operator<<(t x) {
        if (!x)
            w(48);
        else if (x < 0)
            for (w(45); x; x /= 10) *p++ = 48 | -(x % 10);
        else
            for (; x; x /= 10) *p++ = 48 | x % 10;
        while (p != h) w(*--p);
        return *this;
    }
} qio;
} // namespace nqio
using nqio::qio;
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
struct mod {
    ll x;
    mod(ll x = 0) : x(x) {}
    mod operator+(const mod &b) { return mod((x + b.x) % P1); }
    mod operator-(const mod &b) { return mod((x - b.x + P1) % P1); }
    mod operator*(const mod &b) { return mod((x * b.x) % P1); }
    bool operator==(const mod &b) { return x == b.x; }
};
const mod B(131);

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
char tmp[20];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    qio >> n;
    for (ll i = 1; i <= n; i++) {
        qio >> tmp;
        char *it = tmp;
        string s;
        while (*it) s += *it, it++;
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
    qio << (ans + 1);

    return 0;
}

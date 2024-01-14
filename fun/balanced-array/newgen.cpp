#include <bits/stdc++.h>

#include <cmath>

#include "testlib.h"

/*
能不能这样造：先设定一个值 C 在差不多值域的正中间，然后每一个数有三种填法：
- 在 C 附近随机一个数
- 如果下标 i（1-base）是奇数，可以用 2 a_((i+1)/2) - a_1 算这个数
- 如果上一个数是用第二或第三种方式填进去的，则类似地前面的数算出这一个
    */
using namespace std;

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
int MX = 2e8;
bool inrng(int x) { return x <= MX && x >= 1; }
const int MXN = 1e7 + 5;
int a[MXN];
int main(int argc, char **argv) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    registerGen(argc, argv, 1);
    int mxn = opt<int>(1);
    rnd.setSeed(opt<int>(2));
    int n = rnd.wnext(1, mxn, 10);
    cout << n << '\n';
    int ZERO = rnd.next(MX / 3, MX * 2 / 3);
    int st = 1;
    int p = pow(n, 0.75);
    for (int i = 1; i <= n; i++) {
        if (i > 1 && (i ^ st) % 2 == 0 && inrng(2 * a[(i + st) / 2] - a[st]) &&
            (st == 1 ? rnd.next(1, n) < p : rnd.next(1, n) >= p)) {
            a[i] = 2 * a[(i + st) / 2] - a[st];
            ++st;
            // cout << i << endl;
        } else if (i == 1 || rnd.next(1, 5) <= 4) {
            st = 1;
            a[i] = ZERO + rnd.next(-1, 1) * rnd.wnext(0, 1000, 30);
        } else {
            st = 1;
            a[i] = rnd.next(MX / 3, MX * 2 / 3);
        }
        cout << i2s(a[i]);
        if (i < n) cout << ' ';
    }
    cout << '\n';
    return 0;
}

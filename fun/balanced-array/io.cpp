#include <bits/stdc++.h>

#include <cctype>
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
int main() {
    cout << i2s(100);

    return 0;
}

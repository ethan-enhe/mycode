#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10, mod1 = 1e9 + 7, mod2 = 1e9 + 21;
struct pii {
    int x, y;
};
const pii base{500000000, 500000009};
pii operator+(const pii &a, const pii &b) { return {(a.x + b.x) % mod1, (a.y + b.y) % mod2}; }
pii operator-(const pii &a, const pii &b) { return {(a.x - b.x + mod1) % mod1, (a.y - b.y + mod2) % mod2}; }
pii operator*(const pii &a, const pii &b) { return {(1ll * a.x * b.x) % mod1, (1ll * a.y * b.y) % mod2}; }
bool operator==(const pii &a, const pii &b) { return a.x == b.x && a.y == b.y; }

pii h[N], pw[N];
int a[N];

pii hsh(int l, int r) { return h[r] - h[l - 1] * pw[r - l + 1]; }
bool check(int l, int r, int k) {
    pii h1 = hsh(l, r - k * 2);
    pii h2 = hsh(l + k, r - k);
    pii h3 = hsh(l + k * 2, r);
    return h1 + h3 == h2 + h2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    pw[0] = {1, 1};
    for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * base;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (q--) {
        int qi, qx;
        cin >> qi >> qx;
        if (qi == -1) {
            for (int i = 1; i <= n; i++) h[i] = h[i - 1] * base + pii{a[i], a[i]};

            int k = 1;
            for (int i = 1; i <= n; i++) {
                if (i <= 2) {
                    cout << '0';
                    continue;
                }
                bool ok = false;
                while (1 + 2 * k <= i) {
                    if (check(1, i, k)) {
                        ok = true;
                        break;
                    }
                    k++;
                }
                if (ok)
                    cout << '1';
                else
                    cout << '0';
            }
            cout << '\n';
        } else
            a[qi] = qx;
    }
    return 0;
}

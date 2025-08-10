#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

const long long MOD = 998244353;

long long gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    long long n, q;
    cin >> n >> q;
    vector<long long> a(n + 1);
    vector<long long> jmp(n + 1);

    for (long long i = 1; i <= n; ++i) {
        cin >> a[i];
        jmp[i] = gcd(i, a[i]);
    }

    while (q--) {
        long long op;
        cin >> op;
        if (op == 1) {
            long long l, r, c;
            cin >> l >> r >> c;
            for (long long i = l; i <= r; ++i) {
                jmp[i] = jmp[i] * gcd(i / jmp[i], c);
                a[i] = (1LL * a[i] * c) % 998244353;
            }
        } else if (op == 2) {
            long long x;
            cin >> x;
            long long sum = 0;
            while (x <= n) {
                sum = (sum + a[x]) % MOD;
                x += jmp[x];
            }
            cout << sum << endl;
        }
    }

    return 0;
}

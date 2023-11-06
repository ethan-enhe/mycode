#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int MXN = 3.5e3;
const int V = 1e9;

int n, m, arr[MXN], sum[MXN];
int main() {
    cin >> n >> m;
    --m;
    if (m == 0) {
        if (n == 1)
            cout << 1 << endl;
        else
            cout << "Poor E.S.!" << endl;
        return 0;
    }
    sum[0] = 1;
    int dig = 1;
    for (int i = 2; i <= n; i++) {
        memcpy(arr, sum, sizeof(int) * (dig + 2));
        arr[0] += m - 1;
        for (int i = 0; i <= dig; i++) {
            if (arr[i] >= V) arr[i] -= V, arr[i + 1]++;
        }
        if (arr[dig + 1]) ++dig;
        ll v = 0;
        if (m != 1) {
            if (m != 2)
                for (int i = dig; i >= 0; i--) {
                    v = v * V + arr[i];
                    arr[i] = v / m;
                    v -= (ll)arr[i] * m;
                }
            else {
                for (int i = dig; i >= 0; i--) {
                    v = v * V + arr[i];
                    arr[i] = v >> 1;
                    v &= 1;
                }
            }
        }

        if (i == n) {
            bool f = 0;
            for (int i = MXN - 1; i >= 0; i--) {
                if (arr[i] && !f) {
                    f = 1;
                    printf("%d", arr[i]);
                } else if (f) {
                    printf("%09d", arr[i]);
                }
            }
            break;
        }
        for (int i = 0; i <= dig; i++) {
            sum[i] += arr[i];
            if (sum[i] >= V) sum[i] -= V, sum[i + 1]++;
            arr[i] = 0;
        }
        if (sum[dig + 1]) ++dig;
    }
    return 0;
}

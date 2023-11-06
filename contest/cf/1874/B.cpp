#include <bits/stdc++.h>

using namespace std;

const int MXN = 1e6;
int n, m, arr[MXN];
int go(int x, int op) {
    if (op == 1)
        x &= x | 3 << 1;
    else if (op == 2)
        x |= (x & 4) << 1;
    else if (op == 3)
        x ^= (x & 8) >> 1;
    else if (m)
        x ^= 4;
    return x;
}
ll dis[]
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    return 0;
}
